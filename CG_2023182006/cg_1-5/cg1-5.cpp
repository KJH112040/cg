#include <iostream>
#include <random>
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

float bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 1.0f;
typedef struct Rect {
	GLfloat x1, y1, x2, y2, r, g, b;
	bool check;
}Rect;
Rect r[40], eraser;
bool lbutton = false,start=true;
float e_size;
int num;

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLfloat> ps_uid(-1.0f, 0.95f),clr_uid(0.0f,1.0f);
std::uniform_int_distribution<int> cnt_uid(20, 40);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
GLvoid create_rect();
GLvoid eraser_setting();
GLfloat move_x(int x, float move);
GLfloat move_y(int y, float move);
bool Collision_detection(GLfloat obj1_x1, GLfloat obj1_y1, GLfloat obj1_x2, GLfloat obj1_y2, GLfloat obj2_x1, GLfloat obj2_y1, GLfloat obj2_x2, GLfloat obj2_y2);
//void TimerFunction(int value);

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("1-5"); // ������ ����(������ �̸�)
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW Initialized\n";
	create_rect();
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(bgc_r, bgc_g, bgc_b, 1.0f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����
	for (int i = 0; i < num; ++i) {
		if(r[i].check) {
			glColor3f(r[i].r, r[i].g, r[i].b);
			glRectf(r[i].x1, r[i].y1, r[i].x2, r[i].y2);
		}
	}
	if(lbutton){
		glColor3f(eraser.r, eraser.g, eraser.b);
		glRectf(eraser.x1, eraser.y1, eraser.x2, eraser.y2);
	}
	//--- �׸��� ���� �κ��� ���⿡ ���Եȴ�.
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{	glViewport(0, 0, w, h);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
		create_rect();
		break;
	}
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN&&button==GLUT_LEFT_BUTTON) {
		lbutton = true;
		eraser.x1 = move_x(x, -e_size);
		eraser.x2 = move_x(x, e_size);
		eraser.y1 = move_y(y, -e_size);
		eraser.y2 = move_y(y, e_size);
		for (int i = 0; i < num; ++i) {
			if (r[i].check) {
				if (Collision_detection(r[i].x1, r[i].y1, r[i].x2, r[i].y2, eraser.x1, eraser.y1, eraser.x2, eraser.y2)) {
					eraser.r = r[i].r, eraser.g = r[i].g, eraser.b = r[i].b;
					e_size += 0.005;
					r[i].check = false;
				}
			}
		}
	}
	else if (state == GLUT_UP) {
		lbutton = false;
		eraser_setting();
	}
	glutPostRedisplay();
}
void Motion(int x, int y) {
	if (lbutton) {
		eraser.x1 = move_x(x, -e_size);
		eraser.x2 = move_x(x, e_size);
		eraser.y1 = move_y(y, -e_size);
		eraser.y2 = move_y(y, e_size);
		for (int i = 0; i < num; ++i) {
			if(r[i].check) {
				if (Collision_detection(r[i].x1, r[i].y1, r[i].x2, r[i].y2, eraser.x1, eraser.y1, eraser.x2, eraser.y2)) {
					eraser.r = r[i].r, eraser.g = r[i].g, eraser.b = r[i].b;
					e_size += 0.005;
					r[i].check = false;
				}
			}
		}
	}
	glutPostRedisplay();
}
//void TimerFunction(int value){
//	glutPostRedisplay(); // ȭ�� �� ���
//	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
//}
GLvoid create_rect() {
	num = cnt_uid(dre);
	for (int i = 0; i < num; ++i) {
		GLfloat px = ps_uid(dre), py = ps_uid(dre);
		r[i].x1 = px, r[i].x2 = px + 0.05f, r[i].y1 = py, r[i].y2 = py + 0.05f;
		r[i].r = clr_uid(dre), r[i].g = clr_uid(dre), r[i].b = clr_uid(dre);
		r[i].check = true;
	}
}
GLvoid eraser_setting() {
	eraser.r = 0.0f, eraser.g = 0.0f, eraser.b = 0.0f;
	e_size = 0.05f;
}
GLfloat move_x(int x, float move) {
	return ((float)(x - 400) / 400) + move; // 400�� ȭ�� ���� ������ ��
}
GLfloat move_y(int y, float move) {
	return ((float)(300 - y) / 300) + move;
}
bool Collision_detection(GLfloat obj1_x1, GLfloat obj1_y1, GLfloat obj1_x2, GLfloat obj1_y2, GLfloat obj2_x1, GLfloat obj2_y1, GLfloat obj2_x2, GLfloat obj2_y2) {
	if (obj1_x1 <= obj2_x1 && obj2_x1 <= obj1_x2) {
		if (obj1_y1 <= obj2_y1 && obj2_y1 <= obj1_y2) {
			return true;
		}
		else if (obj2_y1 <= obj1_y1 && obj1_y1 <= obj2_y2) {
			return true;
		}
		else return false;
	}
	else if (obj2_x1 <= obj1_x1 && obj1_x1 <= obj2_x2) {
		if (obj1_y1 <= obj2_y1 && obj2_y1 <= obj1_y2) {
			return true;
		}
		else if (obj2_y1 <= obj1_y1 && obj1_y1 <= obj2_y2) {
			return true;
		}
		else return false;
	}
	else return false;
}
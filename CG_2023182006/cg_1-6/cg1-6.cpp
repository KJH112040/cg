#include <iostream>
#include <random>
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

float bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 1.0f;
typedef struct Rect {
	GLfloat x1, y1, x2, y2, r, g, b, size;
	bool check;
	int d_state;
}Rect;
Rect r[10];
int num, move_type = 1;

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLfloat> ps_uid(-1.0f, 0.65f), clr_uid(0.0f, 1.0f), size_uid(0.1f,0.35f);
std::uniform_int_distribution<int> cnt_uid(5, 10), way_uid(1,4);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
//void Motion(int x, int y);
GLvoid create_rect();
GLfloat move_x(int x, float move);
GLfloat move_y(int y, float move);
//bool Collision_detection(GLfloat obj1_x1, GLfloat obj1_y1, GLfloat obj1_x2, GLfloat obj1_y2, GLfloat obj2_x1, GLfloat obj2_y1, GLfloat obj2_x2, GLfloat obj2_y2);
void TimerFunction(int value);

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("6"); // ������ ����(������ �̸�)
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
	//glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(bgc_r, bgc_g, bgc_b, 1.0f); // ���� ��
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����
	for (int i = 0; i < num; ++i) {
		if (r[i].check) {
			if(r[i].d_state==0) {
				glColor3f(r[i].r, r[i].g, r[i].b);
				glRectf(r[i].x1, r[i].y1, r[i].x2, r[i].y2);
			}
			else if (r[i].d_state == 1) {		// 4���
				glColor3f(r[i].r, r[i].g, r[i].b);
				if (move_type == 1) {
					glRectf(r[i].x1, (r[i].y2 + r[i].y1) / 2 - r[i].size / 4, r[i].x1 + r[i].size / 2, (r[i].y2 + r[i].y1) / 2 + r[i].size / 4);
					glRectf(r[i].x2 - r[i].size / 2, (r[i].y2 + r[i].y1) / 2 - r[i].size / 4, r[i].x2, (r[i].y2 + r[i].y1) / 2 + r[i].size / 4);
					glRectf((r[i].x2 + r[i].x1) / 2 - r[i].size / 4, r[i].y1, (r[i].x2 + r[i].x1) / 2 + r[i].size / 4, r[i].y1 + r[i].size / 2);
					glRectf((r[i].x2 + r[i].x1) / 2 - r[i].size / 4, r[i].y2 - r[i].size / 2, (r[i].x2 + r[i].x1) / 2 + r[i].size / 4, r[i].y2);
				}
				else if (move_type == 2) {
					glRectf(r[i].x1, r[i].y1, r[i].x1 + r[i].size / 2, r[i].y1 + r[i].size / 2);
					glRectf(r[i].x2 - r[i].size / 2, r[i].y2 - r[i].size / 2, r[i].x2, r[i].y2);
					glRectf(r[i].x1, r[i].y2 - r[i].size / 2, r[i].x1 + r[i].size / 2, r[i].y2);
					glRectf(r[i].x2 - r[i].size / 2, r[i].y1, r[i].x2, r[i].y1 + r[i].size / 2);
				}
				else if (move_type == 3) {
					int way = way_uid(dre);
					switch (way)
					{
					case 1:
						glRectf(r[i].x1, (r[i].y2 + r[i].y1) / 2 - r[i].size / 2, r[i].x1 + r[i].size / 3, (r[i].y2 + r[i].y1) / 2 - r[i].size / 6);
						glRectf(r[i].x1, (r[i].y2 + r[i].y1) / 2 + r[i].size / 6, r[i].x1 + r[i].size / 3, (r[i].y2 + r[i].y1) / 2 + r[i].size / 2);
						glRectf(r[i].x1 + 2 * r[i].size / 3, (r[i].y2 + r[i].y1) / 2 - r[i].size / 2, r[i].x1 + r[i].size, (r[i].y2 + r[i].y1) / 2 - r[i].size / 6);
						glRectf(r[i].x1 + 2 * r[i].size / 3, (r[i].y2 + r[i].y1) / 2 + r[i].size / 6, r[i].x1 + r[i].size, (r[i].y2 + r[i].y1) / 2 + r[i].size / 2);
						break;
					case 2:
						glRectf(r[i].x2 - r[i].size / 3, (r[i].y2 + r[i].y1) / 2 - r[i].size / 2, r[i].x2, (r[i].y2 + r[i].y1) / 2 - r[i].size / 6);
						glRectf(r[i].x2 - r[i].size / 3, (r[i].y2 + r[i].y1) / 2 + r[i].size / 6, r[i].x2, (r[i].y2 + r[i].y1) / 2 + r[i].size / 2);
						glRectf(r[i].x2 - r[i].size, (r[i].y2 + r[i].y1) / 2 - r[i].size / 2, r[i].x2 - 2 * r[i].size / 3, (r[i].y2 + r[i].y1) / 2 - r[i].size / 6);
						glRectf(r[i].x2 - r[i].size, (r[i].y2 + r[i].y1) / 2 + r[i].size / 6, r[i].x2 - 2 * r[i].size / 3, (r[i].y2 + r[i].y1) / 2 + r[i].size / 2);
						break;
					case 3:
						glRectf((r[i].x2 + r[i].x1) / 2 - r[i].size / 2, r[i].y1, (r[i].x2 + r[i].x1) / 2 - r[i].size / 6, r[i].y1 + r[i].size / 3);
						glRectf((r[i].x2 + r[i].x1) / 2 + r[i].size / 6, r[i].y1, (r[i].x2 + r[i].x1) / 2 + r[i].size / 2, r[i].y1 + r[i].size / 3);
						glRectf((r[i].x2 + r[i].x1) / 2 - r[i].size / 2, r[i].y1 + 2 * r[i].size / 3, (r[i].x2 + r[i].x1) / 2 - r[i].size / 6, r[i].y1 + r[i].size);
						glRectf((r[i].x2 + r[i].x1) / 2 + r[i].size / 6, r[i].y1 + 2 * r[i].size / 3, (r[i].x2 + r[i].x1) / 2 + r[i].size / 2, r[i].y1 + r[i].size);
						break;
					case 4:
						glRectf((r[i].x2 + r[i].x1) / 2 - r[i].size / 2, r[i].y2, (r[i].x2 + r[i].x1) / 2 - r[i].size / 6, r[i].y2 - r[i].size / 3);
						glRectf((r[i].x2 + r[i].x1) / 2 + r[i].size / 6, r[i].y2, (r[i].x2 + r[i].x1) / 2 + r[i].size / 2, r[i].y2 - r[i].size / 3);
						glRectf((r[i].x2 + r[i].x1) / 2 - r[i].size / 2, r[i].y2 - r[i].size, (r[i].x2 + r[i].x1) / 2 - r[i].size / 6, r[i].y2 - 2 * r[i].size / 3);
						glRectf((r[i].x2 + r[i].x1) / 2 + r[i].size / 6, r[i].y2 - r[i].size, (r[i].x2 + r[i].x1) / 2 + r[i].size / 2, r[i].y2 - 2 * r[i].size / 3);
						break;
					}
				}
			}
			else if (r[i].d_state == 2) {		// 8���
				glRectf(r[i].x1, (r[i].y2 + r[i].y1) / 2 - r[i].size / 4, r[i].x1 + r[i].size / 2, (r[i].y2 + r[i].y1) / 2 + r[i].size / 4);
				glRectf(r[i].x2 - r[i].size / 2, (r[i].y2 + r[i].y1) / 2 - r[i].size / 4, r[i].x2, (r[i].y2 + r[i].y1) / 2 + r[i].size / 4);
				glRectf((r[i].x2 + r[i].x1) / 2 - r[i].size / 4, r[i].y1, (r[i].x2 + r[i].x1) / 2 + r[i].size / 4, r[i].y1 + r[i].size / 2);
				glRectf((r[i].x2 + r[i].x1) / 2 - r[i].size / 4, r[i].y2 - r[i].size / 2, (r[i].x2 + r[i].x1) / 2 + r[i].size / 4, r[i].y2);

				glRectf(r[i].x1, r[i].y1, r[i].x1 + r[i].size / 2, r[i].y1 + r[i].size / 2);
				glRectf(r[i].x2 - r[i].size / 2, r[i].y2 - r[i].size / 2, r[i].x2, r[i].y2);
				glRectf(r[i].x1, r[i].y2 - r[i].size / 2, r[i].x1 + r[i].size / 2, r[i].y2);
				glRectf(r[i].x2 - r[i].size / 2, r[i].y1, r[i].x2, r[i].y1 + r[i].size / 2);
			}
		}
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
	case '1':
		move_type = 1;
		break;
	case '2':
		move_type = 2;
		break;
	case '3':
		move_type = 3;
		break;
	case '4':
		move_type = 4;
		break;
	}
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		float px = ((float)(x - 400) / 400), py = ((float)(300 - y) / 300);
		for (int i = 0; i < num; ++i) {
			if((r[i].x1<=px&&px<=r[i].x2)&&(r[i].y1<=py&&py<=r[i].y2)) {
				if (r[i].check) {
					if (move_type == 4)r[i].d_state = 2;
					else r[i].d_state = 1;
					glutTimerFunc(100, TimerFunction, i);
				}
			}
		}
	}
	glutPostRedisplay();
}
//void Motion(int x, int y) {
//	glutPostRedisplay();
//}
void TimerFunction(int value){

	// Ư�� ����� �Ǿ��� �� Ÿ�̸� ���߰� �׳� �簢�� ���ֹ���
	if (r[value].size <= 0.05f) {
		r[value].check = false;
		value = -1;
	}
	else {
		r[value].size -= 0.05f;
		r[value].x1 -= 0.01f;
		r[value].y1 -= 0.01f;
		r[value].x2 += 0.01f;
		r[value].y2 += 0.01f;
	}
	glutPostRedisplay(); // ȭ�� �� ���
	if(value!=-1)glutTimerFunc(100, TimerFunction, value); // Ÿ�̸��Լ� �� ����
}
GLvoid create_rect() {
	num = cnt_uid(dre);
	for (int i = 0; i < num; ++i) {
		GLfloat px = ps_uid(dre), py = ps_uid(dre);
		r[i].size = size_uid(dre);
		r[i].x1 = px, r[i].x2 = px + r[i].size, r[i].y1 = py, r[i].y2 = py + r[i].size;
		r[i].r = clr_uid(dre), r[i].g = clr_uid(dre), r[i].b = clr_uid(dre);
		r[i].d_state = 0;
		r[i].check = true;
	}
}
GLfloat move_x(int x, float move) {
	return ((float)(x - 400) / 400) + move; // 400�� ȭ�� ���� ������ ��
}
GLfloat move_y(int y, float move) {
	return ((float)(300 - y) / 300) + move;
}
//bool Collision_detection(GLfloat obj1_x1, GLfloat obj1_y1, GLfloat obj1_x2, GLfloat obj1_y2, GLfloat obj2_x1, GLfloat obj2_y1, GLfloat obj2_x2, GLfloat obj2_y2) {
//	if (obj1_x1 <= obj2_x1 && obj2_x1 <= obj1_x2) {
//		if (obj1_y1 <= obj2_y1 && obj2_y1 <= obj1_y2) {
//			return true;
//		}
//		else if (obj2_y1 <= obj1_y1 && obj1_y1 <= obj2_y2) {
//			return true;
//		}
//		else return false;
//	}
//	else if (obj2_x1 <= obj1_x1 && obj1_x1 <= obj2_x2) {
//		if (obj1_y1 <= obj2_y1 && obj2_y1 <= obj1_y2) {
//			return true;
//		}
//		else if (obj2_y1 <= obj1_y1 && obj1_y1 <= obj2_y2) {
//			return true;
//		}
//		else return false;
//	}
//	else return false;
//}
#include <iostream>
#include <random>
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

float bgc_r = 0.3f, bgc_g = 0.3f, bgc_b = 0.3f;
int timer_value = 0, timer_value2=0;
typedef struct Shape {
	GLfloat x1, y1, x2, y2, r, g, b;
	bool check;
}Shape;
Shape sh[5],setting[5];
int EWSN[5] = { 1,1,1,1,1 };

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLfloat> clr_uid(0.4f, 1.0f),size_uid(-0.01f,0.01f);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
//void Motion(int x, int y);
void MoveShape_TimerFunction(int value);
void MoveShape2_TimerFunction(int value);

GLvoid draw_shape(GLfloat x, GLfloat y);
GLvoid remove_shape();
//bool back_shape(int i);
GLvoid change_clr();
GLvoid move_cross(int num, int way);
GLvoid move_zigzag(int num, int way);
GLvoid change_size();

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("1-4"); // ������ ����(������ �̸�)
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(bgc_r, bgc_g, bgc_b, 1.0f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����
	for (int i = 0; i < 5; ++i) {
		if(sh[i].check) {
			glColor3f(sh[i].r, sh[i].g, sh[i].b);
			glRectf(sh[i].x1, sh[i].y1, sh[i].x2, sh[i].y2);
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
	switch (key)
	{
	case '1':
		if (timer_value == 0)timer_value = 1;
		else if (timer_value == 1)timer_value = 0;
		glutTimerFunc(100, MoveShape_TimerFunction, timer_value);
		break;
	case '2':
		if (timer_value == 0)timer_value = 2;
		else if (timer_value == 2)timer_value = 0;
		glutTimerFunc(100, MoveShape_TimerFunction, timer_value);
		break;
	case '3':
		if (timer_value2 == 0)timer_value2 = 3;
		else if (timer_value2 == 3)timer_value2 = 0;
		glutTimerFunc(100, MoveShape2_TimerFunction, timer_value2);
		break;
	case '4':
		if (timer_value2 == 0)timer_value2 = 4;
		else if (timer_value2 == 4)timer_value2 = 0;
		glutTimerFunc(100, MoveShape2_TimerFunction, timer_value2);
		break;
	case 's':
		timer_value = 0;
		timer_value2 = 0;
		break;
	case 'm':
		for (int i = 0; i < 5; ++i) {
			if (sh[i].check) {
				sh[i] = setting[i];
			}
		}
		break;
	case 'r':
		remove_shape();
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		draw_shape(((GLfloat)(x-400)/400),((GLfloat)(300-y)/300));
	}
	glutPostRedisplay();
}
//void Motion(int x, int y)
//{
//	glutPostRedisplay();
//}
void MoveShape_TimerFunction(int value)
{
	switch (value)
	{
	case 1:
		for (int i = 0; i < 5; ++i) {
			move_cross(i,EWSN[i]);
		}
		break;
	case 2:
		for (int i = 0; i < 5; ++i) {
			move_zigzag(i, EWSN[i]);
		}
		break;
	}
	glutPostRedisplay(); // ȭ�� �� ���
	if(value!=0)glutTimerFunc(100, MoveShape_TimerFunction, timer_value); // Ÿ�̸��Լ� �� ����
}
void MoveShape2_TimerFunction(int value) {
	switch (value)
	{
	case 3:
		change_size();
		break;
	case 4:
		change_clr();
		break;
	}
	glutPostRedisplay(); // ȭ�� �� ���
	if (value != 0)glutTimerFunc(100, MoveShape2_TimerFunction, timer_value2); // Ÿ�̸��Լ� �� ����
}
GLvoid draw_shape(GLfloat x, GLfloat y) {
	for (int i = 0; i < 5; ++i) {
		if (sh[i].check==false) {
			sh[i].r = clr_uid(dre), sh[i].g = clr_uid(dre), sh[i].b = clr_uid(dre);
			if (x - 0.05f < -1.0f) {
				sh[i].x1 = -1.0f;
			}
			else sh[i].x1 = x - 0.05f;

			if (x + 0.05f > 1) {
				sh[i].x2 = 1.0f;
			}
			else sh[i].x2 = x + 0.05f;

			if (y - 0.05f < -1.0f) {
				sh[i].y1 = -1.0f;
			}
			else sh[i].y1 = y - 0.05f;

			if (y + 0.05f > 1) {
				sh[i].y2 = 1.0f;
			}
			else sh[i].y2 = y + 0.05f;
			sh[i].check = true;
			setting[i] = sh[i];
			break;
		}
	}
}
GLvoid remove_shape() {
	for (int i = 0; i < 5; ++i) {
		sh[i].x1 = 0.0f, sh[i].y1 = 0.0f, sh[i].x2 = 0.0f, sh[i].y2 = 0.0f, sh[i].r = 0.0f, sh[i].g = 0.0f, sh[i].b = 0.0f;
		sh[i].check = false;
		setting[i] = sh[i];
	}
}
//bool back_shape(int i) {			//���߿� �����غ���(�̵��Ͽ� ���ڸ� ���°�)
//	if (setting[i].x1 == sh[i].x1 && setting[i].y1 == sh[i].y1 && setting[i].x2 == sh[i].x2 && setting[i].y2 == sh[i].y2)return true;
//	else {
//		GLfloat a1 = (sh[i].y1 - setting[i].y1) / (sh[i].x1 - setting[i].x1);
//		GLfloat b1 = sh[i].y1 - sh[i].x1 * a1;
//		GLfloat a2 = (sh[i].y2 - setting[i].y2) / (sh[i].x2 - setting[i].x2);
//		GLfloat b2 = sh[i].y2 - sh[i].x2 * a2;
//
//		if (setting[i].x1 < sh[i].x1) {
//			sh[i].x1 -= 0.01f;
//			sh[i].y1 = a1 * sh[i].x1 + b1;
//		}
//		return false;
//	}
//}
GLvoid change_clr() {
	for (int i = 0; i < 5; ++i) {
		if (sh[i].check) {
			sh[i].r = clr_uid(dre), sh[i].g = clr_uid(dre), sh[i].b = clr_uid(dre);
		}
	}
}
GLvoid move_cross(int num, int way) {
	if (sh[num].check) {
		if (way==1) {
			if (sh[num].x2 >= 1)EWSN[num] = 2;
			else if(sh[num].y2 >= 1)EWSN[num] = 3;
			else {
				sh[num].x1 += 0.02;
				sh[num].x2 += 0.02;
				sh[num].y1 += 0.02;
				sh[num].y2 += 0.02;
			}
		}
		else if (way == 2) {
			if (sh[num].y2 >= 1)EWSN[num] = 3;
			else if(sh[num].x1 <= -1)EWSN[num] = 4;
			else {
				sh[num].x1 -= 0.02;
				sh[num].x2 -= 0.02;
				sh[num].y1 += 0.02;
				sh[num].y2 += 0.02;
			}
		}
		else if (way == 3) {
			if (sh[num].x1 <= -1)EWSN[num] = 4;
			else if (sh[num].y1 <= -1)EWSN[num] = 1;
			else {
				sh[num].x1 -= 0.02;
				sh[num].x2 -= 0.02;
				sh[num].y1 -= 0.02;
				sh[num].y2 -= 0.02;
			}
		}
		else if (way == 4) {
			if (sh[num].y1 <= -1)EWSN[num] = 1;
			else if (sh[num].x2 >= 1)EWSN[num] = 2;
			else {
				sh[num].x1 += 0.02;
				sh[num].x2 += 0.02;
				sh[num].y1 -= 0.02;
				sh[num].y2 -= 0.02;
			}
		}
	}
}
GLvoid move_zigzag(int num, int way) {
	if (sh[num].check) {
		if (way == 1) {
			if (sh[num].x2 >= 1)EWSN[num] = 2;
			else if (sh[num].y2 >= 1)EWSN[num] = 4;
			else {
				sh[num].x1 += 0.03;
				sh[num].x2 += 0.03;
				sh[num].y1 += 0.01;
				sh[num].y2 += 0.01;
			}
		}
		else if (way == 2) {
			if (sh[num].y2 >= 1)EWSN[num] = 3;
			else if (sh[num].x1 <= -1)EWSN[num] = 1;
			else {
				sh[num].x1 -= 0.03;
				sh[num].x2 -= 0.03;
				sh[num].y1 += 0.01;
				sh[num].y2 += 0.01;
			}
		}
		else if (way == 3) {
			if (sh[num].x1 <= -1)EWSN[num] = 4;
			else if (sh[num].y1 <= -1)EWSN[num] = 2;
			else {
				sh[num].x1 -= 0.03;
				sh[num].x2 -= 0.03;
				sh[num].y1 -= 0.01;
				sh[num].y2 -= 0.01;
			}
		}
		else if (way == 4) {
			if (sh[num].y1 <= -1)EWSN[num] = 1;
			else if (sh[num].x2 >= 1)EWSN[num] = 3;
			else {
				sh[num].x1 += 0.03;
				sh[num].x2 += 0.03;
				sh[num].y1 -= 0.01;
				sh[num].y2 -= 0.01;
			}
		}
	}
}
GLvoid change_size() {
	for (int i = 0; i < 5; ++i) {
		if (sh[i].check) {
			GLfloat a = size_uid(dre);
			sh[i].x1 -= a;
			sh[i].x2 += a;
			sh[i].y1 -= a;
			sh[i].y2 += a;
		}
	}
}
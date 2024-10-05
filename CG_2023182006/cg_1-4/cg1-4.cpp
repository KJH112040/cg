#include <iostream>
#include <random>
#include <gl/glew.h> // 필요한 헤더파일 include
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

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("1-4"); // 윈도우 생성(윈도우 이름)
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutMainLoop(); // 이벤트 처리 시작
}
GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(bgc_r, bgc_g, bgc_b, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현
	for (int i = 0; i < 5; ++i) {
		if(sh[i].check) {
			glColor3f(sh[i].r, sh[i].g, sh[i].b);
			glRectf(sh[i].x1, sh[i].y1, sh[i].x2, sh[i].y2);
		}
	}
	//--- 그리기 관련 부분이 여기에 포함된다.
	glutSwapBuffers(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
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
	glutPostRedisplay(); // 화면 재 출력
	if(value!=0)glutTimerFunc(100, MoveShape_TimerFunction, timer_value); // 타이머함수 재 설정
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
	glutPostRedisplay(); // 화면 재 출력
	if (value != 0)glutTimerFunc(100, MoveShape2_TimerFunction, timer_value2); // 타이머함수 재 설정
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
//bool back_shape(int i) {			//나중에 도전해보기(이동하여 제자리 가는거)
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
#include <iostream>
#include <random>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void RandomTimerFunction(int value);
typedef struct Rect {
	bool check = false;
	GLfloat x1=0, y1=0, x2=0, y2=0, r=0, g=0, b=0;
}Rect;
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLfloat> pos_uid(-1, 0.8),clr_uid(0.0f,1.0f);
float bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 1.0f;
Rect rect[10];
void Create_rect();
int rect_cnt = 0,select_rect = -1;
bool lbutton = false;
GLfloat dx1, dx2, dy1, dy2;
void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("1-2"); // 윈도우 생성(윈도우 이름)
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
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutMainLoop(); // 이벤트 처리 시작
}
GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(bgc_r, bgc_g, bgc_b, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현
	for (int i = 0; i < 10; ++i) {
		if(rect[i].check) {
			glColor3f(rect[i].r, rect[i].g, rect[i].b);
			glRectf(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
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
	case 'a':
		Create_rect();
		break;
	}
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 0; i < 10; ++i) {
			if (400 * (rect[i].x1 + 1) < x && x < 400 * (rect[i].x2 + 1) && 300 * (1 - rect[i].y2) < y && y < 300 * (1 - rect[i].y1)) {
				select_rect = i;
			}
		}
		if(select_rect!=-1)
		{
			dx1 = ((float)(x - 400) / 400) - rect[select_rect].x1;
			dx2 = rect[select_rect].x2 - ((float)(x - 400) / 400);
			dy1 = ((float)(300 - y) / 300) - rect[select_rect].y1;
			dy2 = rect[select_rect].y2 - ((float)(300 - y) / 300);
		}
		lbutton = true;
	}
	else if (state == GLUT_UP) {
		if (select_rect != -1) {
			select_rect = -1;
		}
		lbutton = false;
	}
	glutPostRedisplay();
}
void Motion(int x, int y)
{
	if (lbutton) {
		std::cout << "이동중\n";
		if(select_rect!=-1){
			if (-1 <= rect[select_rect].x1 && rect[select_rect].x2 <= 1 && -1 <= rect[select_rect].y1 && rect[select_rect].y2 <= 1) {
				if(0<=x&&x<=800&&0<=y&&y<=600){
					rect[select_rect].x1 = ((float)(x - 400) / 400) - dx1;
					rect[select_rect].x2 = dx2 + ((float)(x - 400) / 400);
					rect[select_rect].y1 = ((float)(300 - y) / 300) - dy1;
					rect[select_rect].y2 = dy2 + ((float)(300 - y) / 300);
				}
			}
			else {
				lbutton = false;
				if (-1 >= rect[select_rect].x1) {
					rect[select_rect].x1 += 0.03;
					rect[select_rect].x2 += 0.03;
				}
				else if (rect[select_rect].x2 >= 1) {
					rect[select_rect].x1 -= 0.03;
					rect[select_rect].x2 -= 0.03;
				}

				if (-1 >= rect[select_rect].y1) {
					rect[select_rect].y1 += 0.03;
					rect[select_rect].y2 += 0.03;
				}
				else if (rect[select_rect].y2 >= 1) {
					rect[select_rect].y1 -= 0.03;
					rect[select_rect].y2 -= 0.03;
				}
			}
		}
	}
	glutPostRedisplay();
}
void Create_rect() {
	if (rect_cnt == 10) {
		std::cout << "첫 번째 사각형 제거\n";
		for (int i = 0; i < 9; ++i) {
			rect[i] = rect[i + 1];
		}
		rect[9].check = false;
		--rect_cnt;
	}
	
	for (int i = 0; i < 10; ++i) {
		if (rect[i].check == false) {
			GLfloat px = pos_uid(dre), py = pos_uid(dre);
			rect[i].x1 = px, rect[i].x2 = px + 0.2, rect[i].y1 = py, rect[i].y2 = py + 0.2;
			rect[i].r = clr_uid(dre), rect[i].g = clr_uid(dre), rect[i].b = clr_uid(dre);
			rect[i].check = true;
			++rect_cnt;
			break;
		}
	}
}
void RandomTimerFunction(int value)
{
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, RandomTimerFunction, 1); // 타이머함수 재 설정
}
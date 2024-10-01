#include <iostream>
#include <random>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void RandomTimerFunction(int value);
typedef struct Rect {
	GLfloat x1, y1, x2, y2, r, g, b;
}Rect;
Rect Zoom_InOut(int x, int y, Rect r);
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLfloat> uid(0.0f, 1.0f);
float bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 1.0f;
Rect rect[4] = { {-1,0,0,1,uid(dre),uid(dre),uid(dre)},{0,0,1,1,uid(dre),uid(dre),uid(dre)},
				{-1,-1,0,0,uid(dre),uid(dre),uid(dre)},{0,-1,1,0,uid(dre),uid(dre),uid(dre)} };
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
	//glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutMainLoop(); // 이벤트 처리 시작
}
GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(bgc_r, bgc_g, bgc_b, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현
	for (int i = 0; i < 4; ++i) {
		glColor3f(rect[i].r, rect[i].g, rect[i].b);
		glRectf(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
	}
	//--- 그리기 관련 부분이 여기에 포함된다.
	glutSwapBuffers(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{	glViewport(0, 0, w, h);
}
void Keyboard(unsigned char key, int x, int y)
{
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		std::cout << "좌클릭 마우스 위치: " << x << "," << y << '\n';
		if (400 * (rect[0].x1 + 1) < x && x < 400 * (rect[0].x2 + 1) && 300 * (1 - rect[0].y2) < y && y < 300 * (1 - rect[0].y1)) {
			rect[0].r = uid(dre), rect[0].g = uid(dre), rect[0].b = uid(dre);
		}
		else if (400 * (rect[1].x1 + 1) < x && x < 400 * (rect[1].x2 + 1) && 300 * (1 - rect[1].y2) < y && y < 300 * (1 - rect[1].y1)) {
			rect[1].r = uid(dre), rect[1].g = uid(dre), rect[1].b = uid(dre);
		}
		else if (400 * (rect[2].x1 + 1) < x && x < 400 * (rect[2].x2 + 1) && 300 * (1 - rect[2].y2) < y && y < 300 * (1 - rect[2].y1)) {
			rect[2].r = uid(dre), rect[2].g = uid(dre), rect[2].b = uid(dre);
		}
		else if (400 * (rect[3].x1 + 1) < x && x < 400 * (rect[3].x2 + 1) && 300 * (1 - rect[3].y2) < y && y < 300 * (1 - rect[3].y1)) {
			rect[3].r = uid(dre), rect[3].g = uid(dre), rect[3].b = uid(dre);
		}
	}
	else if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) {
		std::cout << "우클릭 마우스 위치: " << x << "," << y << '\n';
		if (0 < x && x < 400 && 0 < y && y < 300) {
			rect[0] = Zoom_InOut(x, y, rect[0]);
		}
		else if (400 < x && x < 800 && 0 < y && y < 300) {
			rect[1] = Zoom_InOut(x, y, rect[1]);
		}
		else if (0 < x && x < 400 && 300 < y && y < 600) {
			rect[2] = Zoom_InOut(x, y, rect[2]);
		}
		else if (400 < x && x < 800 && 300 < y && y < 600) {
			rect[3] = Zoom_InOut(x, y, rect[3]);
		}
	}
	glutPostRedisplay();
}
void RandomTimerFunction(int value)
{
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, RandomTimerFunction, 1); // 타이머함수 재 설정
}
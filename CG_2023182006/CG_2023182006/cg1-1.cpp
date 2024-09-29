#include <iostream>
#include <random>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void RandomTimerFunction(int value);
float bgc_r=1.0f, bgc_g=1.0f, bgc_b=1.0f;
int timer_OnOff = 0;

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> uid(0, 4);

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("1-1"); // 윈도우 생성(윈도우 이름)
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
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutMainLoop(); // 이벤트 처리 시작
}
GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(bgc_r, bgc_g, bgc_b, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현
	//--- 그리기 관련 부분이 여기에 포함된다.
	glutSwapBuffers(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{	glViewport(0, 0, w, h);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'c':
		bgc_r = 0.0f, bgc_g = 1.0f, bgc_b = 1.0f;
		break;
	case 'm':
		bgc_r = 1.0f, bgc_g = 0.0f, bgc_b = 1.0f;
		break;
	case 'y':
		bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 0.0f;
		break;
	case 'a':
		if(uid(dre)==0)bgc_r = 0.0f, bgc_g = 1.0f, bgc_b = 1.0f;
		else if(uid(dre)==1)bgc_r = 1.0f, bgc_g = 0.0f, bgc_b = 1.0f;
		else if(uid(dre)==2)bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 0.0f;
		else if(uid(dre)==3)bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 1.0f;
		else if(uid(dre)==4)bgc_r = 0.0f, bgc_g = 0.0f, bgc_b = 0.0f;
		break;
	case 'w':
		bgc_r = 256.0f, bgc_g = 256.0f, bgc_b = 256.0f;
		break;
	case 'k':
		bgc_r = 0.0f, bgc_g = 0.0f, bgc_b = 0.0f;
		break;
	case 't':
		timer_OnOff = 1;
		glutTimerFunc(100, RandomTimerFunction, timer_OnOff);
		break;
	case 's':
		timer_OnOff = 0;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}
void RandomTimerFunction(int value)
{
	if (uid(dre) == 0)bgc_r = 0.0f, bgc_g = 1.0f, bgc_b = 1.0f;
	else if (uid(dre) == 1)bgc_r = 1.0f, bgc_g = 0.0f, bgc_b = 1.0f;
	else if (uid(dre) == 2)bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 0.0f;
	else if (uid(dre) == 3)bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 1.0f;
	else if (uid(dre) == 4)bgc_r = 0.0f, bgc_g = 0.0f, bgc_b = 0.0f;
	glutPostRedisplay(); // 화면 재 출력
	if (value==1)glutTimerFunc(100, RandomTimerFunction, timer_OnOff); // 타이머함수 재 설정
}
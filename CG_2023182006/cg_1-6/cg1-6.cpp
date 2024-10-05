#include <iostream>
#include <random>
#include <gl/glew.h> // 필요한 헤더파일 include
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

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("6"); // 윈도우 생성(윈도우 이름)
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW Initialized\n";
	create_rect();
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutMainLoop(); // 이벤트 처리 시작
}
GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(bgc_r, bgc_g, bgc_b, 1.0f); // 바탕 색
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현
	for (int i = 0; i < num; ++i) {
		if (r[i].check) {
			if(r[i].d_state==0) {
				glColor3f(r[i].r, r[i].g, r[i].b);
				glRectf(r[i].x1, r[i].y1, r[i].x2, r[i].y2);
			}
			else if (r[i].d_state == 1) {		// 4등분
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
			else if (r[i].d_state == 2) {		// 8등분
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
	//--- 그리기 관련 부분이 여기에 포함된다.
	glutSwapBuffers(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
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

	// 특정 사이즈가 되었을 때 타이머 멈추고 그냥 사각형 없애버려
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
	glutPostRedisplay(); // 화면 재 출력
	if(value!=-1)glutTimerFunc(100, TimerFunction, value); // 타이머함수 재 설정
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
	return ((float)(x - 400) / 400) + move; // 400은 화면 가로 길이의 반
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
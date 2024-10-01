#include <iostream>
#include <random>
#include <gl/glew.h> // �ʿ��� ������� include
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
void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("1-2"); // ������ ����(������ �̸�)
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
	//glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(bgc_r, bgc_g, bgc_b, 1.0f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����
	for (int i = 0; i < 4; ++i) {
		glColor3f(rect[i].r, rect[i].g, rect[i].b);
		glRectf(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
	}
	//--- �׸��� ���� �κ��� ���⿡ ���Եȴ�.
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{	glViewport(0, 0, w, h);
}
void Keyboard(unsigned char key, int x, int y)
{
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		std::cout << "��Ŭ�� ���콺 ��ġ: " << x << "," << y << '\n';
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
		std::cout << "��Ŭ�� ���콺 ��ġ: " << x << "," << y << '\n';
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
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, RandomTimerFunction, 1); // Ÿ�̸��Լ� �� ����
}
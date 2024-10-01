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
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLfloat> uid(0.0f, 1.0f);
float bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 1.0f;
Rect rect[4] = { {-1.0f,0.0f,0.0f,1.0f,uid(dre),uid(dre),uid(dre)},{0,0,1,1,uid(dre),uid(dre),uid(dre)},
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
		glRectf(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
		glColor3f(rect[i].r, rect[i].g, rect[i].b);
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
		std::cout << "��Ŭ�� ���콺 ��ġ: "<<x<<","<<y<<'\n';
	}
	else if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) {
		std::cout << "��Ŭ�� ���콺 ��ġ: " << x << "," << y << '\n';
	}
	glutPostRedisplay();
}
void RandomTimerFunction(int value)
{
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, RandomTimerFunction, 1); // Ÿ�̸��Լ� �� ����
}
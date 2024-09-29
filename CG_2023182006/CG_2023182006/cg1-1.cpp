#include <iostream>
#include <random>
#include <gl/glew.h> // �ʿ��� ������� include
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

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("1-1"); // ������ ����(������ �̸�)
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
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(bgc_r, bgc_g, bgc_b, 1.0f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����
	//--- �׸��� ���� �κ��� ���⿡ ���Եȴ�.
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
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
	glutPostRedisplay(); // ȭ�� �� ���
	if (value==1)glutTimerFunc(100, RandomTimerFunction, timer_OnOff); // Ÿ�̸��Լ� �� ����
}
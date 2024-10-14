#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <random>
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

float bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 1.0f;
GLint width, height;
GLuint shaderProgramID; //--- ���̴� ���α׷� �̸�
GLuint vertexShader; //--- ���ؽ� ���̴� ��ü
GLuint fragmentShader; //--- �����׸�Ʈ ���̴� ��üGLuint vbo[2], vao[10];GLfloat vertex_data[4][3], colors[4][3];char c[10];int cnt = 0;
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLfloat> ps_uid(-1.0f, 0.65f), clr_uid(0.0f, 1.0f), size_uid(0.1f, 0.35f);
std::uniform_int_distribution<int> random_select_shape_uid(0, 1);

GLchar* vertexSource; //--- ���̴� �ڵ� ������ ���ڿ�
//--- ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�
//--- filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
char* filetobuf(const char* file);

//--- �Ʒ� 5�� �Լ��� ����� ���� �Լ� ��
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void InitBuffer(int);
void Keyboard(unsigned char key, int x, int y);
//void Mouse(int button, int state, int x, int y);
//void Motion(int x, int y);
//GLvoid create_rect();
//GLfloat move_x(int x, float move);
//GLfloat move_y(int y, float move);
//bool Collision_detection(GLfloat obj1_x1, GLfloat obj1_y1, GLfloat obj1_x2, GLfloat obj1_y2, GLfloat obj2_x1, GLfloat obj2_y1, GLfloat obj2_x2, GLfloat obj2_y2);
//void TimerFunction(int value);

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("7"); // ������ ����(������ �̸�)
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW Initialized\n";

	//--- ���̴� �о�ͼ� ���̴� ���α׷� �����
	make_shaderProgram();

	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	//glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(bgc_r, bgc_g, bgc_b, 1.0f); // ���� ��
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	glUseProgram(shaderProgramID);
	glPointSize(5.0);
	//--- ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(shaderProgramID);
	// �׸��� �κ� ����
	//--- ����� VAO �ҷ�����
	for (int i = 0; i < 10;++i) {
		glBindVertexArray(vao[i]);
		switch (c[i])
		{
		case 'p':
			break;
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
	float px = (float)(x - 400) / 400, py = (float)(300 - y) / 300;
	float r = clr_uid(dre), g = clr_uid(dre), b = clr_uid(dre);
	for (int i = 0; i < 4;++i) {
		colors[i][0] = r, colors[i][1] = g, colors[i][2] = b;
	}

	if (cnt < 10) {
		switch (key)
		{
		case 'p':
			vertex_data[0][0] = px, vertex_data[0][1] = py, vertex_data[0][2] = 0;
			InitBuffer(cnt);
			c[cnt] = 'p';
			break;
		case 'l':
			vertex_data[0][0] = px - 0.05, vertex_data[0][1] = py, vertex_data[0][2] = 0;
			vertex_data[1][0] = px + 0.05, vertex_data[1][1] = py, vertex_data[1][2] = 0;
			InitBuffer(cnt);
			c[cnt] = 'l';
			break;
		case 't':
			vertex_data[0][0] = px - 0.05, vertex_data[0][1] = py - 0.05, vertex_data[0][2] = 0;
			vertex_data[1][0] = px, vertex_data[1][1] = py + 0.05, vertex_data[1][2] = 0;
			vertex_data[2][0] = px + 0.05, vertex_data[2][1] = py - 0.05, vertex_data[2][2] = 0;
			InitBuffer(cnt);
			c[cnt] = 't';
			break;
		case 'r':
			vertex_data[0][0] = px - 0.05, vertex_data[0][1] = py - 0.05, vertex_data[0][2] = 0;
			vertex_data[1][0] = px - 0.05, vertex_data[1][1] = py + 0.05, vertex_data[1][2] = 0;
			vertex_data[2][0] = px + 0.05, vertex_data[2][1] = py - 0.05, vertex_data[2][2] = 0;
			vertex_data[3][0] = px + 0.05, vertex_data[3][1] = py + 0.05, vertex_data[3][2] = 0;
			InitBuffer(cnt);
			c[cnt] = 'r';
			break;
		};
	}
	switch(key){
	case 'w':
		//move_up();
		break;
	case 'a':
		//move_left();
		break;
	case 's':
		//move_down();
		break;
	case 'd':
		//move_right();
		break;
	case 'c':
		//remove_shape();
		break;
	}
	glutPostRedisplay();
}
//--- ���ؽ� ���̴� ��ü �����
void make_vertexShaders()
{
	GLchar* vertexSource;
	//--- ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�
	//--- filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
	vertexSource = filetobuf("Vertex_Shader.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if(!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}
//--- �����׸�Ʈ ���̴� ��ü �����
void make_fragmentShaders()
{
	GLchar* fragmentSource;
	//--- �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
	fragmentSource = filetobuf("Fragment_Shader.glsl"); // �����׼��̴� �о����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}
//--- ���̴� ���α׷� ����� ���̴� ��ü ��ũ�ϱ�
GLuint make_shaderProgram()
{
	make_vertexShaders();
	make_fragmentShaders();

	shaderProgramID = glCreateProgram();

	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ������� ������ ���� ���
	GLint result;
	GLchar errorLog[512];
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderProgramID, 512, NULL, errorLog);
		std::cerr << "ERROR:shader program ���� ����\n" << errorLog << std::endl;
		return false;
	}	return shaderProgramID;}void InitBuffer(int index) {	if (cnt < 10)	{		glGenVertexArrays(1, &vao[index]); //--- VAO �� �����ϰ� �Ҵ��ϱ�
		glBindVertexArray(vao[index]); //--- VAO�� ���ε��ϱ�
		glGenBuffers(2, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
		//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		//--- ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
		//--- triShape �迭�� ������: 9 * float
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), vertex_data, GL_STATIC_DRAW);
		//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute �ε��� 0���� ��밡���ϰ� ��
		glEnableVertexAttribArray(0);
		//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		//--- ���� colors���� ���ؽ� ������ �����Ѵ�.
		//--- colors �迭�� ������: 9 *float 
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
		//--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute �ε��� 1���� ��� �����ϰ� ��.
		glEnableVertexAttribArray(1);		++cnt;	}}char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading 
	if (!fptr) // Return NULL on failure 
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
	length = ftell(fptr); // Find out how many bytes into the file we are 
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
	fclose(fptr); // Close the file 
	buf[length] = 0; // Null terminator 
	return buf; // Return the buffer 
};
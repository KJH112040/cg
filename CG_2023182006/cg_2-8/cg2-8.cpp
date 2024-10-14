#define _CRT_SECURE_NO_WARNINGS 
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <stdio.h>
GLfloat vertex_data[36][3];
GLfloat colors[36][3];
GLuint vao, vbo[2];
bool triangle_full = true;
int check[12][2]; // T(1)�Ǵ�F(0), ��и� ǥ��(1:���,2:�»�,3:����,4:����)
/* 2 1
   3 4*/
float bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 1.0f;
GLint width, height;
GLuint shaderProgramID; //--- ���̴� ���α׷� �̸�
GLuint vertexShader; //--- ���ؽ� ���̴� ��ü
GLuint fragmentShader; //--- �����׸�Ʈ ���̴� ��ü
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLfloat> ps_uid(-1.0f, 1.0f), clr_uid(0.0f, 1.0f), size_uid(0.1f, 0.35f);

//--- filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
char* filetobuf(const char* file);

//--- �Ʒ� 5�� �Լ��� ����� ���� �Լ� ��
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void InitBuffer();
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
//void Motion(int x, int y);
//void TimerFunction(int value);

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("8"); // ������ ����(������ �̸�)
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW Initialized\n";

	//--- ���̴� �о�ͼ� ���̴� ���α׷� �����
	for (int i = 0; i < 4; ++i) {
		int a = i * 3;
		colors[a][0] = clr_uid(dre), colors[a][1] = clr_uid(dre), colors[a][2] = clr_uid(dre);
		colors[a+1][0] = clr_uid(dre), colors[a+1][1] = clr_uid(dre), colors[a+1][2] = clr_uid(dre);
		colors[a+2][0] = clr_uid(dre), colors[a+2][1] = clr_uid(dre), colors[a+2][2] = clr_uid(dre);
		if (i == 0) {
			vertex_data[0][0] = -0.65f, vertex_data[0][1] = 0.325f;
			vertex_data[1][0] = -0.45f, vertex_data[1][1] = 0.325f;
			vertex_data[2][0] = -0.55f, vertex_data[2][1] = 0.725f;
			check[i][1] = 2;
		}
		else if (i == 1) {
			vertex_data[3][0] = 0.45f, vertex_data[3][1] = 0.325f;
			vertex_data[4][0] = 0.65f, vertex_data[4][1] = 0.325f;
			vertex_data[5][0] = 0.55f, vertex_data[5][1] = 0.725f;
			check[i][1] = 1;
		}
		else if (i == 2) {
			vertex_data[6][0] = -0.65f, vertex_data[6][1] = -0.725f;
			vertex_data[7][0] = -0.45f, vertex_data[7][1] = -0.725f;
			vertex_data[8][0] = -0.55f, vertex_data[8][1] = -0.325f;
			check[i][1] = 3;
		}
		else if (i == 3) {
			vertex_data[9][0] = 0.45f, vertex_data[9][1] = -0.725f;
			vertex_data[10][0] = 0.65f, vertex_data[10][1] = -0.725f;
			vertex_data[11][0] = 0.55f, vertex_data[11][1] = -0.325f;
			check[i][1] = 4;
		}
		check[i][0] = 1;
		make_shaderProgram();
	}
	
//	InitBuffer();

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
	glBindVertexArray(vao);
	for(int i = 0; i < 12;++i) {
		if(check[i][0]==1) {
			if (triangle_full)glDrawArrays(GL_TRIANGLES, i * 3, 3);
			else glDrawArrays(GL_LINE_LOOP, i * 3, 3);
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
	float cur_x = (float)(x - 400) / 400, cur_y = (float)(300 - y) / 300;
	switch (key) {
	case 'a':
		// ��
		triangle_full = true;
		break;
	case 'b':
		// ��
		triangle_full = false;
		break;
	}
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y) {
	float cur_x = (float)(x - 400) / 400, cur_y = (float)(300 - y) / 300;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

	}
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
	if (!result)
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
	InitBuffer();
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
	}	return shaderProgramID;}void InitBuffer() {	glGenVertexArrays(1, &vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glBindVertexArray(vao); //--- VAO�� ���ε��ϱ�
	glGenBuffers(2, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//--- ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	//--- triShape �迭�� ������: 9 * float
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute �ε��� 0���� ��밡���ϰ� ��
	glEnableVertexAttribArray(0);
	//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- ���� colors���� ���ؽ� ������ �����Ѵ�.
	//--- colors �迭�� ������: 9 *float 
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	//--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute �ε��� 1���� ��� �����ϰ� ��.
	glEnableVertexAttribArray(1);}char* filetobuf(const char* file)
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
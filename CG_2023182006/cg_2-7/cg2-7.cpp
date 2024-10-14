#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <random>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

float bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 1.0f;
GLint width, height;
GLuint shaderProgramID; //--- 세이더 프로그램 이름
GLuint vertexShader; //--- 버텍스 세이더 객체
GLuint fragmentShader; //--- 프래그먼트 세이더 객체GLuint vbo[2], vao[10];GLfloat vertex_data[4][3], colors[4][3];char c[10];int cnt = 0;
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLfloat> ps_uid(-1.0f, 0.65f), clr_uid(0.0f, 1.0f), size_uid(0.1f, 0.35f);
std::uniform_int_distribution<int> random_select_shape_uid(0, 1);

GLchar* vertexSource; //--- 세이더 코드 저장할 문자열
//--- 버텍스 세이더 읽어 저장하고 컴파일 하기
//--- filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수
char* filetobuf(const char* file);

//--- 아래 5개 함수는 사용자 정의 함수 임
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

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("7"); // 윈도우 생성(윈도우 이름)
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW Initialized\n";

	//--- 세이더 읽어와서 세이더 프로그램 만들기
	make_shaderProgram();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	//glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutMainLoop(); // 이벤트 처리 시작
}
GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(bgc_r, bgc_g, bgc_b, 1.0f); // 바탕 색
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	glUseProgram(shaderProgramID);
	glPointSize(5.0);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(shaderProgramID);
	// 그리기 부분 구현
	//--- 사용할 VAO 불러오기
	for (int i = 0; i < 10;++i) {
		glBindVertexArray(vao[i]);
		switch (c[i])
		{
		case 'p':
			break;
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
//--- 버텍스 세이더 객체 만들기
void make_vertexShaders()
{
	GLchar* vertexSource;
	//--- 버텍스 세이더 읽어 저장하고 컴파일 하기
	//--- filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수
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
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}
//--- 프래그먼트 세이더 객체 만들기
void make_fragmentShaders()
{
	GLchar* fragmentSource;
	//--- 프래그먼트 세이더 읽어 저장하고 컴파일하기
	fragmentSource = filetobuf("Fragment_Shader.glsl"); // 프래그세이더 읽어오기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}
//--- 세이더 프로그램 만들고 세이더 객체 링크하기
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

	// 연결되지 않으면 오류 출력
	GLint result;
	GLchar errorLog[512];
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderProgramID, 512, NULL, errorLog);
		std::cerr << "ERROR:shader program 연결 실패\n" << errorLog << std::endl;
		return false;
	}	return shaderProgramID;}void InitBuffer(int index) {	if (cnt < 10)	{		glGenVertexArrays(1, &vao[index]); //--- VAO 를 지정하고 할당하기
		glBindVertexArray(vao[index]); //--- VAO를 바인드하기
		glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기
		//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		//--- 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
		//--- triShape 배열의 사이즈: 9 * float
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), vertex_data, GL_STATIC_DRAW);
		//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute 인덱스 0번을 사용가능하게 함
		glEnableVertexAttribArray(0);
		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		//--- 변수 colors에서 버텍스 색상을 복사한다.
		//--- colors 배열의 사이즈: 9 *float 
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
		//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute 인덱스 1번을 사용 가능하게 함.
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
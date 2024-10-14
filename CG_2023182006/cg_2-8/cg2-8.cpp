#define _CRT_SECURE_NO_WARNINGS 
#include <gl/glew.h> // 필요한 헤더파일 include
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
int check[12][2]; // T(1)또는F(0), 사분면 표시(1:우상,2:좌상,3:좌하,4:우하)
/* 2 1
   3 4*/
float bgc_r = 1.0f, bgc_g = 1.0f, bgc_b = 1.0f;
GLint width, height;
GLuint shaderProgramID; //--- 세이더 프로그램 이름
GLuint vertexShader; //--- 버텍스 세이더 객체
GLuint fragmentShader; //--- 프래그먼트 세이더 객체
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLfloat> ps_uid(-1.0f, 1.0f), clr_uid(0.0f, 1.0f), size_uid(0.1f, 0.35f);

//--- filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수
char* filetobuf(const char* file);

//--- 아래 5개 함수는 사용자 정의 함수 임
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

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("8"); // 윈도우 생성(윈도우 이름)
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW Initialized\n";

	//--- 세이더 읽어와서 세이더 프로그램 만들기
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
	glBindVertexArray(vao);
	for(int i = 0; i < 12;++i) {
		if(check[i][0]==1) {
			if (triangle_full)glDrawArrays(GL_TRIANGLES, i * 3, 3);
			else glDrawArrays(GL_LINE_LOOP, i * 3, 3);
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
	float cur_x = (float)(x - 400) / 400, cur_y = (float)(300 - y) / 300;
	switch (key) {
	case 'a':
		// 면
		triangle_full = true;
		break;
	case 'b':
		// 선
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
	if (!result)
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
	InitBuffer();
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
	}	return shaderProgramID;}void InitBuffer() {	glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(vao); //--- VAO를 바인드하기
	glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기
	//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//--- 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
	//--- triShape 배열의 사이즈: 9 * float
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 0번을 사용가능하게 함
	glEnableVertexAttribArray(0);
	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- 변수 colors에서 버텍스 색상을 복사한다.
	//--- colors 배열의 사이즈: 9 *float 
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 1번을 사용 가능하게 함.
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
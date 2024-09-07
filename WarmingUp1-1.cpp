#include <iostream>
#include <random>
using namespace std;

random_device rd;
default_random_engine d(rd());
uniform_int_distribution<int> uid1(0, 2),uid2(0,1);

int main() {
	
	// 1. 행렬 다루기

	int matrix1[4][4],matrix2[4][4],cnt1=0,cnt2=0;
	for (int row = 0; row < 4; ++row) {						//행 row
		for (int column = 0; column < 4; ++column) {		//열 column
			if (cnt1 == 2 && cnt2 == 2) {
				matrix1[row][column] = uid2(d);
				matrix2[row][column] = uid2(d);
			}
			else if (cnt1 == 2) {
				matrix1[row][column] = uid2(d);
				matrix2[row][column] = uid1(d);
				if (matrix2[row][column] == 2)++cnt2;
			}
			else if (cnt2 == 2) {
				matrix1[row][column] = uid1(d);
				matrix2[row][column] = uid2(d);
				if (matrix1[row][column] == 2)++cnt1;
			}
			else {
				matrix1[row][column] = uid1(d);
				matrix2[row][column] = uid1(d);
				if (matrix1[row][column] == 2)++cnt1;
				if (matrix2[row][column] == 2)++cnt2;
			}
		}
	}

	for (int i = 0; i < 4; ++i) {
		if (i == 0)cout << "행렬1";
		cout<<"	|";
		for (int j = 0; j < 4; ++j) {
			cout << matrix1[i][j] <<"	";
		}
		cout << "|";
		if (i == 0)cout << "	행렬2	|";
		else cout << "		|";
		for (int j = 0; j < 4; ++j) {
			cout << matrix2[i][j] << "	";
		}
		cout << "|\n";
	}

	bool p = false, s = false; //짝홀
	cout << "\n명령어 입력:";
	while (1) {
		int result_matrix[4][4] = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} },cnt1=0,cnt2=0;
		char cmd;
		cin >> cmd;
		switch (cmd)
		{
		case 'm':
		{	// 행렬의 곱셈
			system("cls");
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n결과\n";
			for (int rMatR = 0; rMatR < 4; ++rMatR) {
				for (int rMatC = 0; rMatC < 4; ++rMatC) {
					for (int i = 0; i < 4; ++i) {
						result_matrix[rMatR][rMatC] = result_matrix[rMatR][rMatC] + (matrix1[rMatR][i] * matrix2[i][rMatC]);
					}
				}
			}
			for (int i = 0; i < 4; ++i) {
				cout << "|";
				for (int j = 0; j < 4; ++j) {
					cout << result_matrix[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n명령어 입력:";
		}
			break;
		case 'a':
		{	// 행렬의 덧셈
			system("cls");
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n결과\n";
			for (int rMatR = 0; rMatR < 4; ++rMatR) {
				for (int rMatC = 0; rMatC < 4; ++rMatC) {
					result_matrix[rMatR][rMatC] = matrix1[rMatR][rMatC] + matrix2[rMatR][rMatC];
				}
			}
			for (int i = 0; i < 4; ++i) {
				cout << "|";
				for (int j = 0; j < 4; ++j) {
					cout << result_matrix[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n명령어 입력:";
		}
			break;
		case 'd':
		{	// 행렬의 뺄셈
			system("cls");
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n결과\n";
			for (int rMatR = 0; rMatR < 4; ++rMatR) {
				for (int rMatC = 0; rMatC < 4; ++rMatC) {
					result_matrix[rMatR][rMatC] = matrix1[rMatR][rMatC] - matrix2[rMatR][rMatC];
				}
			}
			for (int i = 0; i < 4; ++i) {
				cout << "|";
				for (int j = 0; j < 4; ++j) {
					cout << result_matrix[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n명령어 입력:";
		}
			break;
		case 'r':
		{	// 행렬식의 값
			system("cls");
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n결과\n";
			cout << "행렬1 행렬식:";
			cout << matrix1[0][0] *(matrix1[1][1] * (matrix1[2][2] * matrix1[3][3] - matrix1[2][3] * matrix1[3][2])- matrix1[1][2] * (matrix1[2][1] * matrix1[3][3] - matrix1[2][3] * matrix1[3][1])+ matrix1[1][3] * (matrix1[2][1] * matrix1[3][2] - matrix1[2][2] * matrix1[3][1]))
				- matrix1[0][1] *(matrix1[1][0] * (matrix1[2][2] * matrix1[3][3] - matrix1[2][3] * matrix1[3][2])- matrix1[1][2] * (matrix1[2][0] * matrix1[3][3] - matrix1[2][3] * matrix1[3][0])+ matrix1[1][3] * (matrix1[2][0] * matrix1[3][2] - matrix1[2][2] * matrix1[3][0]))
				+ matrix1[0][2] *(matrix1[1][0] * (matrix1[2][1] * matrix1[3][3] - matrix1[2][3] * matrix1[3][1])- matrix1[1][1] * (matrix1[2][0] * matrix1[3][3] - matrix1[2][3] * matrix1[3][0])+ matrix1[1][3] * (matrix1[2][0] * matrix1[3][1] - matrix1[2][1] * matrix1[3][0]))
				- matrix1[0][3] *(matrix1[1][0] * (matrix1[2][1] * matrix1[3][2] - matrix1[2][2] * matrix1[3][1])- matrix1[1][1] * (matrix1[2][0] * matrix1[3][2] - matrix1[2][2] * matrix1[3][0])+ matrix1[1][2] * (matrix1[2][0] * matrix1[3][1] - matrix1[2][1] * matrix1[3][0]));
			cout << "\n행렬2 행렬식:";
			cout << matrix2[0][0] * (matrix2[1][1] * (matrix2[2][2] * matrix2[3][3] - matrix2[2][3] * matrix2[3][2]) - matrix2[1][2] * (matrix2[2][1] * matrix2[3][3] - matrix2[2][3] * matrix2[3][1]) + matrix2[1][3] * (matrix2[2][1] * matrix2[3][2] - matrix2[2][2] * matrix2[3][1]))
				- matrix2[0][1] * (matrix2[1][0] * (matrix2[2][2] * matrix2[3][3] - matrix2[2][3] * matrix2[3][2]) - matrix2[1][2] * (matrix2[2][0] * matrix2[3][3] - matrix2[2][3] * matrix2[3][0]) + matrix2[1][3] * (matrix2[2][0] * matrix2[3][2] - matrix2[2][2] * matrix2[3][0]))
				+ matrix2[0][2] * (matrix2[1][0] * (matrix2[2][1] * matrix2[3][3] - matrix2[2][3] * matrix2[3][1]) - matrix2[1][1] * (matrix2[2][0] * matrix2[3][3] - matrix2[2][3] * matrix2[3][0]) + matrix2[1][3] * (matrix2[2][0] * matrix2[3][1] - matrix2[2][1] * matrix2[3][0]))
				- matrix2[0][3] * (matrix2[1][0] * (matrix2[2][1] * matrix2[3][2] - matrix2[2][2] * matrix2[3][1]) - matrix2[1][1] * (matrix2[2][0] * matrix2[3][2] - matrix2[2][2] * matrix2[3][0]) + matrix2[1][2] * (matrix2[2][0] * matrix2[3][1] - matrix2[2][1] * matrix2[3][0]));
			cout << "\n\n명령어 입력:";
		}
			break;
		case 't':
			// 전치 행렬과 그 행렬식 값
			break;
		case 'e':
		{	// 처음 눌렀을 때: 행렬의 짝수값만 출력 -> 또 눌렀을 때: 홀수값만 출력 -> 또 한번 더 눌렀을 때: 원상태 출력
			system("cls");
			if (p == false && s == false) {
				for (int i = 0; i < 4; ++i) {
					if (i == 0)cout << "행렬1";
					cout << "	|";
					for (int j = 0; j < 4; ++j) {
						if (matrix1[i][j] % 2 == 0)cout << matrix1[i][j] << "	";
						else cout << "	";
					}
					cout << "|";
					if (i == 0)cout << "	행렬2	|";
					else cout << "		|";
					for (int j = 0; j < 4; ++j) {
						if (matrix2[i][j] % 2 == 0)cout << matrix2[i][j] << "	";
						else cout << "	";
					}
					cout << "|\n";
				}
				p = true;
				cout << "\n\n명령어 입력:";
			}
			else if (p) {
				for (int i = 0; i < 4; ++i) {
					if (i == 0)cout << "행렬1";
					cout << "	|";
					for (int j = 0; j < 4; ++j) {
						if (matrix1[i][j] % 2 == 1)cout << matrix1[i][j] << "	";
						else cout << "	";
					}
					cout << "|";
					if (i == 0)cout << "	행렬2	|";
					else cout << "		|";
					for (int j = 0; j < 4; ++j) {
						if (matrix2[i][j] % 2 == 1)cout << matrix2[i][j] << "	";
						else cout << "	";
					}
					cout << "|\n";
				}
				p = false;
				s = true;
				cout << "\n\n명령어 입력:";
			}
			else if (s) {
				for (int i = 0; i < 4; ++i) {
					if (i == 0)cout << "행렬1";
					cout << "	|";
					for (int j = 0; j < 4; ++j) {
						cout << matrix1[i][j] << "	";
					}
					cout << "|";
					if (i == 0)cout << "	행렬2	|";
					else cout << "		|";
					for (int j = 0; j < 4; ++j) {
						cout << matrix2[i][j] << "	";
					}
					cout << "|\n";
				}
				s = false;
				cout << "\n\n명령어 입력:";
			}
		}
			break;
		case 's':
		{	// 행렬 다시 랜덤 셋팅
			system("cls");
			cout << "이전 행렬\n";
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n새 행렬\n";
			for (int row = 0; row < 4; ++row) {						//행 row
				for (int column = 0; column < 4; ++column) {		//열 column
					if (cnt1 == 2 && cnt2 == 2) {
						matrix1[row][column] = uid2(d);
						matrix2[row][column] = uid2(d);
					}
					else if (cnt1 == 2) {
						matrix1[row][column] = uid2(d);
						matrix2[row][column] = uid1(d);
						if (matrix2[row][column] == 2)++cnt2;
					}
					else if (cnt2 == 2) {
						matrix1[row][column] = uid1(d);
						matrix2[row][column] = uid2(d);
						if (matrix1[row][column] == 2)++cnt1;
					}
					else {
						matrix1[row][column] = uid1(d);
						matrix2[row][column] = uid1(d);
						if (matrix1[row][column] == 2)++cnt1;
						if (matrix2[row][column] == 2)++cnt2;
					}
				}
			}
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
		}
			break;
		case 'q':
			return 0;
			break;
		case '1':
		{
			system("cls");
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n결과\n";
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j]*1 << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j]*1 << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n명령어 입력:";
		}
			break;
		case '2':
		{
			system("cls");
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n결과\n";
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] * 2 << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] * 2 << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n명령어 입력:";
		}
			break;
		case '3':
		{
			system("cls");
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n결과\n";
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] * 3 << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] * 3 << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n명령어 입력:";
		}
			break;
		case '4':
		{
			system("cls");
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n결과\n";
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] * 4 << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] * 4 << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n명령어 입력:";
		}
			break;
		case '5':
		{
			system("cls");
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n결과\n";
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] * 5 << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] * 5 << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n명령어 입력:";
		}
			break;
		case '6':
		{
			system("cls");
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n결과\n";
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] * 6 << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] * 6 << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n명령어 입력:";
		}
			break;
		case '7':
		{
			system("cls");
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n결과\n";
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] * 7 << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] * 7 << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n명령어 입력:";
		}
			break;
		case '8':
		{
			system("cls");
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n결과\n";
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] * 8 << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] * 8 << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n명령어 입력:";
		}
			break;
		case '9':
		{
			system("cls");
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n결과\n";
			for (int i = 0; i < 4; ++i) {
				if (i == 0)cout << "행렬1";
				cout << "	|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix1[i][j] * 9 << "	";
				}
				cout << "|";
				if (i == 0)cout << "	행렬2	|";
				else cout << "		|";
				for (int j = 0; j < 4; ++j) {
					cout << matrix2[i][j] * 9 << "	";
				}
				cout << "|\n";
			}
			cout << "\n\n명령어 입력:";
		}
			break;
		default:
			cout << "\nError: 명령어가 존재하지 않습니다. 다시 입력해주십시오.\n명령어 입력:";
			break;
		}
	}
}
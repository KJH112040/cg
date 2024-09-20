//#include<iostream>
//#include<random>
//#include<string>
//#include<windows.h>
//using namespace std;
//
//typedef struct board {
//	int board_value=0;
//	bool open = false;
//}board;
//
//board bd[5][5];
//int opencnt = 0;
//int P1_point = 0,P2_point=0;
//bool turn = false;
//void print_board();
//void reset();
//void create_board();
//int select_pos_x(char str);
//int select_pos_y(char str);
//
//random_device rd;
//default_random_engine d(rd());
//uniform_int_distribution<int> uid(1, 13);
//
//int main() {
//	create_board();
//
//	while (opencnt<24) {
//		print_board();
//
//		if (turn)cout << "player2의 차례\n";
//		else cout << "player1의 차례\n";
//		char cmd;
//		cout << "i - 입력, r - 초기화, q - 종료\n입력:";
//		cin >> cmd;
//		switch (cmd)
//		{
//		case 'i':
//		{
//			char str1[3],str2[3];
//			int i1, i2, j1, j2;
//			while (1) {
//				cout << "첫번째 위치 입력:";
//				cin >> str1;
//
//				i1 = select_pos_x(str1[0]);
//				j1 = select_pos_y(str1[1]);
//
//				if (i1 == -1 || j1 == -1) {
//					cout << "오류\n";
//					continue;
//				}
//				else if (bd[j1][i1].open == true) {
//					cout << "이미 열린 격자\n";
//					continue;
//				}
//				bd[j1][i1].open = true;
//				print_board();
//				cout << "두번째 위치 입력:";
//				cin >> str2;
//
//				i2 = select_pos_x(str2[0]);
//				j2 = select_pos_y(str2[1]);
//
//				if (i2 == -1 || j2 == -1) {
//					cout << "오류\n";
//					bd[j1][i1].open = false;
//					continue;
//				}
//				else if (bd[j2][i2].open == true) {
//					cout << "이미 열린 격자\n";
//					bd[j1][i1].open = false;
//					continue;
//				}
//
//				if (str1[0] == str2[0] && str1[1] == str2[1]) {
//					cout << "위치 중복\n";
//					bd[j1][i1].open = false;
//					continue;
//				}
//				else break;
//			}
//			bd[j2][i2].open = true;
//			print_board();
//			if (bd[j1][i1].board_value == 13 || bd[j2][i2].board_value == 13) {
//				for (int i = 0; i < 5; ++i) {
//					for (int j = 0; j < 5; ++j) {
//						if (bd[j1][i1].board_value == bd[i][j].board_value|| bd[j2][i2].board_value == bd[i][j].board_value) {
//							bd[i][j].open = true;
//						}
//					}
//				}
//				cout << "-----------------------------------\n";
//				cout << "|         조커 효과 발동!!!        |\n";
//				cout << "-----------------------------------\n";
//				cout << ": 상대점수를 1점 가져온다\n";
//				Sleep(1000);
//				print_board();
//				opencnt += 3;
//				if (turn) {
//					P2_point += 3;
//					P1_point -= 1;
//					turn = false;
//				}
//				else {
//					P1_point += 3;
//					P2_point -= 1;
//					turn = true;
//				}
//			}
//			else if (bd[j1][i1].board_value == bd[j2][i2].board_value) {
//				opencnt += 2;
//				if (turn) {
//					P2_point += 2;
//					turn = false;
//				}
//				else {
//					P1_point += 2;
//					turn = true;
//				}
//			}
//			else if (bd[j1][i1].board_value != bd[j2][i2].board_value) {
//				bd[j1][i1].open = false;
//				bd[j2][i2].open = false;
//				if (turn) turn = false;
//				else turn = true;
//			}
//		}
//		Sleep(2000);
//		system("cls");
//			break;
//		case 'r':
//			reset();
//			break;
//		case 'q':
//			print_board();
//			cout << "player1의 점수:" << P1_point << "		player2의 점수:" << P2_point << '\n';
//			return 0;
//			break;
//		default:
//			cout << "오류: 다시 시도해주세요\n";
//			break;
//		}
//	}
//
//	print_board();
//	if (P1_point > P2_point) {
//		cout << "player1의 승!!\n";
//		cout << "player1의 점수:" << P1_point << "		player2의 점수:" << P2_point << '\n';
//	}else if (P1_point < P2_point) {
//		cout << "player2의 승!!\n";
//		cout << "player1의 점수:" << P1_point << "		player2의 점수:" << P2_point << '\n';
//	}if (P1_point == P2_point) {
//		cout << "무승부...\n";
//		cout << "player1의 점수:" << P1_point << "		player2의 점수:" << P2_point << '\n';
//	}
//}
//
//void print_board() {
//	cout << "	a	b	c	d	e\n";
//	for (int i = 0; i < 5; ++i) {
//		for (int j = 0; j < 5; ++j) {
//			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
//			if(j==0)cout << i+1 << "	";
//			if (!bd[i][j].open) {
//				cout << "*	";
//			}
//			else {
//				if (bd[i][j].board_value == 1) {
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
//					cout << "A	";
//				}
//				else if (bd[i][j].board_value == 2) {
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
//					cout << "B	";
//				}
//				else if (bd[i][j].board_value == 3) {
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
//					cout << "C	";
//				}
//				else if (bd[i][j].board_value == 4) {
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
//					cout << "D	";
//				}
//				else if (bd[i][j].board_value == 5) {
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
//					cout << "E	";
//				}
//				else if (bd[i][j].board_value == 6) {
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
//					cout << "F	";
//				}
//				else if (bd[i][j].board_value == 7) {
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
//					cout << "G	";
//				}
//				else if (bd[i][j].board_value == 8) {
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
//					cout << "H	";
//				}
//				else if (bd[i][j].board_value == 9) {
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
//					cout << "I	";
//				}
//				else if (bd[i][j].board_value == 10) {
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
//					cout << "J	";
//				}
//				else if (bd[i][j].board_value == 11) {
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
//					cout << "K	";
//				}
//				else if (bd[i][j].board_value == 12) {
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
//					cout << "L	";
//				}
//				else if (bd[i][j].board_value == 13)cout << "@	";
//			}
//		}
//		cout << '\n';
//	}
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
//};
//
//void reset() {
//	opencnt = 0,P1_point = 0, P2_point = 0;
//	turn = false;
//	for (int i = 0; i < 5; ++i) {
//		for (int j = 0; j < 5; ++j) {
//			bd[i][j].open = false;
//			bd[i][j].board_value = 0;
//		}
//	}
//	create_board();
//};
//
//void create_board() {
//	int cnt[13]{ 0,0,0,0,0,0,0,0,0,0,0,0,0 }, i=0,j=0;
//	while (i<5) {
//		int value;
//		if (j==5) {
//			++i;
//			j = 0;
//			if (i == 5)break;
//		}
//		value = uid(d);
//
//		if (value == 1) {
//			if (cnt[0] != 2) {
//				++cnt[0];
//				bd[i][j].board_value = 1;
//				++j;
//			}
//		}
//		else if (value == 2) {
//			if (cnt[1] != 2) {
//				++cnt[1];
//				bd[i][j].board_value = 2;
//				++j;
//			}
//		}
//		else if (value == 3) {
//			if (cnt[2] != 2) {
//				++cnt[2];
//				bd[i][j].board_value = 3;
//				++j;
//			}
//		}
//		else if (value == 4) {
//			if (cnt[3] != 2) {
//				++cnt[3];
//				bd[i][j].board_value = 4;
//				++j;
//			}
//		}
//		else if (value == 5) {
//			if (cnt[4] != 2) {
//				++cnt[4];
//				bd[i][j].board_value = 5;
//				++j;
//			}
//		}
//		else if (value == 6) {
//			if (cnt[5] != 2) {
//				++cnt[5];
//				bd[i][j].board_value = 6;
//				++j;
//			}
//		}
//		else if (value == 7) {
//			if (cnt[6] != 2) {
//				++cnt[6];
//				bd[i][j].board_value = 7;
//				++j;
//			}
//		}
//		else if (value == 8) {
//			if (cnt[7] != 2) {
//				++cnt[7];
//				bd[i][j].board_value = 8;
//				++j;
//			}
//		}
//		else if (value == 9) {
//			if (cnt[8] != 2) {
//				++cnt[8];
//				bd[i][j].board_value = 9;
//				++j;
//			}
//		}
//		else if (value == 10) {
//			if (cnt[9] != 2) {
//				++cnt[9];
//				bd[i][j].board_value = 10;
//				++j;
//			}
//		}
//		else if (value == 11) {
//			if (cnt[10] != 2) {
//				++cnt[10];
//				bd[i][j].board_value = 11;
//				++j;
//			}
//		}
//		else if (value == 12) {
//			if (cnt[11] != 2) {
//				++cnt[11];
//				bd[i][j].board_value = 12;
//				++j;
//			}
//		}
//		else if (value == 13) {
//			if (cnt[12] != 1) {
//				++cnt[12];
//				bd[i][j].board_value = 13;
//				++j;
//			}
//		}
//	}
//};
//
//int select_pos_x(char str) {
//	char ch = str;
//	if (ch == 'a' || ch == 'A') {
//		return 0;
//	}
//	else if (ch == 'b' || ch == 'B') {
//		return 1;
//	}
//	else if (ch == 'c' || ch == 'C') {
//		return 2;
//	}
//	else if (ch == 'd' || ch == 'D') {
//		return 3;
//	}
//	else if (ch == 'e' || ch == 'E') {
//		return 4;
//	}
//	else return -1;
//}
//
//int select_pos_y(char str) {
//	char ch = str;
//	if (ch == '1') {
//		return 0;
//	}
//	else if (ch == '2') {
//		return 1;
//	}
//	else if (ch == '3') {
//		return 2;
//	}
//	else if (ch == '4') {
//		return 3;
//	}
//	else if (ch == '5') {
//		return 4;
//	}
//	else return -1;
//}
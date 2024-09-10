#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<algorithm>
using namespace std;

typedef struct TXT_file_data {
	string line;
	struct Word { string word_data; } word[100];
	int word_num=0;
}FileData;
int line_num = 0;
bool cmd_c, cmd_d, cmd_e, cmd_f, cmd_g, cmd_r1, cmd_r2;
string txtfile(size_t index, string file_name);

int main() {

	// 2. 파일에서 문자열 읽기

	string file_name;
	ifstream file;

	cout << "input data file name:";
	getline(cin, file_name, '\n');
	size_t index = file_name.length();

	file_name = txtfile(index, file_name);
	file.open(file_name);

	if (!file)cout << "Error: 파일 열기 실패";
	else {
		FileData file_data[30];
		while (file.get() != EOF) {
			while (getline(file, file_data[line_num].line))
				++line_num;
		}

		for (int i = 0; i < line_num; ++i) {
			size_t line_size = file_data[i].line.size();
			int j = 0, cnt = 0;
			bool a = false;
			while (j < line_size) {
				if (file_data[i].line[j] != ' ') {
					file_data[i].word[cnt].word_data.push_back(file_data[i].line[j]);
					++j;
				}
				else {
					if (file_data[i].line[j - 1] == ' ' && j != 0) {

					}
					else ++cnt;
					++j;
				}
			}
			file_data[i].word_num = cnt + 1;
		}

		for (int i = 0; i < line_num; ++i) {
			cout << "	" << file_data[i].line << "\n";
		}

		while (1) {
			cout << "\ninput the command:";
			char cmd;
			cin >> cmd;
			switch (cmd) {
			case 'c':
			{	// 대문자로 시작되는 단어를 찾아 그 단어 다른 색으로 출력, 몇 개 있는지 출력, 다시 누르면 원상복귀
				if (cmd_c == false) {
					for (int i = 0; i < line_num; ++i) {
						int word_cnt = 0;
						cout << "	";
						for (int j = 0; j < file_data[i].word_num; ++j) {
							if ('A' <= file_data[i].word[j].word_data[0] && file_data[i].word[j].word_data[0] <= 'Z') {
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
								cout << file_data[i].word[j].word_data << ' ';
								++word_cnt;
							}
							else {
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
								cout << file_data[i].word[j].word_data << ' ';
							}
						}
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						cout << "	" << word_cnt << "\n";
					}
					cmd_c = true;
				}
				else if (cmd_c == true) {
					for (int i = 0; i < line_num; ++i) {
						cout << "	" << file_data[i].line << "\n";
					}
					cmd_c = false;
				}
			}
			break;
			case 'd':
			{	// 문장 한 줄 전체를 거꾸로 출력, 다시 누르면 원상 복구
				if (cmd_d == false) {
					for (int i = 0; i < line_num; ++i) {
						cout << "	";
						reverse(file_data[i].line.begin(), file_data[i].line.end());
						cout << file_data[i].line << "\n";
					}
					cmd_d = true;
				}
				else if (cmd_d == true) {
					for (int i = 0; i < line_num; ++i) {
						cout << "	";
						reverse(file_data[i].line.begin(), file_data[i].line.end());
						cout << file_data[i].line << "\n";
					}
					cmd_d = false;
				}
			}
			break;
			case 'e':
			{
				// 3문자 후 2개의 @문자 삽입, 다시 누르면 원상 복구
				if (cmd_e == false) {
					for (int i = 0; i < line_num; ++i) {
						size_t line_size = file_data[i].line.size();
						int j = 0, cnt = 0;
						cout << "	";
						while (j < line_size) {
							if (cnt == 3) {
								cout << "@@";
								++j;
								cnt = 0;
							}
							else {
								cout << file_data[i].line[j];
								++cnt;
							}
							++j;
						}
						cout << "\n";
					}
					cmd_e = true;
				}
				else if (cmd_e == true) {
					for (int i = 0; i < line_num; ++i) {
						cout << "	" << file_data[i].line << "\n";
					}
					cmd_e = false;
				}
			}
			break;
			case 'f':
			{
				// 공백 기준 모든 단어 거꾸로 출력, 다시 누르면 원상벅구 
				if (cmd_f == false) {
					for (int i = 0; i < line_num; ++i) {
						cout << "	";
						for (int j = 0; j < file_data[i].word_num; ++j) {
							reverse(file_data[i].word[j].word_data.begin(), file_data[i].word[j].word_data.end());
							cout << file_data[i].word[j].word_data << ' ';
						}
						cout << '\n';
					}
					cmd_f = true;
				}
				else if (cmd_f == true) {
					for (int i = 0; i < line_num; ++i) {
						for (int j = 0; j < file_data[i].word_num; ++j) {
							reverse(file_data[i].word[j].word_data.begin(), file_data[i].word[j].word_data.end());
						}
						cout << "	" << file_data[i].line << "\n";
					}
					cmd_f = false;
				}
			}
			break;
			case 'g':
			{	// 문자 내부의 특정 문자 다른문자로 바꾸기
				if (cmd_g == false) {
					char change_before, change_after;
					cout << "input the character:";;
					cin >> change_before;
					cout << "input the character:";;
					cin >> change_after;
					for (int i = 0; i < line_num; ++i) {
						size_t line_size = file_data[i].line.size();
						int j = 0;
						cout << "	";
						while (j < line_size) {
							if (file_data[i].line[j] == change_before) {
								cout << change_after;
							}
							else cout << file_data[i].line[j];
							++j;
						}
						cout << "\n";
					}
					cmd_g = true;
				}
				else if (cmd_g == true) {
					for (int i = 0; i < line_num; ++i) {
						cout << "	" << file_data[i].line << "\n";
					}
					cmd_g = false;
				}
			}
			break;
			case 'h':
				// 각 줄 단어 개수 출력
				for (int i = 0; i < line_num; ++i) {
					cout << "	" << file_data[i].line << "	" << file_data[i].word_num << "\n";
				}
				break;
			case 'r':
			{
				// 오름 -> 내림 -> 복구
				if (cmd_r1 == false && cmd_r2 == false) {
					struct LINE { string data; int word_num = 0; } sort[30];
					int max = 0;
					for (int j = 0; j < line_num; ++j) {
						if (file_data[max].word_num <= file_data[j].word_num)max = j;
					}
					for (int i = 0; i < line_num; ++i) {
						int min = max;
						for (int j = 0; j < line_num; ++j) {
							if (i != 0 && sort[i - 1].word_num >= file_data[j].word_num) {
								if (sort[i - 1].word_num == file_data[j].word_num) {
									for (int a = 0; sort[a].data != ""; ++a) {
										if (sort[a].data == file_data[j].line)break;
										else if (a == i - 1) min = j;
									}
								}
							}
							else if (file_data[min].word_num >= file_data[j].word_num)min = j;
						}
						sort[i].word_num = file_data[min].word_num;
						sort[i].data = file_data[min].line;
					}
					for (int i = 0; i < line_num; ++i) {
						cout << "	" << sort[i].data << "\n";
					}
					cmd_r1 = true;
				}
				else if (cmd_r1 == true) {
					struct LINE { string data; int word_num = 0; } sort[30];
					int min = 0;
					for (int j = 0; j < line_num; ++j) {
						if (file_data[min].word_num >= file_data[j].word_num)min = j;
					}
					for (int i = 0; i < line_num; ++i) {
						int max = min;
						for (int j = 0; j < line_num; ++j) {
							if (i != 0 && sort[i - 1].word_num <= file_data[j].word_num) {
								if (sort[i - 1].word_num == file_data[j].word_num) {
									for (int a = 0; sort[a].data != ""; ++a) {
										if (sort[a].data == file_data[j].line)break;
										else if (a == i - 1) max = j;
									}
								}
							}
							else if (file_data[max].word_num <= file_data[j].word_num)max = j;
						}
						sort[i].word_num = file_data[max].word_num;
						sort[i].data = file_data[max].line;
					}
					for (int i = 0; i < line_num; ++i) {
						cout << "	" << sort[i].data << "\n";
					}
					cmd_r1 = false, cmd_r2 = true;
				}
				else if (cmd_r2 == true) {
					for (int i = 0; i < line_num; ++i) {
						cout << "	" << file_data[i].line << "\n";
						cmd_r2 = false;
					}
				}
				break;
			case 's':
			{
				// 명령어 s와 단어 같이 입력하면, 입려받은 문장 모두 출력하면서 단어를 찾아 다른 색으로 출력, 몇 개 있는지 계산하여 출력
				string input;
				cin >> input;
				int word_cnt = 0;
				for (int i = 0; i < line_num; ++i) {
					cout << "	";
					for (int j = 0; j < file_data[i].word_num; ++j) {
						if (stricmp(file_data[i].word[j].word_data.c_str(), input.c_str()) == 0) {
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
							cout << file_data[i].word[j].word_data << ' ';
							++word_cnt;
						}
						else {
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
							cout << file_data[i].word[j].word_data << ' ';
						}
					}
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << "\n";
				}
				cout << "total:" << word_cnt << '\n';
			}
			break;
			case 'q':
				return 0;
				break;
			default:
				cout << "\nError: 명령어가 존재하지 않습니다. 다시 입력해주십시오.\n";
				break;
			}
			}
		}
	}
}

string txtfile(size_t index, string file_name) {
	string txt;
	if (index > 3) {
		if (file_name.find(".txt", index - 4) == string::npos) {
			file_name.append(".txt");
		}
	}
	else {
		file_name.append(".txt");
	}
	return txt = file_name;
}
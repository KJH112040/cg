#include<iostream>
#include<cmath>
using namespace std;
typedef struct List {
	int x{ 0 }, y{ 0 }, z{ 0 };
	double distance{0};
	bool value=false;
}List;

List point_data[20];
void OutPut_List();
bool cmd_a, cmd_s;

int main() {
	while (1) {
		char cmd;
		cin >> cmd;
		switch (cmd)
		{
		case '+':
		{
			int input_x, input_y, input_z;
			cin >> input_x >> input_y >> input_z;
			bool error=true;
			for (int i = 0; i < 20; ++i) {
				if (point_data[i].value == false) {
					point_data[i].x = input_x;
					point_data[i].y = input_y;
					point_data[i].z = input_z;
					point_data[i].value = true;
					error = false;
					break;
				}
			}

			if (error)cout << "데이터 저장 공간 부족\n";
			else OutPut_List();
		}
			break;
		case '-':
		{
			bool error = true;
			for (int i = 19; i >-1; --i) {
				if (point_data[i].value == true) {
					point_data[i].x = 0;
					point_data[i].y = 0;
					point_data[i].z = 0;
					point_data[i].value = false;
					error = false;
					break;
				}
			}

			if (error)cout << "저장된 데이터 찾을 수 없음\n";
			else OutPut_List();
		}
			break;
		case 'e':
		{
			int input_x, input_y, input_z;
			cin >> input_x >> input_y >> input_z;
			bool error = true;
			int cnt = 0;
			for (int i = 0; i < 20; ++i)if (point_data[i].value == true)++cnt;

			if(cnt!=19)
			{
				if(point_data[0].value==true)
				{
					for (int i = 19; i > 0; --i) {
						if (point_data[i].value == true && point_data[i + 1].value == false && i != 19) {
							point_data[i + 1].x = point_data[i].x;
							point_data[i + 1].y = point_data[i].y;
							point_data[i + 1].z = point_data[i].z;
							point_data[i].x = 0;
							point_data[i].y = 0;
							point_data[i].z = 0;
							point_data[i].value = false;
							point_data[i + 1].value = true;
						}
					}
				}

				for (int i = 0; i < 20; ++i) {
					if (point_data[i].value == false) {
						point_data[i].x = input_x;
						point_data[i].y = input_y;
						point_data[i].z = input_z;
						point_data[i].value = true;
						error = false;
						break;
					}
				}
			}

			if (error)cout << "데이터 저장 공간 부족\n";
			else OutPut_List();
		}
			break;
		case 'd':
		{
			bool error = true;
			for (int i = 0; i < 20; ++i) {
				if (point_data[i].value == true) {
					point_data[i].x = 0;
					point_data[i].y = 0;
					point_data[i].z = 0;
					point_data[i].value = false;
					error = false;
					break;
				}
			}

			if (error)cout << "저장된 데이터 찾을 수 없음\n";
			else OutPut_List();
		}
			break;
		case 'l': 
		{
			int cnt = 1;
			for (int i = 0; i < 20; ++i) if (point_data[i].value = true)++cnt;
			cout << "리스트 길이:" << cnt << '\n';
		}
			break;
		case 'c':
		{
			for (int i = 0; i < 20; ++i) {
				point_data[i].value = false;
				point_data[i].x = 0;
				point_data[i].y = 0;
				point_data[i].z = 0;
			}
		}
			break;
		case 'm': 
		{
			double max = 0;
			int index;
			for (int i = 0; i < 20; ++i) {
				point_data[i].distance=sqrt(point_data[i].x * point_data[i].x + point_data[i].y * point_data[i].y + point_data[i].z * point_data[i].z);
			}
			for (int i = 0; i < 20; ++i) {
				if (max < point_data[i].distance&&point_data[i].value==true) {
					max = point_data[i].distance;
					index = i;
				}
			}
			cout << "(" << point_data[index].x << "," << point_data[index].y << "," << point_data[index].z << ")\n";
		}
			break;
		case 'n':
		{
			double min,max=0;
			int index;
			for (int i = 0; i < 20; ++i) {
				point_data[i].distance = sqrt(point_data[i].x * point_data[i].x + point_data[i].y * point_data[i].y + point_data[i].z * point_data[i].z);
			}
			for (int i = 0; i < 20; ++i) {
				if (max < point_data[i].distance && point_data[i].value == true) {
					max = point_data[i].distance;
				}
			}
			min = max;
			for (int i = 0; i < 20; ++i) {
				if (min > point_data[i].distance && point_data[i].value == true) {
					min = point_data[i].distance;
					index = i;
				}
			}
			cout << "(" << point_data[index].x << "," << point_data[index].y << "," << point_data[index].z << ")\n";
		}
			break;
		case 'a'://오름차
		{
			if (cmd_a == false) {
				List sort[20];
				for (int i = 0; i < 20; ++i) {
					point_data[i].distance = sqrt(point_data[i].x * point_data[i].x + point_data[i].y * point_data[i].y + point_data[i].z * point_data[i].z);
					sort[i] = point_data[i];
				}
				for (int i = 0; i < 20; ++i) {
					List min;
					int k=i;
					if (sort[i].value)min = sort[i];
					for (int j = i+1; j < 20; ++j) {
						if (sort[j].value) {
							if (min.distance > sort[j].distance) {
								min = sort[j];
								k = j;
							}
						}
					}
					List tmp = sort[i];
					sort[i] = min;
					sort[k] = tmp;

				}
				for (int i = 19; i > -1; --i) {
					cout << i << "	" << sort[i].x << ' ' << sort[i].y << ' ' << sort[i].z << '\n';
				}
				cmd_a = true;
			}
			else if (cmd_a == true) {
				OutPut_List();
				cmd_a = false;
			}
		}
			break;
		case 's'://내림차
		{
			if (cmd_s == false) {
				List sort[20];
				for (int i = 0; i < 20; ++i) {
					point_data[i].distance = sqrt(point_data[i].x * point_data[i].x + point_data[i].y * point_data[i].y + point_data[i].z * point_data[i].z);
					sort[i] = point_data[i];
				}
				for (int i = 0; i < 20; ++i) {
					List max;
					int k = i;
					if (sort[i].value)max = sort[i];
					for (int j = i + 1; j < 20; ++j) {
						if (sort[j].value) {
							if (max.distance < sort[j].distance) {
								max = sort[j];
								k = j;
							}
						}
					}
					List tmp = sort[i];
					sort[i] = max;
					sort[k] = tmp;

				}
				for (int i = 19; i > -1; --i) {
					cout << i << "	" << sort[i].x << ' ' << sort[i].y << ' ' << sort[i].z << '\n';
				}
				cmd_s = true;
			}
			else if (cmd_s == true) {
				OutPut_List();
				cmd_s = false;
			}
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

void OutPut_List() {
	for (int i = 19; i > -1; --i) {
		cout << i << "	" << point_data[i].x << ' ' << point_data[i].y << ' ' << point_data[i].z << '\n';
	}
}
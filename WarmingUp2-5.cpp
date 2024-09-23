//#include<iostream>
//using namespace std;
//typedef struct Shape {
//	int x1=0, y1=0, x2=0, y2=0,w=0,h=0;
//}Sh;
//
//Sh shape;
//bool board[30][30];
//void input_pos();
//int save_pos(int x1, int y1, int x2, int y2);
//void print_board();
//void start_board();
//void move_board(char cmd);
//int main() {
//	input_pos();
//	while (1) {
//		print_board();
//		char cmd;
//		cout << "input order: ";
//		cin >> cmd;
//		switch (cmd)
//		{
//		case 'x':
//			move_board('x');
//			break;
//		case 'X':
//			move_board('X');
//			break;
//		case 'y':
//			move_board('y');
//			break;
//		case 'Y':
//			move_board('Y');
//			break;
//		case 's':
//		{
//			if(shape.x1<shape.x2&&shape.y1<shape.y2){
//				--shape.w, --shape.h;
//				for (int i = shape.y1; i <= shape.y2; ++i) {
//					board[i][shape.x2] = false;
//				}
//				for (int i = shape.x1; i <= shape.x2; ++i) {
//					board[shape.y2][i] = false;
//				}
//				--shape.x2, --shape.y2;
//			}
//		}
//			break;
//		case 'S':
//		{
//			if (shape.x1 <= shape.x2 && shape.y1 <= shape.y2) {
//				++shape.w, ++shape.h;
//				for (int i = shape.y1; i <= shape.y2+1; ++i) {
//					board[i][shape.x2+1] = true;
//				}
//				for (int i = shape.x1; i <= shape.x2+1; ++i) {
//					board[shape.y2+1][i] = true;
//				}
//				++shape.x2, ++shape.y2;
//			}
//		}
//			break;
//		case 'i':
//		{
//			if (shape.x1 <= shape.x2) {
//				++shape.w;
//				for (int i = shape.y1; i <= shape.y2; ++i) {
//					board[i][shape.x2 + 1] = true;
//				}
//				++shape.x2;
//			}
//		}
//			break;
//		case 'I':
//		{
//			if (shape.x1 < shape.x2) {
//				--shape.w;
//				for (int i = shape.y1; i <= shape.y2; ++i) {
//					board[i][shape.x2] = false;
//				}
//				--shape.x2;
//			}
//		}
//			break;
//		case 'j':
//		{
//			if (shape.y1 <= shape.y2) {
//				++shape.h;
//				for (int i = shape.x1; i <= shape.x2; ++i) {
//					board[shape.y2 + 1][i] = true;
//				}
//				++shape.y2;
//			}
//		}
//			break;
//		case 'J':
//		{
//			if (shape.y1 < shape.y2) {
//				--shape.h;
//				for (int i = shape.x1; i <= shape.x2; ++i) {
//					board[shape.y2][i] = false;
//				}
//				--shape.y2;
//			}
//		}
//			break;
//		case 'a':
//		{
//			if (shape.x1 <= shape.x2) {
//				++shape.w;
//				for (int i = shape.y1; i <= shape.y2; ++i) {
//					board[i][shape.x2 + 1] = true;
//				}
//				++shape.x2;
//			}
//
//			if (shape.y1 < shape.y2) {
//				--shape.h;
//				for (int i = shape.x1; i <= shape.x2; ++i) {
//					board[shape.y2][i] = false;
//				}
//				--shape.y2;
//			}
//		}
//			break;
//		case 'A':
//		{
//			if (shape.x1 < shape.x2) {
//				--shape.w;
//				for (int i = shape.y1; i <= shape.y2; ++i) {
//					board[i][shape.x2] = false;
//				}
//				--shape.x2;
//			}
//
//			if (shape.y1 <= shape.y2) {
//				++shape.h;
//				for (int i = shape.x1; i <= shape.x2; ++i) {
//					board[shape.y2 + 1][i] = true;
//				}
//				++shape.y2;
//			}
//		}
//			break;
//		case 'm'://사각형 면적 출력(면적:가로*세로=)
//		{
//			cout << "면적: " << shape.w << "x" << shape.h << " = " << shape.w * shape.h << '\n';
//		}
//			break;
//		case 'n'://전체 면적에 대한 사각형 면적 비율 출력(전체 면적: 30*30 = 900, 사각형 면적: , 면적 비율: (/300)*100 = %)
//		{
//			int a = shape.w * shape.h;
//			cout << "전체 면적: 30x30 = 900, 사각형 면적: " << a << ", 면적 비율: (" << a << "/900)*100 = " << ((float)a / 900) * 100 << "%\n";
//		}
//			break;
//		case 'r'://리셋 후 다시 좌표 입력부터
//		{
//			shape.x1 = 0, shape.y1 = 0, shape.x2 = 0, shape.y2 = 0;
//			for (int i = 0; i < 30; ++i) {
//				for (int j = 0; j < 30; ++j) {
//					board[i][j] = false;
//				}
//			}
//			input_pos();
//		}
//			break;
//		case 'q':
//			return 0;
//			break;
//		default:
//			cout << "오류\n";
//			break;
//		}
//	}
//}
//
//void input_pos() {
//	int x1, y1, x2, y2;
//	while (1) {
//		cout << "input coord value: ";
//		cin >> x1 >> y1 >> x2 >> y2;
//		if (save_pos(x1, y1, x2, y2) == -1)continue;
//		else break;
//	}
//	start_board();
//}
//int save_pos(int x1, int y1, int x2, int y2) {
//	if (x1 < 1 || x1>30) {
//		cout << "범위 오류\n";
//		return -1;
//	}
//	else if (y1 < 1 || y1>30) {
//		cout << "범위 오류\n";
//		return -1;
//	}
//	else if (x2 < 1 || x2>30) {
//		cout << "범위 오류\n";
//		return -1;
//	}
//	else if (y2 < 1 || y2>30) {
//		cout << "범위 오류\n";
//		return -1;
//	}
//	else {
//		shape.x1 = x1-1;
//		shape.y1 = y1-1;
//		shape.x2 = x2-1;
//		shape.y2 = y2-1;
//		return 0;
//	}
//}
//void print_board() {
//	for (int i = 0; i < 30; ++i) {
//		for (int j = 0; j < 30; ++j) {
//			if (!board[i][j]) cout << ".  ";
//			else cout << "0  ";
//		}
//		cout << "\n";
//	}
//}
//void start_board() {
//	if (shape.x1 > shape.x2) {
//		int tmp = shape.x1;
//		shape.x1 = shape.x2;
//		shape.x2 = tmp;
//	}
//	if (shape.y1 > shape.y2) {
//		int tmp = shape.y1;
//		shape.y1 = shape.y2;
//		shape.y2 = tmp;
//	}
//	shape.h = shape.y2 - shape.y1 + 1;
//	shape.w = shape.x2 - shape.x1 + 1;
//	for (int i = 0; i < 30; ++i) {
//		for (int j = 0; j < 30; ++j) {
//			if (shape.y1 <= i && i <= shape.y2) {
//				if (shape.x1 <= j && j <= shape.x2) {
//					board[i][j] = true;
//				}
//			}
//		}
//	}
//}
//void move_board(char cmd) {
//	// y가 벽에 걸쳐 있을 때, x하면 기존에 걸쳐져 있던 벽에서 빠져나가고 사각형이 길어지는 경우가 있을 수 있음(그 반대(y,x->x,y)도 마찬가지) ::돌려보니 걍 사라짐
//	int start[2] = { 0,0 }, end[2] = { 0,0 };
//	bool wall_x = false,wall_y=false;
//	if (shape.x1 > shape.x2)wall_x = true;
//	if (shape.y1 > shape.y2)wall_y = true;
//	start[0] = shape.x1, end[0] = shape.x2;
//	start[1] = shape.y1, end[1] = shape.y2;
//	for (int i = 0; i < 30; ++i) {
//		for (int j = 0; j < 30; ++j) {
//			board[i][j] = false;
//		}
//	}
//	if (cmd == 'x') {
//		++shape.x1, ++shape.x2;
//		if (shape.x1 > 29)shape.x1 = shape.x1 - 30;
//		if (shape.x2 > 29)shape.x2 = shape.x2 - 30;
//
//		if (shape.w == 30) {
//			for (int i = start[1]; i <= end[1]; ++i) {
//				for (int j = 0; j < 30; ++j) {
//					board[i][j] = true;
//				}
//			}
//		}
//		else if (wall_x) {
//			for (int i = start[1]; i <= end[1]; ++i) {
//				if (start[0] == 29) {
//					for (int j = 0; j <= end[0] + 1; ++j) {
//						board[i][j] = true;
//					}
//				}
//				else {
//					for (int j = 0; j <= end[0]+1; ++j) {
//						board[i][j] = true;
//					}
//					for (int j = start[0]+1; j < 30; ++j) {
//						board[i][j] = true;
//					}
//				}
//			}
//		}
//		else {
//			for (int i = start[1]; i <= end[1]; ++i) {
//				if (end[0] == 29) {
//					board[i][0] = true;
//					for (int j = start[0] + 1; j < 30; ++j) {
//						board[i][j] = true;
//					}
//				}
//				else{
//					for (int j = start[0] + 1; j <= end[0] + 1; ++j) {
//						board[i][j] = true;
//					}
//				}
//			}
//		}
//	}
//	else if (cmd == 'X') {
//		--shape.x1, --shape.x2;
//		if (shape.x1 < 0)shape.x1 = shape.x1 + 30;
//		if (shape.x2 < 0)shape.x2 = shape.x2 + 30;
//
//		if(shape.w==30){
//			for (int i = start[1]; i <= end[1]; ++i) {
//				for (int j = 0; j < 30; ++j) {
//					board[i][j] = true;
//				}
//			}
//		}
//		else if (wall_x) {
//			for (int i = start[1]; i <= end[1]; ++i) {
//				if (end[0] == 0) {
//					for (int j = start[0] - 1; j < 30; ++j) {
//						board[i][j] = true;
//					}
//				}
//				else {
//					for (int j = 0; j <= end[0] - 1; ++j) {
//						board[i][j] = true;
//					}
//					for (int j = start[0] - 1; j < 30; ++j) {
//						board[i][j] = true;
//					}
//				}
//			}
//		}
//		else {
//			for (int i = start[1]; i <= end[1]; ++i) {
//				if (start[0] == 0) {
//					board[i][29] = true;
//					for (int j = 0; j <= end[0] - 1; ++j) {
//						board[i][j] = true;
//					}
//				}
//				else {
//					for (int j = start[0] - 1; j <= end[0] - 1; ++j) {
//						board[i][j] = true;
//					}
//				}
//			}
//		}
//	}
//	else if (cmd == 'y') {
//		++shape.y1, ++shape.y2;
//		if (shape.y1 > 29)shape.y1 = shape.y1 - 30;
//		if (shape.y2 > 29)shape.y2 = shape.y2 - 30;
//
//		if (shape.h==30) {
//			for (int i = 0; i < 30; ++i) {
//				for (int j = start[0]; j <= end[0]; ++j) {
//					board[i][j] = true;
//				}
//			}
//		}
//		else if (wall_y) {
//			if (start[1] == 29) {
//				for (int i = 0; i <= end[1] + 1; ++i) {
//					for (int j = start[0]; j <= end[0]; ++j) {
//						board[i][j] = true;
//					}
//				}
//			}
//			else {
//				for (int i = 0; i <= end[1] + 1; ++i) {
//					for (int j = start[0]; j <= end[0]; ++j) {
//						board[i][j] = true;
//					}
//				}
//				for (int i = start[1]+1; i <30; ++i) {
//					for (int j = start[0]; j <= end[0]; ++j) {
//						board[i][j] = true;
//					}
//				}
//			}
//		}
//		else {
//			if (end[1] == 29) {
//				for (int i = start[0]; i <= end[0]; ++i) {
//					board[0][i] = true;
//				}
//				for (int i = start[1] + 1; i < 30; ++i) {
//					for (int j = start[0]; j <= end[0]; ++j) {
//						board[i][j] = true;
//					}
//				}
//			}
//			else {
//				for (int i = start[1] + 1; i <= end[1] + 1; ++i) {
//					for (int j = start[0]; j <= end[0]; ++j) {
//						board[i][j] = true;
//					}
//				}
//			}
//		}
//	}
//	else if (cmd == 'Y') {
//		--shape.y1, --shape.y2;
//		if (shape.y1 < 0)shape.y1 = shape.y1 + 30;
//		if (shape.y2 < 0)shape.y2 = shape.y2 + 30;
//
//		if (shape.h == 30) {
//			for (int i = 0; i < 30; ++i) {
//				for (int j = start[0]; j <= end[0]; ++j) {
//					board[i][j] = true;
//				}
//			}
//		}
//		else if (wall_y) {
//			if (end[1] == 0) {
//				for (int i = start[1] - 1; i < 30; ++i) {
//					for (int j = start[0]; j <= end[0]; ++j) {
//						board[i][j] = true;
//					}
//				}
//			}
//			else {
//				for (int i = 0; i <= end[1] - 1; ++i) {
//					for (int j = start[0]; j <= end[0]; ++j) {
//						board[i][j] = true;
//					}
//				}
//				for (int i = start[1] - 1; i < 30; ++i) {
//					for (int j = start[0]; j <= end[0]; ++j) {
//						board[i][j] = true;
//					}
//				}
//			}
//		}
//		else {
//			if (start[1] == 0) {
//				for (int j = start[0]; j <= end[0]; ++j) {
//					board[29][j] = true;
//				}
//				for (int i = 0; i <= end[1] - 1; i++) {
//					for (int j = start[0]; j <= end[0]; ++j) {
//						board[i][j] = true;
//					}
//				}
//			}
//			else {
//				for (int i = start[1] - 1; i <= end[1] - 1; ++i) {
//					for (int j = start[0]; j <= end[0]; ++j) {
//						board[i][j] = true;
//					}
//				}
//			}
//		}
//	}
//}
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>


using std::cout;
using std::cin;
using std::endl;

const int num_ene = 5;//�л�����
const int x = 35;
const int y = 25;
int canvas[y][x] = { 0 };//�����������Ϣ�洢��������
int top, width;//�߽�
int pos_x, pos_y;//�ɻ�����
int enemy_x[num_ene], enemy_y[num_ene];//�л�������
int score;
int bullet_num;//�ӵ�����
char ch;

void gotoxy(int x, int y)  //����ƶ���(x,y)λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void startup()
{
	top = y;
	width = x;
	pos_x = width / 2;
	pos_y = top / 2;
	for (int t = 0; t < num_ene; t++) {
		enemy_x[t] = rand() % width;
		enemy_y[t] = 0;
		canvas[enemy_y[t]][enemy_x[t]] = 3;
	}

	ch = '\0';
	score = 0;
	bullet_num = 0;
}

void show()
{
	int i, j;
	//��������������
	gotoxy(0, 0);


	for (i = 0; i < top; i++) {
		for (j = 0; j < width; j++) {
			if (canvas[i][j] == 1)
				cout << '*';
			else if (canvas[i][j] == 2)
				cout << '|';
			else if (canvas[i][j] == 3)
				cout << '$';
			else
				cout << ' ';
		}
		cout << endl;
	}
	cout << "�÷֣�" << score << endl;
}

void updata_Input()
{
	if (_kbhit()) {

		ch = _getch();
		if (ch == 'a') {
			canvas[pos_y][pos_x] = 0;
			pos_x--;
			if (pos_x < 0)
				pos_x = 0;
			canvas[pos_y][pos_x] = 1;
		}
		else if (ch == 'd') {
			canvas[pos_y][pos_x] = 0;
			pos_x++;
			if (pos_x > width - 1)
				pos_x = width - 1;
			canvas[pos_y][pos_x] = 1;
		}
		else if (ch == 'w') {
			canvas[pos_y][pos_x] = 0;
			pos_y--;
			if (pos_y < 0)
				pos_y = 0;
			canvas[pos_y][pos_x] = 1;
		}
		else if (ch == 's') {
			canvas[pos_y][pos_x] = 0;
			pos_y++;
			if (pos_y > top - 1)
				pos_y = top - 1;
			canvas[pos_y][pos_x] = 1;
		}
		else if (ch == ' ') {

			int left = pos_x - bullet_num;
			if (left < 0)
				left = 0;
			int right = pos_x + bullet_num;
			if (right > width - 1)
				right = width - 1;
			for (int i = left; i <= right; i++) {
				canvas[pos_y - 1][i] = 2;
			}

		}
	}

}

void updata_No_Input()
{
	canvas[pos_y][pos_x] = 1;


	//�л����±߽磬��������
	for (int t = 0; t < num_ene; t++) {
		if (enemy_y[t] >= top - 1) {			//�����>=top����ô�����
			canvas[enemy_y[t]][enemy_x[t]] = 0;
			enemy_x[t] = rand() % width;
			enemy_y[t] = 0;
			canvas[enemy_y[t]][enemy_x[t]] = 3;
		}
	}




	static int i = 0;
	if (i <= 5) {
		i++;
	}
	else {
		for (int t = 0; t < num_ene; t++) {
			canvas[enemy_y[t]][enemy_x[t]] = 0;
			enemy_y[t]++;
			canvas[enemy_y[t]][enemy_x[t]] = 3;
		}


		i = 0;
	}


	//�ӵ�����
	for (int n = 0; n < top; n++) {
		for (int m = 0; m < width; m++) {


			if (canvas[n][m] == 2) {
				canvas[n][m] = 0;//��ȥǰһ֡���ӵ�
				for (int t = 0; t < num_ene; t++) {
					if (n == enemy_y[t] && m == enemy_x[t]) {			//����ӵ��򵽵л�
						canvas[enemy_y[t]][enemy_x[t]] = 0;
						enemy_x[t] = rand() % width;
						enemy_y[t] = 0;
						canvas[enemy_y[t]][enemy_x[t]] = 3;
						score++;
						if (score % 10 == 0)
							bullet_num++;
					}
					else {
						if (n > 0)
							canvas[n - 1][m] = 2;
					}


				}

			}
		}
	}

	//�л������ɻ�����Ϸ����
	for (int i = 0; i < num_ene; i++) {
		if ((enemy_x[i] == pos_x) && (enemy_y[i] == pos_y)) {
			system("cls");
			for (int t = 0; t < top / 2; t++) {
				cout << '\n';
			}
			for (int y = 0; y < width / 2; y++) {
				cout << ' ';
			}
			cout << "Game Over";
			for (int t = 0; t < top / 2; t++) {
				cout << '\n';
			}
			exit(0);
		}
	}



	//�������ӣ��ӵ����


}





int main()
{

	startup();
	while (true) {
		show();
		updata_Input();
		updata_No_Input();
	}

	return 0;
}






//Note
//�ӵ��͵л��ƶ���ʽ��һ��
//�������������������ڣ�����̨��С������ı߽粻ƥ��  ����߽������⣬����1������1  �����п������
/*
*		��һ��
*		for (int t = 0; t < top / 2; t++) {
*			cout << '\n';
*		}
*		for (int y = 0; y < width / 2; y++) {
*			cout << ' ';
*		}
*		�������ǵ��������ȵڶ�������canvas��
*/
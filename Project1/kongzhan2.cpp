#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>


using std::cout;
using std::cin;
using std::endl;

const int num_ene = 5;//敌机数量
const int x = 35;
const int y = 25;
int canvas[y][x] = { 0 };//将所以输出信息存储在数组中
int top, width;//边界
int pos_x, pos_y;//飞机坐标
int enemy_x[num_ene], enemy_y[num_ene];//敌机坐标组
int score;
int bullet_num;//子弹数量
char ch;

void gotoxy(int x, int y)  //光标移动到(x,y)位置
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
	//比清屏函数好用
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
	cout << "得分：" << score << endl;
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


	//敌机到下边界，重新生成
	for (int t = 0; t < num_ene; t++) {
		if (enemy_y[t] >= top - 1) {			//如果是>=top，那么会溢出
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


	//子弹上升
	for (int n = 0; n < top; n++) {
		for (int m = 0; m < width; m++) {


			if (canvas[n][m] == 2) {
				canvas[n][m] = 0;//消去前一帧的子弹
				for (int t = 0; t < num_ene; t++) {
					if (n == enemy_y[t] && m == enemy_x[t]) {			//如果子弹打到敌机
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

	//敌机碰到飞机，游戏结束
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



	//分数增加，子弹变多


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
//子弹和敌机移动方式不一样
//输出有问题基本都出现在：控制台大小和输出的边界不匹配  输出边界有问题，多了1或少了1  数组有可能溢出
/*
*		第一代
*		for (int t = 0; t < top / 2; t++) {
*			cout << '\n';
*		}
*		for (int y = 0; y < width / 2; y++) {
*			cout << ' ';
*		}
*		本代码是第三代（比第二代多了canvas）
*/
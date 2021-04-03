#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>


using std::cout;
using std::cin;
using std::endl;

int pos_x, pos_y;//飞机坐标
int top, right;//边界
int zidan_x, zidan_y;//子弹坐标
int enemy_x, enemy_y;//敌机坐标
int score = 0;//得分
int isKilled = 0;
char ch = '\0';

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
	top = 30;
	right = 60;
	pos_x = right / 2;
	pos_y = top / 2;
	zidan_x = -1;
	zidan_y = -1;
	enemy_x = rand() % right;
	enemy_y = 0;
}

void show()
{
	int i, j;
	//比清屏函数好用
	gotoxy(0, 0);
	//Sleep(500);
	//碰到边界不要在往上了
	if (pos_x <= 0)
		pos_x = 0;
	if (pos_y <= 0)
		pos_y = 0;
	if (pos_x > right)
		pos_x = right;
	if (pos_y > top)
		pos_y = top;
	/*if (zidan_x <= 0)
		zidan_x = 0;
	if (zidan_y <= 0)
		zidan_y = 0;*/

	for (i = 0; i < top; i++) {
		for (j = 0; j < right; j++) {
			if ((i == pos_y) && (j == pos_x))//优先显示写在前面
				cout << "*";
			else if (((i == zidan_y) && (j == zidan_x))) {
					cout << "|";
			}
			else if (((i == enemy_y) && (j == enemy_x))) {
					cout << "$";
			}
			else
			{
				cout << " ";
			}
		}

		cout << endl;
	}
	cout << "得分:" << score << endl;
}

void updata_Input()
{
	if (_kbhit()) {


		ch = _getch();
		if (ch == 'w')
			pos_y--;
		else if (ch == 'a')
			pos_x--;
		else if (ch == 's')
			pos_y++;
		else if (ch == 'd')
			pos_x++;
		else if (ch == ' ')
		{
			zidan_y = pos_y - 1;
			zidan_x = pos_x;
		}
		//手动生成敌机
		//else if (ch == 'k')
		//{
		//	enemy_y = 0;
		//	//随机生成不同位置敌机
		//	enemy_x = rand() % right;
		//}
			
	}
	/*switch (ch)
	{
	case 'w':
		pos_y--; break;
	case 'a':
		pos_x--; break;
	case 's':
		pos_y++; break;
	case 'd':
		pos_x++; break;
	case ' ':
		zidan_y = pos_y - 1;break;
	}*/
}

void updata_No_Input()
{
	if (zidan_y > -1)
		zidan_y--;
	//单独让敌机速度变慢
	static int speed = 0;
	if (speed < 5)
		speed++;
	else {

		//敌机如果到底部，重新生成
		if (enemy_y <= top)
			enemy_y++;
		else {
			enemy_y = 0;
			//随机生成不同位置敌机
			enemy_x = rand() % right;

		}
		speed = 0;
	}
	//子弹击中敌机
	if ((zidan_x == enemy_x) && (zidan_y == enemy_y)) {
		score++;
		zidan_y = -1;
		enemy_y = 0;
		enemy_x = rand() % right;
	}
	if ((pos_x == enemy_x) && (pos_y == enemy_y)) {
		system("cls");
		cout << "Game Over" << endl;
		exit(0);
	}

}

int main()
{
	startup();
	while (true) {
		show();
		updata_No_Input();
		updata_Input();
	}

	return 0;
}
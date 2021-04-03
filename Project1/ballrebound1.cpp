#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>


using std::cout;
using std::cin;
using std::endl;

int pos_x, pos_y;//小球坐标
int v_x, v_y;//速度方向
int top, width;//边界
int ban_x, ban_y;//板中心坐标
int radius;//板半径
int left, right;//板左右边界
char ch;
static int times;

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
	top = 20;
	width = 25;
	pos_x = width / 2;
	pos_y = top / 2;
	v_x = 1;
	v_y = 1;
	ban_x = width / 2;
	ban_y = top - 1;
	radius = 5;
	left = ban_x - radius / 2;
	right = ban_x + radius / 2;
	ch = '\0';
	times = 0;
}

void show()
{
	int i, j;
	//比清屏函数好用
	gotoxy(0, 0);
	//Sleep(500);
	//碰到边界反弹

	for (i = 1; i <= top; i++) {
		for (j = 1; j <= width; j++) {
			if ((i == pos_y) && (j == pos_x))//优先显示写在前面
				cout << "o";//○比o大，所以输出时不同
			else if (j == width) {
				cout << "|";
			}
			else if (i == top) {
				cout << "-";
			}
			else if ((i == ban_y) && ((j >= left) && (j <= right))) {
				cout << "*";
			}
			else {
				cout << " ";
			}

		}

		cout << endl;
	}
}

void updata_Input()
{
	if (_kbhit()) {

		ch = _getch();
		if (ch == 'a') {
			ban_x--;
			left = ban_x - radius / 2;
			right = ban_x + radius / 2;
		}

		else if (ch == 'd') {
			ban_x++;
			left = ban_x - radius / 2;
			right = ban_x + radius / 2;
		}


	}

}

void updata_No_Input()
{

	if (times <= 8) {
		times++;
	}
	else {
		//小球碰到劈面改变方向
		if ((pos_x <= 1) || (pos_x >= width - 1))
			v_x = -1 * v_x;
		if ((pos_y <= 1) || (((pos_y == ban_y - 1)) && (pos_x >= left) && (pos_x <= right)))
			v_y = -1 * v_y;
		/*碰到上界和板是反弹
		*	(((pos_y == ban_y - 1)) && (pos_x >= left - 1) && (v_x >= 0)) || //小球x速度为正从左上角穿过最左的板时可以让它反弹(没加直接穿过了)
		*	(((pos_y == ban_y - 1)) && (pos_x <= right + 1) && (v_x < 0)))//它在往下就碰到板了  x速度为负从右上角穿过最有边同理
		*	
		*	为了能够让小球在挡板同行GameOver  但Bug太多  放弃
		*	
		*/
		
		else if ((pos_y == ban_y - 1) && ((pos_x < left) || (pos_x > right))) {	//没接住小球
			system("cls");
			for (int q = 0; q < 20; q++) {
				for (int p = 0; p < 25; p++) {
					if ((q == 10) && (p == 25 / 2))
						cout << "Game Over!!!";
					else
						cout << " ";
				}
				cout << endl;
			}

			exit(0);
		}
		pos_x += v_x;
		pos_y += v_y;
		times = 0;
	}



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
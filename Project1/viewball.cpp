#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <graphics.h>


using std::cout;
using std::cin;
using std::endl;

#define size 25

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

}

void show()
{
	//int i, j;
	//比清屏函数好用
	//gotoxy(0, 0);
	initgraph(600, 600);
	setbkcolor(YELLOW);
	cleardevice();
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if ((i + j) % 2 == 1) {
				setcolor(BLACK);
				solidrectangle(i * size, j * size, (i + 1) * size, (j + 1) * size);
			}
			else {
				setcolor(WHITE);
				solidrectangle(i * size, j * size, (i + 1) * size, (j + 1) * size);
			}

		}

	}
	_getch();
	closegraph();
}

void updata_Input()
{

}

void updata_No_Input()
{

}

int main()
{
	/*startup();
	while (true) {
		show();
		updata_Input();
		updata_No_Input();
	}*/
	show();
	return 0;
}
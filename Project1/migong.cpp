#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

using std::cin;
using std::cout;
using std::endl;

#define width 14
#define high 12
int maze[high][width] = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1,
      1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1,
      1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1,
      1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1,
      1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1,
      1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1,
      1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1,
      1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1,
      1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  };
int x = 1, y = 1;


void gotoxy(int x, int y)  //光标移动到(x,y)位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}


void show()  // 显示画面
{
	gotoxy(0, 0);  // 光标移动到原点位置，以下重画清屏
	int i, j;
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (maze[i][j] == 1)
				cout << "o";
			else if (maze[i][j] == 2)
				cout << "x";
			else
				cout << " ";
		}
		cout << endl;
	}
	Sleep(20);
}

void updateWithoutInput()
{
	maze[1][1] = 2;
}

void updateWithInput()
{
	char ch;
	if (_kbhit())
	{
		ch = _getch();
		if (ch == 'a') {
			maze[x][y] = 0;
			x--;
			maze[y][x] = 2;
		}
		else if (ch == 'd') {
			maze[x][y] = 0;
			x++;
			maze[y][x] = 2;
		}
		else if (ch == 'w') {
			maze[x][y] = 0;
			y--;
			maze[y][x] = 2;
		}
		else if (ch == 's') {
			maze[x][y] = 0;
			y++;
			maze[y][x] = 2;
		}
	}
}

int main()
{
	while (1) 
	{
		updateWithoutInput();
		show();   
		updateWithInput();
	}
	return 0;
	

}
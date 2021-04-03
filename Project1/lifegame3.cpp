#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>


using std::cout;
using std::cin;
using std::endl;

const int x = 20;
const int y = 30;
int cells[x][y];//С������
int top, width;//�߽�

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
	top = 20;
	width = 25;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cells[i][j] = rand() % 2;
		}
	}
}

void show()
{
	int i, j;
	//��������������
	gotoxy(0, 0);

	for (i = 1; i <= top; i++) {
		for (j = 1; j <= width; j++) {
			if (cells[i][j]==1)//������ʾд��ǰ��
				cout << "o";//���o���������ʱ��ͬ
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}

void updata_Input()
{
	/*if (_kbhit()) {

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


	}*/

}

void updata_No_Input()
{
	int neighbor = 0;
	int temp[x][y];
	for (int i = 1; i < x - 1; i++) {
		for (int j = 1; j < y - 1; j++) {
			neighbor = cells[i - 1][j - 1] + cells[i - 1][j] + cells[i - 1][j + 1] +
				cells[i][j - 1] + cells[i][j] + cells[i][j + 1] +
				cells[i + 1][j - 1] + cells[i + 1][j] + cells[i + 1][j + 1];
			if (neighbor == 3)
				temp[i][j] = 1;
			else if (neighbor == 2)
				temp[i][j] = cells[i][j];
			else {
				temp[i][j] = 0;
			}
		}
	}
	for (int i = 1; i < x-1; i++) {
		for (int j = 1; j < y-1; j++) {
			cells[i][j] = temp[i][j];
		}
	}
	Sleep(500);
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
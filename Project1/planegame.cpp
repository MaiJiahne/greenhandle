#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int x = 10;
	int y = 15;
	int ny = 5;
	const char ch[4] = { 'w','a','s','d' };
	char tch = '\0';
	int i, j;
	int isFire = 0;
	int isKill = 0;
	while (true) {
		system("cls");

		//避免到顶部坐标还在加
		if (x < 0)
			x = 0;
		if (y < 0)
			y = 0;
		//是否开火分开输出
		if (isFire == 1) {
			if ((y + 1) == ny)
				isKill = 1;
			if (!isKill) {
				for (j = 0; j < ny; j++) {
					cout << "  ";
				}
				cout << "+" << endl;
			}
			else {
				for (j = 0; j < ny; j++) {
					cout << "  ";
				}
				cout << endl;
				isKill = 0;
				ny = rand() % 11 + 1;//随机生成位置，+1为了能让子弹打到
			}
			for (i = 0; i < x; i++)
			{
				for (int t = 0; t < y; t++)
					cout << "  ";
				cout << "  |\n";
			}
			//关掉子弹
			isFire = 0;
		}
		else {
			for (j = 0; j < ny; j++) {
				cout << "  ";
			}
			cout << "+" << endl;
			for (i = 0; i < x; i++)
				cout << "\n";

		}
		for (j = 0; j < y; j++)
			cout << "  ";
		cout << "  *" << endl;
		for (j = 0; j < y; j++)
			cout << "  ";
		cout << "*****" << endl;
		for (j = 0; j < y; j++)
			cout << "  ";
		cout << " * *  " << endl;
		tch = _getch();
		switch (tch) {
		case 'w':
			x--; break;
		case 'a':
			y--; break;
		case 's':
			x++; break;
		case 'd':
			y++; break;
		case ' ':
		{
			isFire = 1;
			/*
			*
			*  手动控制子弹开关
			*
			*/
			/*if (isFire == 0)
				isFire = 1;
			else
			{
				isFire = 0;
			}
			break;*/
		}
		}
	}
}
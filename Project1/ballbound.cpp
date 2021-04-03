#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int x = 3;
	int y = 3;
	int v_x = 1;//方向
	int v_y = 1;
	int left = 1, right = 37;//边界
	int top = 1, bottom = 15;
	int i, j, t;
	while (true) {
		/*
		*碰到边界方向变反，相当弹回
		*
		*/
		if ((x == top) || (x == bottom))
			v_x = -1 * v_x;
		x += v_x;
		if ((y == left) || (y == right))
			v_y = -1 * v_y;
		y += v_y;
		system("cls");
		for (int area = 0; area <= 38; area++)
			cout << "▃";
		cout << endl;
		for (i = 0; i < x; i++) {
			cout << "丨";
			for (t = 0; t < right; t++)
				cout << "  ";
			cout << "丨\n";
		}
		cout << "丨";
		for (j = 1; j < y; j++)
			cout << "  ";
		cout << "○";
		for (j; j < right; j++)
			cout << "  ";
		cout << "丨" << endl;
		for (; i <= bottom; i++) {
			cout << "丨";
			for (t = 0; t < right; t++)
				cout << "  ";
			cout << "丨\n";
		}
		for (int k = 0; k <= 38; k++)
			cout << "▃";
		Sleep(50);
	}
}
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
	int v_x = 1;//����
	int v_y = 1;
	int left = 1, right = 37;//�߽�
	int top = 1, bottom = 15;
	int i, j, t;
	while (true) {
		/*
		*�����߽緽��䷴���൱����
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
			cout << "�z";
		cout << endl;
		for (i = 0; i < x; i++) {
			cout << "ح";
			for (t = 0; t < right; t++)
				cout << "  ";
			cout << "ح\n";
		}
		cout << "ح";
		for (j = 1; j < y; j++)
			cout << "  ";
		cout << "��";
		for (j; j < right; j++)
			cout << "  ";
		cout << "ح" << endl;
		for (; i <= bottom; i++) {
			cout << "ح";
			for (t = 0; t < right; t++)
				cout << "  ";
			cout << "ح\n";
		}
		for (int k = 0; k <= 38; k++)
			cout << "�z";
		Sleep(50);
	}
}
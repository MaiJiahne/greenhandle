#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	initgraph(1200, 800);
	setbkcolor(YELLOW);
	//Œß∆Â∆Â≈Ã
	/*for (int i = 30; i <= 31 * 19; i += 30) {
		line(50, i, 31 * 19, i);

	}
	for (int j = 50; j < 30 * 19 + 50; j += 30) {
		line(j, 30, j, 30 * 19);
	}*/
	/*for (int i = 50; i <= 50 + 6 * 30; i++) {
		for (int j = 30; j <= 30 * 7; j++) {
			if ((i == 50 + 6 * 30) && (j == 30 * 7))
				putpixel(i, j, RED);
		}
	}*/
	//¥ÌŒÛπ˙º œÛ∆Â∆Â≈Ã
	/*for (int j = 0; j < 9; j++) {
		for (int i = 40; i <= 40 * 9; i += 40) {
			if ((i / 40) % 2)
				setfillcolor(RED);
			else
				setfillcolor(GREEN);
			solidrectangle(i, 40 * sqrt(2) + 40 + 40 * j, i + 40, 40 * sqrt(2) + 40 * j);

		}
		cout << endl;
	}*/







	_getch();
	closegraph();



	return 0;
}
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>


using std::cout;
using std::cin;
using std::endl;

int pos_x, pos_y;//�ɻ�����
int top, right;//�߽�
int zidan_x, zidan_y;//�ӵ�����
int enemy_x, enemy_y;//�л�����
int score = 0;//�÷�
int isKilled = 0;
char ch = '\0';

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
	//��������������
	gotoxy(0, 0);
	//Sleep(500);
	//�����߽粻Ҫ��������
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
			if ((i == pos_y) && (j == pos_x))//������ʾд��ǰ��
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
	cout << "�÷�:" << score << endl;
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
		//�ֶ����ɵл�
		//else if (ch == 'k')
		//{
		//	enemy_y = 0;
		//	//������ɲ�ͬλ�õл�
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
	//�����õл��ٶȱ���
	static int speed = 0;
	if (speed < 5)
		speed++;
	else {

		//�л�������ײ�����������
		if (enemy_y <= top)
			enemy_y++;
		else {
			enemy_y = 0;
			//������ɲ�ͬλ�õл�
			enemy_x = rand() % right;

		}
		speed = 0;
	}
	//�ӵ����ел�
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
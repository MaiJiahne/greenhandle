#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>


using std::cout;
using std::cin;
using std::endl;

int pos_x, pos_y;//С������
int v_x, v_y;//�ٶȷ���
int top, width;//�߽�
int ban_x, ban_y;//����������
int radius;//��뾶
int left, right;//�����ұ߽�
char ch;
static int times;

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
	//��������������
	gotoxy(0, 0);
	//Sleep(500);
	//�����߽練��

	for (i = 1; i <= top; i++) {
		for (j = 1; j <= width; j++) {
			if ((i == pos_y) && (j == pos_x))//������ʾд��ǰ��
				cout << "o";//���o���������ʱ��ͬ
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
		//С����������ı䷽��
		if ((pos_x <= 1) || (pos_x >= width - 1))
			v_x = -1 * v_x;
		if ((pos_y <= 1) || (((pos_y == ban_y - 1)) && (pos_x >= left) && (pos_x <= right)))
			v_y = -1 * v_y;
		/*�����Ͻ�Ͱ��Ƿ���
		*	(((pos_y == ban_y - 1)) && (pos_x >= left - 1) && (v_x >= 0)) || //С��x�ٶ�Ϊ�������ϽǴ�������İ�ʱ������������(û��ֱ�Ӵ�����)
		*	(((pos_y == ban_y - 1)) && (pos_x <= right + 1) && (v_x < 0)))//�������¾���������  x�ٶ�Ϊ�������ϽǴ������б�ͬ��
		*	
		*	Ϊ���ܹ���С���ڵ���ͬ��GameOver  ��Bug̫��  ����
		*	
		*/
		
		else if ((pos_y == ban_y - 1) && ((pos_x < left) || (pos_x > right))) {	//û��סС��
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
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>


using std::cout;
using std::cin;
using std::endl;

const int x = 35;
const int y = 25;
int canvas[y][x] = { 0 };//�����������Ϣ�洢��������
int top, width;//�߽�
int pos_x, pos_y;//��ͷ����
int moveDirection;//����
int snake_length_begin;//��ʼ����
int eatOneself;//�Ƿ�Ե�����
int food_x, food_y;	//ʳ������
int isEat;

char ch;

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
	top = y;
	width = x;
	pos_x = width / 2;
	pos_y = top / 2;
	snake_length_begin = 5;
	ch = '\0';
	moveDirection = 4;
	eatOneself = 0;
	isEat = 0;
	food_x = rand() % (width - 2) + 1;
	food_y = rand() % (top - 2) + 1;
	canvas[food_y][food_x] = -2;


	for (int i = 0; i < top; i++) {
		canvas[i][0] = -1;
		canvas[i][width - 1] = -1;
	}
	for (int j = 0; j < width; j++) {
		canvas[0][j] = -1;
		canvas[top - 1][j] = -1;
	}
	canvas[pos_y][pos_x] = 1;
	for (int i = 1; i <= snake_length_begin; i++) {
		canvas[pos_y][pos_x - i] = i + 1;
	}
}

void Move()
{
	int  old_tail_x = 0, old_tail_y = 0;
	int max = 0;

	for (int i = 1; i < top - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			if (canvas[i][j] > 0)
				canvas[i][j]++;		//�����߿����۵���������
			if (max < canvas[i][j]) {
				max = canvas[i][j];
				old_tail_x = j;
				old_tail_y = i;
			}

		}
	}

	if (moveDirection == 1) {		//�����ƶ�
		pos_y--;
		if (canvas[pos_y][pos_x] > 1)		//�Ե�����,ֱ���жϴ���1
			eatOneself = 1;
		if (canvas[pos_y][pos_x] == -2)		//�Ե�ʳ��
			isEat = 1;
		canvas[pos_y][pos_x] = 1;
	}
	if (moveDirection == 2) {		//�����ƶ�
		pos_y++;
		if (canvas[pos_y][pos_x] > 1)
			eatOneself = 1;
		if (canvas[pos_y][pos_x] == -2)
			isEat = 1;
		canvas[pos_y][pos_x] = 1;
	}
	if (moveDirection == 3) {		//�����ƶ�
		pos_x--;
		if (canvas[pos_y][pos_x] > 1)
			eatOneself = 1;
		if (canvas[pos_y][pos_x] == -2)
			isEat = 1;
		canvas[pos_y][pos_x] = 1;
	}
	if (moveDirection == 4) {		//�����ƶ�
		pos_x++;
		if (canvas[pos_y][pos_x] > 1)
			eatOneself = 1;
		if (canvas[pos_y][pos_x] == -2)
			isEat = 1;
		canvas[pos_y][pos_x] = 1;
	}


	if (isEat == 1) {
		food_x = rand() % (width - 2) + 1;		//��������ʳ��
		food_y = rand() % (top - 2) + 1;
		canvas[food_y][food_x] = -2;
		isEat = 0;
		//���ȼ�1  ������β���һ��
	}
	else
		canvas[old_tail_y][old_tail_x] = 0;


	if ((pos_x >= width - 1) || (pos_x <= 0) || (pos_y >= top - 1) || (pos_y <= 0) || (eatOneself == 1)) {	//ײ���߽�����������Ϸ
		system("cls");
		for (int t = 0; t < top / 2; t++) {
			cout << '\n';
		}
		for (int y = 0; y < width / 2; y++) {
			cout << ' ';
		}
		cout << "Game Over";
		for (int t = 0; t < top / 2; t++) {
			cout << '\n';
		}
		exit(0);
	}

}
void show()
{
	int i, j;
	//��������������
	gotoxy(0, 0);

	Sleep(100);
	for (i = 0; i < top; i++) {
		for (j = 0; j < width; j++) {
			if (canvas[i][j] == -1)
				cout << '#';	//�߽�
			else if (canvas[i][j] == 1)
				cout << '@';		//��ͷ
			else if (canvas[i][j] >= 2)
				cout << '*';	//����
			else if (canvas[i][j] == -2)
				cout << 'F';	//ʳ��
			else if (canvas[i][j] == 0)
				cout << ' ';

		}
		cout << endl;
	}
	//cout << "�÷֣�" << score << endl;
}

void updata_Input()
{
	if (_kbhit()) {

		ch = _getch();

		if (ch == 'a') {
			moveDirection = 3;
		}
		else if (ch == 'd') {
			moveDirection = 4;
		}
		else if (ch == 'w') {
			moveDirection = 1;
		}
		else if (ch == 's') {
			moveDirection = 2;
		}
	}
}

void updata_No_Input()
{

	Move();

	/*static int i = 0;
	if (i <= 5) {
		i++;
	}
	else {


		i = 0;
	}*/

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






//Note
//�������������������ڣ�����̨��С������ı߽粻ƥ��  ����߽������⣬����1������1  �����п������
/*
*		��һ��
*		for (int t = 0; t < top / 2; t++) {
*			cout << '\n';
*		}
*		for (int y = 0; y < width / 2; y++) {
*			cout << ' ';
*		}
*		�������ǵ��������ȵڶ�������canvas��
*/
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>


using std::cout;
using std::cin;
using std::endl;

const int x = 35;
const int y = 25;
int canvas[y][x] = { 0 };//将所以输出信息存储在数组中
int top, width;//边界
int pos_x, pos_y;//虫头坐标
int moveDirection;//方向
int snake_length_begin;//初始长度
int eatOneself;//是否吃到蛇身
int food_x, food_y;	//食物坐标
int isEat;

char ch;

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
				canvas[i][j]++;		//这样蛇可以折叠，还方便
			if (max < canvas[i][j]) {
				max = canvas[i][j];
				old_tail_x = j;
				old_tail_y = i;
			}

		}
	}

	if (moveDirection == 1) {		//向上移动
		pos_y--;
		if (canvas[pos_y][pos_x] > 1)		//吃到蛇身,直接判断大于1
			eatOneself = 1;
		if (canvas[pos_y][pos_x] == -2)		//吃到食物
			isEat = 1;
		canvas[pos_y][pos_x] = 1;
	}
	if (moveDirection == 2) {		//向下移动
		pos_y++;
		if (canvas[pos_y][pos_x] > 1)
			eatOneself = 1;
		if (canvas[pos_y][pos_x] == -2)
			isEat = 1;
		canvas[pos_y][pos_x] = 1;
	}
	if (moveDirection == 3) {		//向左移动
		pos_x--;
		if (canvas[pos_y][pos_x] > 1)
			eatOneself = 1;
		if (canvas[pos_y][pos_x] == -2)
			isEat = 1;
		canvas[pos_y][pos_x] = 1;
	}
	if (moveDirection == 4) {		//向右移动
		pos_x++;
		if (canvas[pos_y][pos_x] > 1)
			eatOneself = 1;
		if (canvas[pos_y][pos_x] == -2)
			isEat = 1;
		canvas[pos_y][pos_x] = 1;
	}


	if (isEat == 1) {
		food_x = rand() % (width - 2) + 1;		//重新生成食物
		food_y = rand() % (top - 2) + 1;
		canvas[food_y][food_x] = -2;
		isEat = 0;
		//长度加1  保留蛇尾最后一个
	}
	else
		canvas[old_tail_y][old_tail_x] = 0;


	if ((pos_x >= width - 1) || (pos_x <= 0) || (pos_y >= top - 1) || (pos_y <= 0) || (eatOneself == 1)) {	//撞到边界或蛇身结束游戏
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
	//比清屏函数好用
	gotoxy(0, 0);

	Sleep(100);
	for (i = 0; i < top; i++) {
		for (j = 0; j < width; j++) {
			if (canvas[i][j] == -1)
				cout << '#';	//边界
			else if (canvas[i][j] == 1)
				cout << '@';		//蛇头
			else if (canvas[i][j] >= 2)
				cout << '*';	//蛇身
			else if (canvas[i][j] == -2)
				cout << 'F';	//食物
			else if (canvas[i][j] == 0)
				cout << ' ';

		}
		cout << endl;
	}
	//cout << "得分：" << score << endl;
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
//输出有问题基本都出现在：控制台大小和输出的边界不匹配  输出边界有问题，多了1或少了1  数组有可能溢出
/*
*		第一代
*		for (int t = 0; t < top / 2; t++) {
*			cout << '\n';
*		}
*		for (int y = 0; y < width / 2; y++) {
*			cout << ' ';
*		}
*		本代码是第三代（比第二代多了canvas）
*/
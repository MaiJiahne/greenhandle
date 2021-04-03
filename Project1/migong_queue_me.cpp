#include <iostream>

using std::cin;
using std::cout;
using std::endl;

//˳�����
#define MAXSIZE 50
struct path
{
	int x;
	int y;
	int pre;
};
class Queue {
public:
	int front;
	int rear;
	path point[MAXSIZE];

	Queue() :front(0), rear(0), point() {}
	~Queue() = default;
	void Enque(path);
	bool Deque();
	bool getHead(path&);
	void show();
};

//���
void Queue::Enque(path l)
{
	if ((rear + 1) % MAXSIZE == front) {
		cout << "��������" << endl;
	}
	else {
		point[++rear] = l;
	}
}

//����
bool Queue::Deque()
{
	if (front == rear) {    //��һ��ͷ���
		cout << "����Ϊ��" << endl;
		return false;
	}
	else {
		++front;
		return true;
	}
}

//���ض�ͷԪ��
bool Queue::getHead(path& l) {
	if (front == rear) {    //��һ��ͷ���
		cout << "����Ϊ��" << endl;
		return false;
	}
	else {
		l = point[front + 1];
		return true;
	}
}

//��������
void Queue::show()
{
	if (front == rear) {    //��һ��ͷ���
		cout << "����Ϊ��" << endl;
	}
	else {
		for (int i = front; i <= rear; i++) {
			cout << point[i].x << " " << point[i].y << " " << point[i].pre << " " << endl;
		}
	}

}

int main()
{
	int maze[10][10] =
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,1,0,0,0,1,0,1},
		{1,0,0,1,0,0,0,1,0,1},
		{1,0,0,0,0,1,1,0,0,1},
		{1,0,1,1,1,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,1},
		{1,0,1,0,0,0,1,0,0,1},
		{1,0,1,1,1,0,1,1,0,1},
		{1,1,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};
	Queue que;
	path l = { 2,3,-1 };
	path l1 = { 2,1,0 };
	path l2 = { 5,8,1 };
	path l3 = { 3,2,2 };
	que.Deque();
	que.Enque(l);
	que.Enque(l1);
	que.Enque(l2);
	que.Enque(l3);
	que.show();

	que.Deque();
	que.show();





}
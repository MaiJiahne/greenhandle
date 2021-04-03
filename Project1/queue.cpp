#include "queue.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


//析构函数
Queue::~Queue()
{
	int num = 0;//结点数量
	if (front) {
		while (front) {
			QueueNode* d = front;
			if(front == rear){
				rear = nullptr;
			}
			front = front->next;
			delete d;
			cout << "删掉第" << ++num << "个结点" << "	";
		}
		cout << endl;
	}
}

//判断队列是否为空
bool Queue::empty()
{
	if (!rear)
		return true;
	else
		return false;
}
//入队
void Queue::Enque(int x)
{
	if(empty()){
		rear = new QueueNode;
		rear->data = x;
		rear->next = nullptr;
		front = rear;
	}
	else{
		rear->next = new QueueNode;
		rear = rear->next;
		rear->data = x;
		rear->next = nullptr;
	}
}

//出队
bool Queue::Deque()
{
	if(empty()){
		cout<<"此队列为空"<<endl;
		return false;
	}
	else{
		QueueNode* d = front;
		//只有一个结点
		if(front  == rear){
			front = nullptr;
			rear = nullptr;
		}
		else{
			front = front->next;
		}
		delete d;
		return true;
	}
}

//返回队头元素
bool Queue::getHead(int& e)
{
	if(empty()){
		cout<<"此队列为空"<<endl;
		return false;
	}
	else{
		e = front->data;
		return true;
	}
}

//遍历队列
void Queue::showQueue()
{
	if (empty()) {
		cout << "此队列为空" << endl;
	}
	else {
		cout << "队列为：";
		QueueNode* p = front;
		while (p) {
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
}

//删除整个队列
void Queue::delete_que()
{
	if (front) {
		while (front) {
			QueueNode* d = front;
			if(front == rear){
				rear = nullptr;
			}
			front = front->next;
			delete d;
		}
	}
}

//添加三个随机数到队列中
void Queue::addThreeRandNum()
{
	srand(time(0));
	for(int i = 0; i < 3; i++)
	{
		int Rnum = rand() % 800 +  100; 
		Enque(Rnum);
	}
}

//利用出队入队遍历整个队列
void Queue::show()
{
	if (empty()) {
		cout << "此队列为空" << endl;
	}
	else {
		vector<int> ivec;
		int temp;
		while (front) {
			getHead(temp);
			cout << temp << " ";
			ivec.push_back(temp);
			Deque();
		}
		cout << endl;

		for (auto& i : ivec) {
			Enque(i);
		}

	}
}

//翻转队列
void Queue::reverse()
{
	if (empty()) {
		cout << "此队列为空,不能进行翻转操作" << endl;
	}
	else if(!front->next){
		cout << "队列只有一个结点，不用进行翻转操作" << endl;
	}
	else{
		//设置一个向量存储队列内容，在反方向入队队列
		QueueNode* p = front;
		vector<int> ivec;
		while (p) {
			ivec.push_back(p->data);
			p = p->next;
		}
		delete_que();
		for (auto beg = ivec.crbegin(); beg != ivec.crend(); ++beg) {
			Enque(*beg);
		}
	}
}
#include "queue.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


//��������
Queue::~Queue()
{
	int num = 0;//�������
	if (front) {
		while (front) {
			QueueNode* d = front;
			if(front == rear){
				rear = nullptr;
			}
			front = front->next;
			delete d;
			cout << "ɾ����" << ++num << "�����" << "	";
		}
		cout << endl;
	}
}

//�ж϶����Ƿ�Ϊ��
bool Queue::empty()
{
	if (!rear)
		return true;
	else
		return false;
}
//���
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

//����
bool Queue::Deque()
{
	if(empty()){
		cout<<"�˶���Ϊ��"<<endl;
		return false;
	}
	else{
		QueueNode* d = front;
		//ֻ��һ�����
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

//���ض�ͷԪ��
bool Queue::getHead(int& e)
{
	if(empty()){
		cout<<"�˶���Ϊ��"<<endl;
		return false;
	}
	else{
		e = front->data;
		return true;
	}
}

//��������
void Queue::showQueue()
{
	if (empty()) {
		cout << "�˶���Ϊ��" << endl;
	}
	else {
		cout << "����Ϊ��";
		QueueNode* p = front;
		while (p) {
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
}

//ɾ����������
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

//��������������������
void Queue::addThreeRandNum()
{
	srand(time(0));
	for(int i = 0; i < 3; i++)
	{
		int Rnum = rand() % 800 +  100; 
		Enque(Rnum);
	}
}

//���ó�����ӱ�����������
void Queue::show()
{
	if (empty()) {
		cout << "�˶���Ϊ��" << endl;
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

//��ת����
void Queue::reverse()
{
	if (empty()) {
		cout << "�˶���Ϊ��,���ܽ��з�ת����" << endl;
	}
	else if(!front->next){
		cout << "����ֻ��һ����㣬���ý��з�ת����" << endl;
	}
	else{
		//����һ�������洢�������ݣ��ڷ�������Ӷ���
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
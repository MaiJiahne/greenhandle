#include "stack_rd.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

stack::~stack()
{
	int num = 0;//�������
	if (top) {
		while (top) {
			stackNode* d = top;
			top = top->next;
			delete d;
			cout << "ɾ��ջ����" << ++num << "�����" << "	";
		}
		cout << endl;
	}
}

//�ж��Ƿ�ջ��
bool stack::empty()
{
	if (!top)
		return true;
	else
		return false;
}

//����ջ��Ԫ�أ����ջΪ�գ��򷵻�int����ʾ�����ֵ
bool stack::Top(int& e)
{
	if (empty()) {
		cout << "��ջΪ��" << endl;
		return  false;
	}
	else {
		e = top->data;
		return true;
	}
}

//��ջ����
void stack::Push(int x)
{
	if (empty()) {
		top = new stackNode;
		top->data = x;
		top->next = nullptr;
	}
	else {
		stackNode* p = new stackNode;
		p->data = x;
		p->next = top;
		top = p;
	}
}

//��ջ����
bool stack::Pop()
{
	if (empty()) {
		cout << "��ջΪ��" << endl;
		return false;
	}
	else {
		stackNode* d = top;
		top = top->next;
		delete d;
		return true;
	}
}

//�����������ջ������鿴����
void stack::show()
{
	if (empty()) {
		cout << "��ջΪ��" << endl;
	}
	else {
		cout << "��ջԪ��Ϊ��";
		vector<int> ivec;
		stackNode* p = top;
		while (p) {
			ivec.push_back(p->data);
			p = p->next;
		}
		for (auto beg = ivec.crbegin(); beg != ivec.crend(); ++beg) {
			cout << *beg << " ";
		}
		cout << endl;
	}
}

//�����������ջ
void stack::addThreeRandowNum()
{
	srand(time(0));
	for (int i = 0; i < 3; i++) {
		int RandNum = rand() % 800 + 100;
		Push(RandNum);
	}
}

//Ӧ�ó�ջ���ջ������
void stack::showStack()
{
	if (empty()) {
		cout << "��ջΪ��" << endl;
	}
	else {
		vector<int> ivec;
		int top_;
		while (top) {
			Top(top_);
			cout << top_ << "	";	//��ջ�����
			ivec.push_back(top_);	//ÿ��Ԫ�ش��������У�˳��Ϊ��
			Pop();
		}
		cout << endl;
		for (auto beg = ivec.crbegin(); beg != ivec.crend(); ++beg) {	//ջ��ʱΪ�գ����ô���������Ԫ�ص���������ջ
			Push(*beg);
		}
	}
}
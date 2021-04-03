#include "stack_st.h"
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

//����ջ��Ԫ�أ����ջΪ�գ��򷵻�int����ʾ�����ֵ
int stack::Top()
{
	if (!top) {
		cout << "��ջΪ��" << endl;
		return  2147483647;
	}
	else {
		return top->data;
	}
}

//��ջ����
void stack::Push(int x)
{
	if (!top) {
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

//�����������ջ������鿴����
void stack::show()
{
	if (!top) {
		cout << "��ջΪ��" << endl;
	}
	else {
		vector<int> ivec;
		stackNode* p = top;
		while (p) {
			ivec.push_back(p->data);
			p = p->next;
		}
		for (auto beg = ivec.crbegin(); beg != ivec.crend(); ++beg) {
			cout << *beg << "	";
		}
		cout << endl;
	}
}

//��ջ����
void stack::Pop()
{
	if (!top) {
		cout << "��ջΪ��" << endl;
	}
	else {
		stackNode* d = top;
		top = top->next;
		delete d;
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
	if (!top) {
		cout << "��ջΪ��" << endl;
	}
	else {
		vector<int> ivec;
		while (top) {
			cout << Top() << "	";	//��ջ�����
			ivec.push_back(Top());	//ÿ��Ԫ�ش��������У�˳��Ϊ��
			Pop();
		}
		cout << endl;
		for (auto beg = ivec.crbegin(); beg != ivec.crend(); ++beg) {	//ջ��ʱΪ�գ����ô���������Ԫ�ص���������ջ
			Push(*beg);
		}
	}
}
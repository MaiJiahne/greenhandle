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
	int num = 0;//结点数量
	if (top) {
		while (top) {
			stackNode* d = top;
			top = top->next;
			delete d;
			cout << "删掉栈顶第" << ++num << "个结点" << "	";
		}
		cout << endl;
	}
}

//返回栈顶元素，如果栈为空，则返回int所表示的最大值
int stack::Top()
{
	if (!top) {
		cout << "此栈为空" << endl;
		return  2147483647;
	}
	else {
		return top->data;
	}
}

//入栈操作
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

//正序遍历整个栈，方便查看数据
void stack::show()
{
	if (!top) {
		cout << "此栈为空" << endl;
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

//出栈操作
void stack::Pop()
{
	if (!top) {
		cout << "此栈为空" << endl;
	}
	else {
		stackNode* d = top;
		top = top->next;
		delete d;
	}
}

//生三个随机入栈
void stack::addThreeRandowNum()
{
	srand(time(0));
	for (int i = 0; i < 3; i++) {
		int RandNum = rand() % 800 + 100;
		Push(RandNum);
	}
}

//应用出栈输出栈的内容
void stack::showStack()
{
	if (!top) {
		cout << "此栈为空" << endl;
	}
	else {
		vector<int> ivec;
		while (top) {
			cout << Top() << "	";	//从栈顶输出
			ivec.push_back(Top());	//每个元素存入向量中，顺序为反
			Pop();
		}
		cout << endl;
		for (auto beg = ivec.crbegin(); beg != ivec.crend(); ++beg) {	//栈此时为空，在用存在向量的元素倒序重新入栈
			Push(*beg);
		}
	}
}
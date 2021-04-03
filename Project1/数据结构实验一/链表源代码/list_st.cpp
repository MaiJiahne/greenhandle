#include "list_st.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


//析构整个链表
List::~List()
{
	int num = 0;//结点数量
	if (head) {
		while (head) {
			ListNode* d = head;
			head = head->next;
			delete d;
			cout << "删掉第" << ++num << "个结点" << "	";
		}
		cout << endl;
	}
}

//创建链表		以 x 为初始值创建一个结点的链表
void List::createList(int x)
{
	head = new ListNode;
	head->data = x;
	head->next = nullptr;
}

//遍历整个链表
void List::showList()
{
	if (!head) {
		cout << "此链表为空" << endl;
	}
	else {
		ListNode* p = head;
		while (p) {
			cout << p->data << "	";
			p = p->next;
		}
		cout << endl;
	}
}

//查找一个整数是否在链表中，返回 -1 表示不在链表里,返回大于 0 的数表示第一个值为 x 数的位置
int List::find(int x)
{
	if (!head) {
		return -1;
	}
	else {
		ListNode* p = head;
		int pos = 1;	// x 的位置
		while (p) {
			if (p->data == x) {
				return pos;
			}
			else {
				p = p->next;
				pos++;
			}
		}
		return -1;
	}

}

//链表插入操作		插入 num 位置之后	插入 0 位置表示插入头结点之前  空链表时插入 1 之后是不合法的
void List::Insert(int num, int x)	
{
	int pos = 1;	// p 指针位置
	ListNode* p = head;
	while (p && pos < num) {
		p = p->next;
		pos++;
	}
	if (!head && num == 0) {	//空链表
		head = new ListNode;
		head->data = x;
		head->next = nullptr;
	}
	else if (!p || num < 0) {
		cout << "位置不合法" << endl;
	}
	else {
		ListNode* s = new ListNode;
		s->data = x;
		if (num == 0) {
			s->next = p;
			head = s;
		}
		else {
			s->next = p->next;
			p->next = s;
		}
	}

}


//链表删除操作,删除参数位置数据
void List::Delete_pos(int num)	//删除第 num 的结点
{
	if (!head) {
		cout << "此链表为空" << endl;
		//exit(0);
	}
	else {
		ListNode* p = head;
		int pos = 1;	// p 指针位置
		while (p && pos < num - 1) {		//循环结束 p 指向要删除结点的前驱（num 在正常范围下）
			p = p->next;
			pos++;
		}
		if (p == nullptr || (num <= 0)) {
			cout << "位置不合法" << endl;
			exit(0);
		}
		if (num == 1) {		//删除头结点
			head = head->next;
			delete p;
		}
		else if (p->next == nullptr) {		//当不为空指针时，刚好为超出一位
			cout << "位置不合法" << endl;
			exit(0);
		}
		else {
			ListNode* d = p->next;
			p->next = d->next;
			delete d;
		}
	}
}

//链表删除操作,删除第一个跟参数数值相同数据
void List::Delete_value(int x)
{
	if (!head) {
		cout << "此链表为空" << endl;
	}
	else if (head->data == x) {
		ListNode* p = head;
		head = head->next;
		delete p;
	}
	else {
		//设置快慢指针
		bool isExist = false;	//是否存在值相等的值
		ListNode* p = head->next;
		ListNode* q = head;
		while (p) {
			if (p->data == x) {
				isExist = true;
				q->next = p->next;
				delete p;
				break;
			}
			else {
				p = p->next;
				q = q->next;
			}
		}
		if (!isExist) {
			cout << "链表中没有" << x << "数值的数据" << endl;
		}
	}
	//如果链表不为空，输出链表内容
	if (head)
	{
		showList();
	}
}

//删除整个链表
void List::Delete_list()
{
	if (head) {
		while (head) {
			ListNode* d = head;
			head = head->next;
			delete d;
		}
	}
	else {
		cout << "链表已空" << endl;
	}
}

//链表添加三个随机数,分别插入表头
void List::AddThreeRandomNum()
{
	srand(time(0));
	for (int i = 0; i < 3; i++) {
		int RandomNum = rand() % 900 + 100;
		Insert(0, RandomNum);
	}
}

//将链表翻转
void List::reverse()
{
	if (!head) {
		cout << "此链表为空,不能进行翻转操作" << endl;
	}
	else if(!head->next){
		cout << "链表只有一个结点，不用进行翻转操作" << endl;
	}
	else {
		//设置一个向量存储链表内容，在反方向插入链表
		ListNode* p = head;
		vector<int> ivec;
		while (p) {
			ivec.push_back(p->data);
			p = p->next;
		}
		Delete_list();
		//将第一个数据先插入表头，最终成链末的数据
		for (auto& i : ivec) {
			Insert(0, i);
		}
		showList();
	}
}

/*
*用随机函数生成10个3位整数(100~999)，把这些整数存于单链表中，
*然后读入一个整数，以该值为基准把单链表分割为两部分，所有小
*于该值的结点排在大于或等于该值的结点之前。
*/
void List::sort_value(int x)
{
	AddThreeRandomNum();
	ListNode* head_temp = new ListNode;		//临时链表,将链表分类暂时存放
	ListNode* s = nullptr;	//用来创建结点
	ListNode* p = head;	
	head_temp->data = x;
	head_temp->next = nullptr;
	ListNode* division = head_temp;	//值为x，作为分隔点
	while (p) {
		if (p->data < x) {	//小于插入链表头
			s = new ListNode;
			s->data = p->data;
			s->next = head_temp;
			head_temp = s;
			p = p->next;
		}
		else {	//大于等于插入分隔点之后
			s = new ListNode;
			s->data = p->data;
			s->next = division->next;
			division->next = s;
			p = p->next;
		}
	}
	Delete_list();
	bool isDelete = false;	//判断值x是否已删去,x在初创链表时创建，应该删除

	while (head_temp) {
		if ((!isDelete) && (head_temp->data == x)) {	//如果还未删去，碰到x时不赋值给链表
			ListNode* d = head_temp;
			head_temp = head_temp->next;
			isDelete = true;
			delete d;
		}
		else {
			ListNode* d = head_temp;
			Insert(0, head_temp->data);	//分类好的链头依次插入表头，顺序为反
			head_temp = head_temp->next;
			delete d;
		}
	}
	reverse();	//顺序颠倒为正
}
#include "list_rd_.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

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

//num取值为 1—max+1
void List::Insert(int num, int x)
{
	int i = 1;
	ListNode* p = head;
	while (p && i < num - 1) {
		p = p->next;
		i++;
	}
	if (!p && num == 1) {
		head = new ListNode(x);
	}
	else if (!p || num < 1) {
		cout << "位置不合法" << endl;
	}
	else {
		if (num == 1) {
			ListNode* n = new ListNode(x, head);
			head = n;
		}
		else {
			p->next = new ListNode(x, p->next);
		}
	}
}

void List::Delete(int num)
{
	if (!head) {
		cout << "此链表为空" << endl;
	}
	else {
		ListNode* p = head;
		int pos = 1;	// p 指针位置
		while (p && pos < num - 1) {		//循环结束 p 指向要删除结点的前驱（num 在正常范围下）
			p = p->next;
			pos++;
		}
		if (!p || num < 1) {	
			cout << "位置不合法" << endl;
		}
		else if (num == 1) {		//删除头结点
			head = head->next;
			delete p;
		}
		else if (!p->next) {		//当不为空指针时，刚好为超出一位
			cout << "位置不合法" << endl;
		}
		else {
			ListNode* d = p->next;
			p->next = d->next;
			delete d;
		}
	}
}

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
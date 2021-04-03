#include "list_rd_.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

List::~List()
{
	int num = 0;//�������
	if (head) {
		while (head) {
			ListNode* d = head;
			head = head->next;
			delete d;
			cout << "ɾ����" << ++num << "�����" << "	";
		}
		cout << endl;
	}
}

//numȡֵΪ 1��max+1
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
		cout << "λ�ò��Ϸ�" << endl;
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
		cout << "������Ϊ��" << endl;
	}
	else {
		ListNode* p = head;
		int pos = 1;	// p ָ��λ��
		while (p && pos < num - 1) {		//ѭ������ p ָ��Ҫɾ������ǰ����num ��������Χ�£�
			p = p->next;
			pos++;
		}
		if (!p || num < 1) {	
			cout << "λ�ò��Ϸ�" << endl;
		}
		else if (num == 1) {		//ɾ��ͷ���
			head = head->next;
			delete p;
		}
		else if (!p->next) {		//����Ϊ��ָ��ʱ���պ�Ϊ����һλ
			cout << "λ�ò��Ϸ�" << endl;
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
		cout << "������Ϊ��" << endl;
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
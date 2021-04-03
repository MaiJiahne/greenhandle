#include "list_st.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


//������������
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

//��������		�� x Ϊ��ʼֵ����һ����������
void List::createList(int x)
{
	head = new ListNode;
	head->data = x;
	head->next = nullptr;
}

//������������
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

//����һ�������Ƿ��������У����� -1 ��ʾ����������,���ش��� 0 ������ʾ��һ��ֵΪ x ����λ��
int List::find(int x)
{
	if (!head) {
		return -1;
	}
	else {
		ListNode* p = head;
		int pos = 1;	// x ��λ��
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

//����������		���� num λ��֮��	���� 0 λ�ñ�ʾ����ͷ���֮ǰ  ������ʱ���� 1 ֮���ǲ��Ϸ���
void List::Insert(int num, int x)	
{
	int pos = 1;	// p ָ��λ��
	ListNode* p = head;
	while (p && pos < num) {
		p = p->next;
		pos++;
	}
	if (!head && num == 0) {	//������
		head = new ListNode;
		head->data = x;
		head->next = nullptr;
	}
	else if (!p || num < 0) {
		cout << "λ�ò��Ϸ�" << endl;
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


//����ɾ������,ɾ������λ������
void List::Delete_pos(int num)	//ɾ���� num �Ľ��
{
	if (!head) {
		cout << "������Ϊ��" << endl;
		//exit(0);
	}
	else {
		ListNode* p = head;
		int pos = 1;	// p ָ��λ��
		while (p && pos < num - 1) {		//ѭ������ p ָ��Ҫɾ������ǰ����num ��������Χ�£�
			p = p->next;
			pos++;
		}
		if (p == nullptr || (num <= 0)) {
			cout << "λ�ò��Ϸ�" << endl;
			exit(0);
		}
		if (num == 1) {		//ɾ��ͷ���
			head = head->next;
			delete p;
		}
		else if (p->next == nullptr) {		//����Ϊ��ָ��ʱ���պ�Ϊ����һλ
			cout << "λ�ò��Ϸ�" << endl;
			exit(0);
		}
		else {
			ListNode* d = p->next;
			p->next = d->next;
			delete d;
		}
	}
}

//����ɾ������,ɾ����һ����������ֵ��ͬ����
void List::Delete_value(int x)
{
	if (!head) {
		cout << "������Ϊ��" << endl;
	}
	else if (head->data == x) {
		ListNode* p = head;
		head = head->next;
		delete p;
	}
	else {
		//���ÿ���ָ��
		bool isExist = false;	//�Ƿ����ֵ��ȵ�ֵ
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
			cout << "������û��" << x << "��ֵ������" << endl;
		}
	}
	//�������Ϊ�գ������������
	if (head)
	{
		showList();
	}
}

//ɾ����������
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
		cout << "�����ѿ�" << endl;
	}
}

//����������������,�ֱ�����ͷ
void List::AddThreeRandomNum()
{
	srand(time(0));
	for (int i = 0; i < 3; i++) {
		int RandomNum = rand() % 900 + 100;
		Insert(0, RandomNum);
	}
}

//������ת
void List::reverse()
{
	if (!head) {
		cout << "������Ϊ��,���ܽ��з�ת����" << endl;
	}
	else if(!head->next){
		cout << "����ֻ��һ����㣬���ý��з�ת����" << endl;
	}
	else {
		//����һ�������洢�������ݣ��ڷ������������
		ListNode* p = head;
		vector<int> ivec;
		while (p) {
			ivec.push_back(p->data);
			p = p->next;
		}
		Delete_list();
		//����һ�������Ȳ����ͷ�����ճ���ĩ������
		for (auto& i : ivec) {
			Insert(0, i);
		}
		showList();
	}
}

/*
*�������������10��3λ����(100~999)������Щ�������ڵ������У�
*Ȼ�����һ���������Ը�ֵΪ��׼�ѵ�����ָ�Ϊ�����֣�����С
*�ڸ�ֵ�Ľ�����ڴ��ڻ���ڸ�ֵ�Ľ��֮ǰ��
*/
void List::sort_value(int x)
{
	AddThreeRandomNum();
	ListNode* head_temp = new ListNode;		//��ʱ����,�����������ʱ���
	ListNode* s = nullptr;	//�����������
	ListNode* p = head;	
	head_temp->data = x;
	head_temp->next = nullptr;
	ListNode* division = head_temp;	//ֵΪx����Ϊ�ָ���
	while (p) {
		if (p->data < x) {	//С�ڲ�������ͷ
			s = new ListNode;
			s->data = p->data;
			s->next = head_temp;
			head_temp = s;
			p = p->next;
		}
		else {	//���ڵ��ڲ���ָ���֮��
			s = new ListNode;
			s->data = p->data;
			s->next = division->next;
			division->next = s;
			p = p->next;
		}
	}
	Delete_list();
	bool isDelete = false;	//�ж�ֵx�Ƿ���ɾȥ,x�ڳ�������ʱ������Ӧ��ɾ��

	while (head_temp) {
		if ((!isDelete) && (head_temp->data == x)) {	//�����δɾȥ������xʱ����ֵ������
			ListNode* d = head_temp;
			head_temp = head_temp->next;
			isDelete = true;
			delete d;
		}
		else {
			ListNode* d = head_temp;
			Insert(0, head_temp->data);	//����õ���ͷ���β����ͷ��˳��Ϊ��
			head_temp = head_temp->next;
			delete d;
		}
	}
	reverse();	//˳��ߵ�Ϊ��
}
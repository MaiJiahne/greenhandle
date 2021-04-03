#include <iostream>

using std::cout;
using std::cin;
using std::endl;

struct Code
{
	int data;
	Code* next;
};
class ListNode {
private:
	Code* head;
	Code* rear;
public:
	ListNode() : head(nullptr), rear(nullptr) {}
	ListNode(Code* p) : head(p), rear(p) {}
	void end_insert(int);
	void end_deList();
	void show();
};

void ListNode::end_insert(int data) {
	if (!head) {
		head = new Code;
		head->data = data;
		head->next = nullptr;
		rear = head;
	}
	else {
		Code* create = new Code;
		create->data = data;
		create->next = nullptr;
		rear->next = create;
		rear = create;
	}
}

void ListNode::end_deList() {
	if (!head)
	{
		cout << "链表为空" << endl;
		return;
	}
	else {
		if (head->next) {	//只有一个结点
			Code* temp = head;
			while (temp->next != rear) {
				temp = temp->next;
			}
			rear = temp;
			temp = temp->next;
			rear->next = nullptr;
			delete temp;
		}
		else {
			Code* temp = head;
			head = nullptr;
			rear = nullptr;
			delete temp;
		}
	}

}

void ListNode::show() {
	if (!head) {
		cout << "此链表为空" << endl;
		return;
	}
	else {
		Code* get = head;
		while (get) {
			cout << get->data << "  ";
			get = get->next;
		}
	}

}

int main()
{
	ListNode lst1;
	//ListNode lst2();被认为是函数了
	lst1.show();
	lst1.end_deList();
	lst1.end_insert(4);
	lst1.end_insert(6);
	lst1.end_insert(1);
	lst1.end_insert(2);
	lst1.show();
	cout << endl;
	for (int i = 0; i < 6; i++) {
		lst1.end_deList();
	}
	lst1.show();
}


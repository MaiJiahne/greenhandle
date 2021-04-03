#pragma once

class ListNode {

	
public:
	int data;
	ListNode* next;
	ListNode() = default;
	ListNode(int x):data(x), next(nullptr){}
	ListNode(int x, ListNode* next_) :data(x), next(next_) {}
};

class List {
	ListNode* head;
public:
	List():head(nullptr){}
	~List();
	void Insert(int, int);
	void Delete(int);
	void showList();
};

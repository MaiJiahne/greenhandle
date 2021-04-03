#pragma once

struct stackNode {
	int data;
	stackNode* next;
};

class stack {

private:
	stackNode* top;
public:
	stack() :top(nullptr) {}
	~stack();
	bool empty();
	bool Top(int &);
	void Push(int);
	bool Pop();
	void show();
	void addThreeRandowNum();
	void showStack();
};

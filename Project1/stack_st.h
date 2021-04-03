#pragma once

struct stackNode {
	int data;
	stackNode* next;
};

class stack {

private:
	stackNode* top;
public:
	stack():top(nullptr){}
	~stack();
	int Top();
	void Push(int);
	void Pop();
	void show();
	void addThreeRandowNum();
	void showStack();
};

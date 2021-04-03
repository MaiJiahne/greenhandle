struct QueueNode{
	int data;
	QueueNode* next;
};

class Queue
{
private:
	QueueNode* front;
	QueueNode* rear;
public:
	Queue():front(nullptr),rear(nullptr){}
	~Queue();
	bool empty();
	void Enque(int );
	bool Deque();
	bool getHead(int&);
	void showQueue();
	void show();
	void delete_que();
	void addThreeRandNum();
	void reverse();
};
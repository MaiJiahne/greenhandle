#include "queue.h"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
	Queue que;
	//入队操作
	que.Enque(1);
	que.Enque(2);
	que.Enque(3);
	que.Enque(4);
	que.showQueue();
	cout << "---------------------------------------------------------" << endl;

	//出队操作
	que.showQueue();
	que.Deque();
	cout << "出队后，";
	que.showQueue();
	cout << "---------------------------------------------------------" << endl;

	//返回队头元素
	que.showQueue();
	int num = 0;
	que.getHead(num);
	cout << " 队头元素为" << num << endl;
	cout << "---------------------------------------------------------" << endl;

	//用随机函数生成10个3位整数(100~999)，
	//把这些整数应用入队操作存于队列中
	que.showQueue();
	que.addThreeRandNum();
	cout << "加入三个随机数后，";
	que.showQueue();
	cout << "---------------------------------------------------------" << endl;

	//把队列的内容翻转，应用出队操作输出队列的内容
	que.showQueue();
	que.reverse();
	cout << "队列翻转后，";
	que.showQueue();
	cout << "---------------------------------------------------------" << endl;

	//应用遍历操作输出队列的内容
	cout << "应用遍历操作输出队列" << endl;
	vector<int> ivec;
	int temp;
	while (!que.empty()) {
		que.getHead(temp);
		cout << temp << " ";
		ivec.push_back(temp);
		que.Deque();
	}
	cout << endl;
	for (auto& i : ivec) {
		que.Enque(i);
	}
	cout << "---------------------------------------------------------" << endl;

}
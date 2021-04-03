#include "stack_rd.h"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
	stack sta;
	int temp = 0;

	//入栈
	sta.Push(4);
	sta.Push(3);
	sta.Push(2);
	sta.Push(1);
	sta.show();
	cout << "-----------------------------------------------------------" << endl;

	//出栈
	sta.show();
	sta.Pop();
	cout << "出栈后，";
	sta.show();
	cout << "-----------------------------------------------------------" << endl;

	//返回栈顶数据
	sta.show();
	sta.Top(temp);
	cout << "栈顶数据为：";
	cout << temp << endl;
	cout << "-----------------------------------------------------------" << endl;
	
	/*
	 *用随机函数生成10个3位整数(100~999)，把这些整数应
	 *用入栈操作存于堆栈中，在入栈接口处设置断点①，按
	 *“F5”启动调试，按“F10”逐句执行，直到数据全部入
	 *栈。程序暂停时观察栈顶数据和栈顶位置；
	*/
	sta.show();
	sta.addThreeRandowNum();
	cout << "三个随机数入栈后";
	sta.show();
	cout << "-----------------------------------------------------------" << endl;

	/*
	 *应用出栈操作输出堆栈的内容，在出栈接口处设置断点②，
	 *按“F5”启动调试，按“F10”逐句执行，直到所有数据完
	 *全出栈，程序暂停时观察栈顶数据和栈顶位置的变化。
	*/
	cout << "应用出栈操作输出堆栈的内容" << endl;
	vector<int> ivec;
	int top_;
	while (sta.empty()) {
		sta.Top(top_);
		cout << top_ << "	";	//从栈顶输出
		ivec.push_back(top_);	//每个元素存入向量中，顺序为反
		sta.Pop();
	}
	cout << endl;
	for (auto beg = ivec.crbegin(); beg != ivec.crend(); ++beg) {	//栈此时为空，在用存在向量的元素倒序重新入栈
		sta.Push(*beg);
	}
	sta.show();

	cout << "-----------------------------------------------------------" << endl;
}
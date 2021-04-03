#include "stack_st.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	stack sta;
	cout << sta.Top() << endl;
	sta.Pop();
	sta.Push(4);
	sta.Push(3);
	sta.Push(2);
	sta.Push(1);
	cout << sta.Top() << endl;
	sta.Pop();

	sta.showStack();

	sta.Push(5);
	sta.show();

	sta.addThreeRandowNum();
	sta.show();



}
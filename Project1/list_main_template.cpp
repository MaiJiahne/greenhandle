#include "list_rd_.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	List lst;
	lst.Delete(2);
	lst.Delete(1);
	lst.Insert(4, 4);
	lst.Insert(1, 3);
	lst.Insert(1, 4);
	lst.Insert(1, 1);
	lst.Insert(1, 2);
	lst.showList();
	lst.Delete(2);
	lst.showList();
	
}
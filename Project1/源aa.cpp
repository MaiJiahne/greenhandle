#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
	/*vector<int> ivec;
	istream_iterator<int> in(cin), eof;
	ostream_iterator<int> out(cout, " "),out1(cout," ");
	copy(in, eof, back_inserter(ivec));
	for (auto i : ivec)
	{
		cout << i << " ";
	}
	cout << endl;
	copy(ivec.begin(), ivec.end(), out);
	cout << endl;
	out1 = 3;*/
	vector<int> i(10, 5);
	int a = 0, b = 3;
	for_each(i.begin(), i.end(), [a,b](int t)->void
		{   });

}
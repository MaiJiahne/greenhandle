#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

int main()
{
	vector<int> ivec(10, 0);
	for_each(ivec.begin(), ivec.end(), [](int i) {cout << i << " "; });
	[&] {
		for (auto& i : ivec) {
			cout << i << " ";
		}
	};
}



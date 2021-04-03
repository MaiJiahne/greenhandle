#include <iostream>
#include <vector>
using namespace std;
vector<int> twoSum(vector<int>& nums, int target)
{
	int i, j;
	for (i = 0; i < nums.size() - 1; ++i)
	{
		for (j = i + 1; j < nums.size(); ++j)
		{
			if ((nums[i] + nums[j]) == target)
				return { i,j };
		}
	}
	return { i,j };
}
int main()
{
	vector<int> ivec{ 2,7,11,15 };
	vector<int> temp = twoSum(ivec, 9);
	for (auto t : temp)
	{
		cout << t << " ";
	}
}
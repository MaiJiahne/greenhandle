#include <iostream>
#include <string>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stack;

//判段括号匹配是否合法
bool isLegal(string str)
{
	stack<char> chSta;
	for (auto ch : str) {
		if (ch == '{' || ch == '[' || ch == '(') {
			chSta.push(ch);
		}
		else if (ch == '}' || ch == ']' || ch == ')') {
			if (chSta.empty()) {
				return false;
			}
			else if (ch == '}' && chSta.top() == '{') {
				chSta.pop();
			}
			else if (ch == ']' && chSta.top() == '[') {
				chSta.pop();
			}
			else if (ch == ')' && chSta.top() == '(') {
				chSta.pop();
			}
		}
		else {
			cout << "输入不合法" << endl;
			return false;
		}
	}
	if (chSta.empty()) {
		return true;
	}
	else    return false;

}

int main()
{
	string brackets;
	for (int i = 0; i < 5; i++)
	{
		cout << "请输入需要验证的括号" << endl;
		getline(cin, brackets);
		if (isLegal(brackets)) {
			cout << "匹配成功" << endl;
		}
		else {
			cout << "匹配失败" << endl;
		}
	}

}
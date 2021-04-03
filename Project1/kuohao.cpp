#include <iostream>
#include <string>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stack;

//�ж�����ƥ���Ƿ�Ϸ�
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
			cout << "���벻�Ϸ�" << endl;
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
		cout << "��������Ҫ��֤������" << endl;
		getline(cin, brackets);
		if (isLegal(brackets)) {
			cout << "ƥ��ɹ�" << endl;
		}
		else {
			cout << "ƥ��ʧ��" << endl;
		}
	}

}
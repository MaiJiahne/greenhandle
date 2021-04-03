#include <iostream>
using namespace std;

void invert(char A[])
{
    char ch;
    static int i = 0;//利用静态变量存储数组下标
    cin >> ch;
    if (ch != '#')
    {
        invert(A);
        A[i++] = ch;//先存的放到后边
    }
    A[i] = '\0';
}

int main()
{
    char A[6];
    cout << "请输入一个字符串（以’#‘为结束标志，不包括‘#’）" << endl;
    invert(A);
    cout << "逆置后为：" << A;//char型数组可以利用数组名直接输出，int型则会输出其首地址
    return 0;
}

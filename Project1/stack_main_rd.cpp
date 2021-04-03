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

	//��ջ
	sta.Push(4);
	sta.Push(3);
	sta.Push(2);
	sta.Push(1);
	sta.show();
	cout << "-----------------------------------------------------------" << endl;

	//��ջ
	sta.show();
	sta.Pop();
	cout << "��ջ��";
	sta.show();
	cout << "-----------------------------------------------------------" << endl;

	//����ջ������
	sta.show();
	sta.Top(temp);
	cout << "ջ������Ϊ��";
	cout << temp << endl;
	cout << "-----------------------------------------------------------" << endl;
	
	/*
	 *�������������10��3λ����(100~999)������Щ����Ӧ
	 *����ջ�������ڶ�ջ�У�����ջ�ӿڴ����öϵ�٣���
	 *��F5���������ԣ�����F10�����ִ�У�ֱ������ȫ����
	 *ջ��������ͣʱ�۲�ջ�����ݺ�ջ��λ�ã�
	*/
	sta.show();
	sta.addThreeRandowNum();
	cout << "�����������ջ��";
	sta.show();
	cout << "-----------------------------------------------------------" << endl;

	/*
	 *Ӧ�ó�ջ���������ջ�����ݣ��ڳ�ջ�ӿڴ����öϵ�ڣ�
	 *����F5���������ԣ�����F10�����ִ�У�ֱ������������
	 *ȫ��ջ��������ͣʱ�۲�ջ�����ݺ�ջ��λ�õı仯��
	*/
	cout << "Ӧ�ó�ջ���������ջ������" << endl;
	vector<int> ivec;
	int top_;
	while (sta.empty()) {
		sta.Top(top_);
		cout << top_ << "	";	//��ջ�����
		ivec.push_back(top_);	//ÿ��Ԫ�ش��������У�˳��Ϊ��
		sta.Pop();
	}
	cout << endl;
	for (auto beg = ivec.crbegin(); beg != ivec.crend(); ++beg) {	//ջ��ʱΪ�գ����ô���������Ԫ�ص���������ջ
		sta.Push(*beg);
	}
	sta.show();

	cout << "-----------------------------------------------------------" << endl;
}
#include "queue.h"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
	Queue que;
	//��Ӳ���
	que.Enque(1);
	que.Enque(2);
	que.Enque(3);
	que.Enque(4);
	que.showQueue();
	cout << "---------------------------------------------------------" << endl;

	//���Ӳ���
	que.showQueue();
	que.Deque();
	cout << "���Ӻ�";
	que.showQueue();
	cout << "---------------------------------------------------------" << endl;

	//���ض�ͷԪ��
	que.showQueue();
	int num = 0;
	que.getHead(num);
	cout << " ��ͷԪ��Ϊ" << num << endl;
	cout << "---------------------------------------------------------" << endl;

	//�������������10��3λ����(100~999)��
	//����Щ����Ӧ����Ӳ������ڶ�����
	que.showQueue();
	que.addThreeRandNum();
	cout << "���������������";
	que.showQueue();
	cout << "---------------------------------------------------------" << endl;

	//�Ѷ��е����ݷ�ת��Ӧ�ó��Ӳ���������е�����
	que.showQueue();
	que.reverse();
	cout << "���з�ת��";
	que.showQueue();
	cout << "---------------------------------------------------------" << endl;

	//Ӧ�ñ�������������е�����
	cout << "Ӧ�ñ��������������" << endl;
	vector<int> ivec;
	int temp;
	while (!que.empty()) {
		que.getHead(temp);
		cout << temp << " ";
		ivec.push_back(temp);
		que.Deque();
	}
	cout << endl;
	for (auto& i : ivec) {
		que.Enque(i);
	}
	cout << "---------------------------------------------------------" << endl;

}
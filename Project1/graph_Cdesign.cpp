#include "graph_Cdesign.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::setiosflags;
using std::setw;
using std::ios;
using std::to_string;
using std::queue;

//����ͼ
Graph::Graph()
{
	vexnum = rand() % 20 + 10;//�������11~20����ׯ
	arcnum = 0;//�ȳ�ʼ��Ϊ��
	Dhp = nullptr;
	village = new Village[vexMax];
	for (int i = 0; i < vexnum; i++)
	{
		village[i] = { "��ׯ" + to_string(i),i };//�������,��ׯ����
	}
	//������ά����
	Arcs = new Arc * [vexMax];
	for (int st = 0; st < vexMax; st++) {
		Arcs[st] = new Arc[vexMax];
	}

	srand(int(time(0)));
	//��ʼ���ڽӾ���
	for (int i = 0; i < vexMax; i++) {
		for (int j = 0; j < vexMax; j++) {
			if (i == j) {
				Arcs[i][j] = 0;	//�Լ����Լ�·��Ϊ0
			}
			else
			{
				Arcs[i][j] = wMax;
			}

		}
	}//for(i)
	for (int i = 0; i < vexnum; i++) {	//�ڽ��Ͼ���
		for (int j = i; j < vexnum; j++) {
			if (i == j)	continue;
			else
			{
				int temp = rand() & 10 + 1;//�������1~10������С�ڵ���2�������㲻����,��2�ɸ���
				if (temp > 2) {
					Arcs[i][j] = rand() % 100 + 1;	//�������1~100��·��
					Arcs[j][i] = rand() % 100 + 1;
					arcnum += 2;//������������
				}
			}
		}//for (int j = i)
	}//for (int i)

}
//����ͼ
Graph::~Graph()
{
	if (village) {
		delete[]village;
		village = nullptr;
	}
	if (Dhp) {
		delete[]Dhp;
		Dhp = nullptr;
	}

	for (int st = 0; st < vexMax; st++) {
		if (Arcs[st]) {
			delete[]Arcs[st];
			Arcs[st] = nullptr;
		}

	}
	if (Arcs) {
		delete[]Arcs;
		Arcs = nullptr;
	}

}
//���ͼ����Ϣ
void Graph::display()
{
	cout << "ͼ�ı���Ϊ��" << vexnum << "ͼ�ĵ���Ϊ��" << arcnum << endl;
	/*for (int i = 0; i < vexnum; i++) {
		cout << "��ׯ��ţ�" << setw(3) << setiosflags(ios::left) << village[i].pos
			<< "   ��ׯ���֣�" << setw(3) << setiosflags(ios::left) << village[i].name << endl;
	}*/

	cout << "�ڽӾ���Ϊ��" << endl;
	for (int i = 0; i < vexnum; i++) {
		for (int j = 0; j < vexnum; j++) {
			if (Arcs[i][j] == wMax) {	//�����·�������
				cout << setw(3) << setiosflags(ios::left) << "��" << " ";
			}
			else
			{
				cout << setw(3) << setiosflags(ios::left) << Arcs[i][j] << " ";
			}

		}
		cout << endl;
	}
	cout << endl;
}
//��ӵ�
void Graph::addVex() {
	vexnum++;
	village[vexnum - 1] = { "��ׯ" + to_string(vexnum - 1),vexnum - 1 };
	for (int st = 0; st < vexnum; st++) {
		if (st != vexnum - 1) {	//���Լ�·��Ϊ0
			int temp = rand() & 10 + 1;//�������1~10������С�ڵ���2�������㲻����,��2�ɸ���
			if (temp > 2) {
				Arcs[vexnum - 1][st] = rand() % 100 + 1;	//�������1~100��·��
				Arcs[st][vexnum - 1] = rand() % 100 + 1;
				arcnum += 2;//������������
			}
		}

	}
}
//ɾ����
bool Graph::delVex(int n) {
	if (n < 0 || n >= vexnum) {
		cout << "��������ȷ�ĵ�\n";
		return false;
	}
	else
	{
		int sub_arcnum = 0;//��ȥ�ߵ�����
		for (int st = 0; st < vexnum; st++) {//ͳ��Ҫɾ���ı���
			if (Arcs[n][st] != wMax && Arcs[n][st] != 0) {
				sub_arcnum += 2;
			}
		}
		//Ҫɾ���ĵ㼰��ر������ĵ㽻����Ȼ�������1�������ƶ�
		Village temp = village[n];
		village[n] = village[vexnum - 1];
		village[vexnum - 1] = temp;
		for (int st = 0; st < vexnum; st++) {
			Arc temp = Arcs[n][st];
			Arcs[n][st] = Arcs[vexnum - 1][st];
			Arcs[vexnum - 1][st] = Arcs[n][st];

			temp = Arcs[st][n];
			Arcs[st][n] = Arcs[st][vexnum - 1];
			Arcs[st][vexnum - 1] = temp;
		}
		arcnum -= sub_arcnum;//��ȥ����
		vexnum--;//��ȥ����
		return true;
	}
}
//�ҿ�˹����(Dijkstra)�㷨�����·��
void Graph::shortestPath_DIJ(int n)
{
	if (n < 0 || n >= vexnum) {
		cout << "n�ǲ���ȷ����" << endl;
		return;
	}
	/*-----------------------------�ȳ�ʼ����������---------------------------*/
	Dhp = new Dhelp[vexMax];
	for (int i = 0; i < vexnum; i++) {
		if (Arcs[n][i] != wMax)	//��� n �� i ֮���л�
			Dhp[i] = { false,n,Arcs[n][i] };
		else		//��� n �� i ֮���޻�����ǰ����ʼ��Ϊ -1
		{
			Dhp[i] = { false,-1,Arcs[n][i] };
		}
	}
	Dhp[n] = { true,-1,0, };	//n��n֮��Ȩֵ��Ϊ��

	for (int i = 0; i < vexnum - 1; i++) {	//�������n��ÿ��������·��
		int min = wMax;	//�����Сֵ
		int v = n;//�����Сֵ�ĵ�
		for (int j = 0; j < vexnum; j++) {
			if (!Dhp[j].S && Dhp[j].cost < min) {	//�����δ������·����ȨֵС����Сֵ
				min = Dhp[j].cost;
				v = j;
			}

		}//for(j)

		Dhp[v].S = true;	//��������·��
		for (int k = 0; k < vexnum; k++) {	//����һ���µ㣬�������·��
			//������¼����Ϊ��ת�㣬Ȩֵ��С�����
			if ((!Dhp[k].S) && (Dhp[k].cost > Dhp[v].cost + Arcs[v][k])) {
				Dhp[k] = { false,v,Dhp[v].cost + Arcs[v][k] };
			}
		}//for(k)



	}//for(i)



}

//���ÿ�����·��
void Graph::displayShortestPath()
{
	int v = -1;//���v��ÿ��������·��
	for (int i = 0; i < vexnum; i++) {	//�ҳ�v��
		if (Dhp[i].path == -1) {
			v = i;
			break;
		}
	}

	for (int i = 0; i < vexnum; i++) {
		if (i != v) {
			cout << "�Ӵ�ׯ" << setw(3) << setiosflags(ios::left) << v << "����ׯ"
				<< setw(3) << setiosflags(ios::left) << i << "���·������Ϊ��"
				<< setw(3) << setiosflags(ios::left) << Dhp[i].cost
				<< "   �Ӵ�ׯ" << setw(3) << setiosflags(ios::left) << i << "����ׯ"
				<< setw(3) << setiosflags(ios::left) << v << "��·��Ϊ";
			queue<int> ique;//����һ�����У���·������������Ϊ��ׯi����ҽԺ��·��
			for (int t = Dhp[i].path; t != -1; t = Dhp[t].path) {
				ique.push(t);
			}
			cout << i;
			while (!ique.empty()) {
				cout << "-->" << ique.front();
				ique.pop();
			}
			cout << endl;
		}
	}
	//��շ������ʹ��
	if (Dhp) {
		delete[]Dhp;
		Dhp = nullptr;
	}

}

//��ҽԺ����ÿ����ׯ��������·����ѡ������ʵ�
void Graph::AllshortestPath()
{
	int* sumPathLength = new int[vexnum];//·�����Ⱥ�
	for (int i = 0; i < vexnum; i++) {	//��ʼ������
		sumPathLength[i] = 0;
	}
	cout << "--------------------------------------------------------------------------------------\n";
	for (int st = 0; st < vexnum; st++)
	{
		cout << "ҽԺѡ�ڴ�ׯ" << st << "�����\n\n";
		shortestPath_DIJ(st);
		for (int rd = 0; rd < vexnum; rd++) {
			sumPathLength[st] += Dhp[rd].cost;//���·��֮��
		}
		displayShortestPath();
		cout << "\nҽԺѡ�ڴ�ׯ" << st << "�������·����Ϊ��" << sumPathLength[st] << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}
	int hospitalPos = -1;//ҽԺѡ���λ��
	int minCost = wMax;//��Сֵ
	for (int st = 0; st < vexnum; st++) {//���·������С��
		if (sumPathLength[st] < minCost) {
			hospitalPos = st;
			minCost = sumPathLength[st];
		}
	}
	for (int st = 0; st < vexnum; st++) {
		cout << "ҽԺѡ���ڴ�ׯ" << setw(2) << setiosflags(ios::left) << st
			<< "ʱ·���ܳ���Ϊ��" << setw(3) << setiosflags(ios::left) << sumPathLength[st] << endl;
	}
	cout << "\nҽԺѡ���ڴ�ׯ" << hospitalPos << "����ʣ�����ܳ���Ϊ��" << minCost << endl;
	delete[]sumPathLength;//�����ڴ�
}

//������
void Main()
{
	bool start = true;
	int option = 0;
	Graph* G = nullptr;
	while (start) {//ѭ����startΪfalseʱ����
		cout << "---------------------------\n";
		cout << "������ѡ��\n";
		cout << "���� 1 ����һ��ͼ\n";
		cout << "���� 2 ���ͼ����Ϣ\n";
		cout << "���� 3 ���ҽԺѡַ���\n";
		cout << "���� 4 ��ӵ�\n";
		cout << "���� 5 ��������\n";
		cout << "---------------------------\n";
		cin >> option;
		if (option < 1 || option > 5) {
			cout << "��������ȷ����\n";
			continue;
		}
		switch (option)
		{
		case 1:
		{
			if (G) {
				delete G;
			}
			G = new Graph;
			cout << "�ɹ�����һ��ͼ\n";
			break;
		}
		case 2:
		{
			if (!G) {
				cout << "��ǰδ����ͼ\n";
			}
			else
			{
				G->display();
			}

			break;
		}
		case 3:
		{
			if (!G) {
				cout << "��ǰδ����ͼ\n";
			}
			else
			{
				G->AllshortestPath();
			}
			break;
		}
		case 4:
		{
			if (!G) {
				cout << "��ǰδ����ͼ\n";
			}
			else
			{
				G->addVex();
				cout << "�ɹ����һ����\n";
			}
			break;
		}
		//case 5:
		//{
		//	if (!G) {
		//		cout << "��ǰδ����ͼ\n";
		//	}
		//	else
		//	{
		//		int n = 0;
		//		cout << "������Ҫɾ���ĵ�\n";
		//		cin >> n;
		//		if (G->delVex(n)) {
		//			cout << "�ɹ�ɾ��һ����\n";
		//		}
		//	}
		//	break;
		//}
		case 5:
		{
			cout << "�������\n";
			start = false;
			break;
		}
		default:
			break;
		}
	}//while
	if (G) {
		delete G;
	}

}


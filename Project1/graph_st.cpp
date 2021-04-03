#include "graph.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::setiosflags;
using std::setw;
using std::ios;
using std::queue;
using std::vector;

Graph::Graph()
{
	graph.arcNum = graph.vexNum = 0;
	for (int i = 0; i < vexMax; i++) {
		graph.vex[i] = i;
		graph.visited[i] = false;//�Ƿ��ѷ���
		for (int j = 0; j < vexMax; j++) {
			graph.Arcs[i][j] = wMax;
		}
	}

}

//����ͼ
void Graph::createGraph()
{
	cout << "��������ͱ���" << endl;
	cin >> graph.vexNum >> graph.arcNum;

	int beg = 0, end = 0, weight = -1;	//�ߵ������յ�
	for (int i = 0; i < graph.arcNum; i++) {
		cout << "����ߵ������յ㲢����Ȩֵ" << endl;
		cin >> beg >> end >> weight;
		if ((beg < 0 || beg >= graph.vexNum) || (end < 0 || end >= graph.vexNum)) {	//������벻��ȷ����������
			cout << "��������ȷ����" << endl;
			i--;
			continue;
		}
		graph.Arcs[beg][end] = weight;
		graph.Arcs[end][beg] = weight;
	}
}

//����ڽӾ���
void Graph::display()
{
	cout << "�ڽӾ���Ϊ��" << endl;
	for (int i = 0; i < graph.vexNum; i++) {
		for (int j = 0; j < graph.vexNum; j++) {
			cout << setw(10) << setiosflags(ios::left) << graph.Arcs[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//������ȱ�����ͨͼ
void Graph::DFS(myGraph& graph, int n)	//��̬�������Ǹı��Ա��ֵ������
{
	if (!graph.visited[n]) {
		cout << graph.vex[n] << " ";
		graph.visited[n] = true;
		for (int i = 0; i < graph.vexNum; i++) {	//�����n�������ĵ�δ����������б���
			if (graph.Arcs[n][i] != wMax && !graph.visited[i]) {
				DFS(graph, i);
			}
		}
	}
}

void Graph::DFS(int n)
{

	DFS(graph, n);

}

//������ȱ�������ͨͼ
void Graph::DFSTraverse()
{
	for (int i = 0; i < graph.vexNum; i++) {
		DFS(graph, i);
	}


	for (int i = 0; i < vexMax; i++) {	//visited�ָ�Ϊfalse����������ظ����� DFS �� BFS
		graph.visited[i] = false;
	}

}

//������ȱ�����ͨͼ
void Graph::BFS(int n)
{
	queue<int> ique;
	ique.push(n);		//�����
	while (!ique.empty()) {
		int pos = ique.front();
		if (!graph.visited[pos]) {	//���δ�����������
			cout << graph.vex[pos] << " ";
			graph.visited[pos] = true;
		}
		ique.pop();
		for (int i = 0; i < graph.vexNum; i++) {

			if (graph.Arcs[pos][i] != wMax) {
				if (!graph.visited[i]) {
					cout << graph.vex[i] << " ";
					graph.visited[i] = true;
					ique.push(i);	//������δ���ʵ����
				}



			}//if 
		}//for

	}//while

}

//������ȱ�������ͨͼ
void Graph::BFSTraverse()
{
	for (int i = 0; i < graph.vexNum; i++) {
		BFS(i);
	}

	for (int i = 0; i < vexMax; i++) {	//visited�ָ�Ϊfalse����������ظ����� DFS �� BFS
		graph.visited[i] = false;
	}
}


infoH* closedge = new infoH[vexMax];//ʵ������ķ�㷨�ĸ����ṹ
//����ķ�㷨--��С������
void Graph::MiniSpanTree_Prim(int n)	//��n��ʼ
{
	if (n < 0 || n >= graph.vexNum) {
		cout << "n�ǲ���ȷ����" << endl;
		return;
	}
	for (int i = 0; i < graph.vexNum; i++) {	//��ʼ��closedge,ǰ����Ϊn��
		if (i != n) {
			closedge[i] = { n,graph.Arcs[n][i] };
		}
	}
	closedge[n] = { -1,0 };
	cout << "�����Ϊ��";
	int k = -1, u = -1;	//��¼����ߵ������յ�
	vector<int> ivec;	//��ŵ㣬���������˳��
	ivec.push_back(n);	//��n��ʼ��n�ȼ���
	for (int i = 0; i < graph.vexNum - 1; i++) {
		k = location_min(closedge);		//�ҵ�Ȩֵ��С�����������
		u = closedge[k].adjvex;
		ivec.push_back(k);	//���������
		cout << "<" << u << "," << k << ">" << " ";	//�������������ǰ��
		closedge[k].lowcost = 0;
		for (int j = 0; j < graph.vexNum; j++) {
			if (closedge[j].lowcost > graph.Arcs[k][j]) {	//������Ϣ�����δ����㵽�¼�����ȨֵС��ԭ������Ϊ��С��
				closedge[j] = { k ,graph.Arcs[k][j] };
			}
		}

	}
	cout << endl;
	cout << "�����˳��Ϊ��";
	cout << "{";
	for (auto i = ivec.cbegin(); i != ivec.cend(); ++i) {
		cout << *i;
		if (i + 1 != ivec.cend()) {
			cout << ",";
		}
	}
	cout << "}" << endl;

	//��closedge��λ����������ͼʹ��
	for (int i = 0; i < graph.vexNum; i++) {
		closedge[i] = { -1,wMax };
	}
}

//����ķ�㷨--����ΪȨֵ��С��
int Graph::location_min(infoH* closedge)
{
	int min = wMax;
	int pos = -1;
	for (int i = 0; i < graph.vexNum; i++) {
		if (closedge[i].lowcost != 0 && closedge[i].lowcost <= min) {
			pos = i;
			min = closedge[i].lowcost;
		}
	}
	return pos;
}

Digraph::Digraph() :Graph() {
	graph.arcNum = graph.vexNum = 0;
	for (int i = 0; i < vexMax; i++) {
		graph.vex[i] = i;
		graph.visited[i] = false;
		for (int j = 0; j < vexMax; j++) {
			graph.Arcs[i][j] = wMax;
		}
	}
}

/*-------------------------����ͼ------------------------------------------*/
//����ͼ���Լ��Ĵ�������
void Digraph::createGraph() {
	cout << "��������ͱ���" << endl;
	cin >> graph.vexNum >> graph.arcNum;

	int beg = 0, end = 0, weight = -1;	//�ߵ������յ�
	for (int i = 0; i < graph.arcNum; i++) {
		cout << "����ߵ������յ㲢����Ȩֵ" << endl;
		cin >> beg >> end >> weight;
		if ((beg < 0 || beg >= graph.vexNum) || (end < 0 || end >= graph.vexNum)) {	//������벻��ȷ����������
			cout << "��������ȷ����" << endl;
			i--;
			continue;
		}
		graph.Arcs[beg][end] = weight;
	}
}
//����ڽӾ���
void Digraph::display()
{
	cout << "�ڽӾ���Ϊ��" << endl;
	for (int i = 0; i < graph.vexNum; i++) {
		for (int j = 0; j < graph.vexNum; j++) {
			cout << setw(10) << setiosflags(ios::left) << graph.Arcs[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

Dhelp* Dhp = new Dhelp[vexMax];// �ҿ�˹����(Dijkstra)�㷨�����ṹ
//�ҿ�˹����(Dijkstra)�㷨�����·��
void Digraph::shortestPath_DIJ(int n)
{
	if (n < 0 || n >= graph.vexNum) {
		cout << "n�ǲ���ȷ����" << endl;
		return;
	}
	/*-----------------------------�ȳ�ʼ����������---------------------------*/
	for (int i = 0; i < graph.vexNum; i++) {
		if (graph.Arcs[n][i] != wMax)	//��� n �� i ֮���л�
			Dhp[i] = { false,n,graph.Arcs[n][i] };
		else		//��� n �� i ֮���޻�����ǰ����ʼ��Ϊ -1
		{
			Dhp[i] = { false,-1,graph.Arcs[n][i] };
		}
	}
	Dhp[n] = { true,-1,0, };	//n��n֮��Ȩֵ��Ϊ��

	for (int i = 0; i < graph.vexNum - 1; i++) {	//�������n��ÿ��������·��
		int min = wMax;	//�����Сֵ
		int v = n;//�����Сֵ�ĵ�
		for (int j = 0; j < graph.vexNum; j++) {
			if (!Dhp[j].S && Dhp[j].cost < min) {	//�����δ������·����ȨֵС����Сֵ
				min = Dhp[j].cost;
				v = j;
			}

		}//for(j)

		Dhp[v].S = true;	//��������·��
		for (int k = 0; k < graph.vexNum; k++) {	//����һ���µ㣬�������·��
			//������¼����Ϊ��ת�㣬Ȩֵ��С�����
			if ((!Dhp[k].S) && (Dhp[k].cost > Dhp[v].cost + graph.Arcs[v][k])) {
				Dhp[k] = { false,v,Dhp[v].cost + graph.Arcs[v][k] };
			}
		}//for(k)



	}//for(i)



}

//���ÿ�����·��
void Digraph::displayShortestPath()
{
	int v = -1;//���v��ÿ��������·��
	for (int i = 0; i < graph.vexNum; i++) {	//�ҳ�v��
		if (Dhp[i].path == -1) {
			v = i;
			break;
		}
	}

	for (int i = 0; i < graph.vexNum; i++) {
		if (i != v) {
			cout << "<" << v << "," << i << "> ���·��Ϊ��" << Dhp[i].cost << endl;
		}
	}
}

void Delete() {	//ɾ��������̬�ڴ�
	delete[]closedge;
	delete[]Dhp;
};

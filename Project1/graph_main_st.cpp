#include "graph.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	Graph G;
	G.createGraph();
	G.display();
	cout << "�ӽ�� 0 ��ʼ������ȱ���ͼ" << endl;
	G.BFS(0);
	cout << endl;
	cout << "�ӽ�� 0 ��ʼ������ȱ���ͼ" << endl;
	G.DFS(0);
	cout << endl;
	cout << "����ķ�㷨" << endl;
	G.MiniSpanTree_Prim(0);

	//Digraph DG;
	//DG.createGraph();
	//DG.display();
	//DG.shortestPath_DIJ(0);
	//cout << "��������㵽 0 �����·��" << endl;
	//DG.displayShortestPath();



	Delete();//ɾ��������̬�ڴ�
}
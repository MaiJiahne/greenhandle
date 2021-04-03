#pragma once

#define vexMax 50	//�������ֵ
#define wMax 32767	//����ֵ
typedef int Vex;	//��
typedef int Arc;	//��

struct myGraph
{
	Vex vex[vexMax];
	int vexNum, arcNum;	//�����ͱ���
	Arc Arcs[vexMax][vexMax];
	bool visited[vexMax];//�Ƿ��ѷ���
};

typedef int weight;// Ȩֵ
struct infoH	//ʵ������ķ�㷨�ĸ����ṹ
{
	int adjvex;
	weight lowcost;
};

class Graph {
private:
	myGraph graph;
	static void DFS(myGraph&, int);
public:
	Graph();
	~Graph() = default;
	void createGraph();
	void display();
	void DFS(int);
	void DFSTraverse();
	void BFS(int);
	void BFSTraverse();
	void MiniSpanTree_Prim(int);
	int location_min(infoH*);
};

struct Dhelp	//�ҿ�˹����(Dijkstra)�㷨�����ṹ
{
	bool S;	//���Ƿ���������·��
	int path;	//���·���ϵ�ֱ��ǰ����
	int cost;	//��ĳ������·��Ȩֵ
};

//����ͼ
class Digraph:public Graph
{
public:
	Digraph();
	~Digraph() = default;
	void createGraph();
	void display();
	void shortestPath_DIJ(int);
	void displayShortestPath();
private:
	myGraph graph;
};

void Delete();


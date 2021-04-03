#pragma once

#define vexMax 50	//点数最大值
#define wMax 32767	//极大值
typedef int Vex;	//点
typedef int Arc;	//边

struct myGraph
{
	Vex vex[vexMax];
	int vexNum, arcNum;	//点数和边数
	Arc Arcs[vexMax][vexMax];
	bool visited[vexMax];//是否已访问
};

typedef int weight;// 权值
struct infoH	//实现普利姆算法的辅助结构
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

struct Dhelp	//狄克斯特拉(Dijkstra)算法辅助结构
{
	bool S;	//点是否已算好最短路径
	int path;	//最短路径上的直接前驱点
	int cost;	//到某点的最短路径权值
};

//有向图
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


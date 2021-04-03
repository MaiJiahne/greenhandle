#pragma once
#include <string>

using std::string;

#define vexMax 50		//点最大值
#define	wMax	32767	//最大路径（权值）

struct Village
{
	string name;//村庄名字
	int pos = 0;//村庄序号
};

struct Dhelp	//狄克斯特拉(Dijkstra)算法辅助结构
{
	bool S;	//点是否已算好最短路径
	int path;	//最短路径上的直接前驱点
	int cost;	//到某点的最短路径权值
};

typedef int Arc;//边

class Graph
{
public:
	Graph();
	void display();//输出图信息
	void addVex();//添加点
	bool delVex(int);//删除点
	void shortestPath_DIJ(int);//用狄克斯特拉(Dijkstra)算法算最短路径
	void displayShortestPath();//输出最短路径
	void AllshortestPath();//每个点都算出最短路径
	~Graph();

private:
	int vexnum;//点数量
	int arcnum;//边数量
	Village* village;//村庄
	Arc** Arcs;//临近矩阵
	Dhelp* Dhp;// 狄克斯特拉(Dijkstra)算法辅助结构
};

//运行的主函数
void Main();


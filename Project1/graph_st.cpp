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
		graph.visited[i] = false;//是否已访问
		for (int j = 0; j < vexMax; j++) {
			graph.Arcs[i][j] = wMax;
		}
	}

}

//创建图
void Graph::createGraph()
{
	cout << "输入点数和边数" << endl;
	cin >> graph.vexNum >> graph.arcNum;

	int beg = 0, end = 0, weight = -1;	//边的起点和终点
	for (int i = 0; i < graph.arcNum; i++) {
		cout << "输入边的起点和终点并输入权值" << endl;
		cin >> beg >> end >> weight;
		if ((beg < 0 || beg >= graph.vexNum) || (end < 0 || end >= graph.vexNum)) {	//如果输入不正确，重新输入
			cout << "请输入正确数据" << endl;
			i--;
			continue;
		}
		graph.Arcs[beg][end] = weight;
		graph.Arcs[end][beg] = weight;
	}
}

//输出邻接矩阵
void Graph::display()
{
	cout << "邻接矩阵为：" << endl;
	for (int i = 0; i < graph.vexNum; i++) {
		for (int j = 0; j < graph.vexNum; j++) {
			cout << setw(10) << setiosflags(ios::left) << graph.Arcs[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//深度优先遍历连通图
void Graph::DFS(myGraph& graph, int n)	//静态函数不是改变成员的值用引用
{
	if (!graph.visited[n]) {
		cout << graph.vex[n] << " ";
		graph.visited[n] = true;
		for (int i = 0; i < graph.vexNum; i++) {	//如果与n点相连的点未遍历，则进行遍历
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

//深度优先遍历非连通图
void Graph::DFSTraverse()
{
	for (int i = 0; i < graph.vexNum; i++) {
		DFS(graph, i);
	}


	for (int i = 0; i < vexMax; i++) {	//visited恢复为false，后面可以重复调用 DFS 和 BFS
		graph.visited[i] = false;
	}

}

//广度优先遍历连通图
void Graph::BFS(int n)
{
	queue<int> ique;
	ique.push(n);		//先入队
	while (!ique.empty()) {
		int pos = ique.front();
		if (!graph.visited[pos]) {	//如果未遍历，则输出
			cout << graph.vex[pos] << " ";
			graph.visited[pos] = true;
		}
		ique.pop();
		for (int i = 0; i < graph.vexNum; i++) {

			if (graph.Arcs[pos][i] != wMax) {
				if (!graph.visited[i]) {
					cout << graph.vex[i] << " ";
					graph.visited[i] = true;
					ique.push(i);	//将连接未访问的入队
				}



			}//if 
		}//for

	}//while

}

//广度优先遍历非连通图
void Graph::BFSTraverse()
{
	for (int i = 0; i < graph.vexNum; i++) {
		BFS(i);
	}

	for (int i = 0; i < vexMax; i++) {	//visited恢复为false，后面可以重复调用 DFS 和 BFS
		graph.visited[i] = false;
	}
}


infoH* closedge = new infoH[vexMax];//实现普利姆算法的辅助结构
//普利姆算法--最小生成树
void Graph::MiniSpanTree_Prim(int n)	//从n开始
{
	if (n < 0 || n >= graph.vexNum) {
		cout << "n是不正确数据" << endl;
		return;
	}
	for (int i = 0; i < graph.vexNum; i++) {	//初始化closedge,前驱都为n，
		if (i != n) {
			closedge[i] = { n,graph.Arcs[n][i] };
		}
	}
	closedge[n] = { -1,0 };
	cout << "加入边为：";
	int k = -1, u = -1;	//记录加入边的起点和终点
	vector<int> ivec;	//存放点，输出点加入的顺序
	ivec.push_back(n);	//从n开始，n先加入
	for (int i = 0; i < graph.vexNum - 1; i++) {
		k = location_min(closedge);		//找到权值最小，加入点阵容
		u = closedge[k].adjvex;
		ivec.push_back(k);	//点加入阵容
		cout << "<" << u << "," << k << ">" << " ";	//输出加入点和它的前驱
		closedge[k].lowcost = 0;
		for (int j = 0; j < graph.vexNum; j++) {
			if (closedge[j].lowcost > graph.Arcs[k][j]) {	//更新信息，如果未加入点到新加入点的权值小于原来，则换为更小的
				closedge[j] = { k ,graph.Arcs[k][j] };
			}
		}

	}
	cout << endl;
	cout << "加入点顺序为：";
	cout << "{";
	for (auto i = ivec.cbegin(); i != ivec.cend(); ++i) {
		cout << *i;
		if (i + 1 != ivec.cend()) {
			cout << ",";
		}
	}
	cout << "}" << endl;

	//将closedge复位，方便后面的图使用
	for (int i = 0; i < graph.vexNum; i++) {
		closedge[i] = { -1,wMax };
	}
}

//普利姆算法--查找为权值最小的
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

/*-------------------------有向图------------------------------------------*/
//有向图有自己的创建方法
void Digraph::createGraph() {
	cout << "输入点数和边数" << endl;
	cin >> graph.vexNum >> graph.arcNum;

	int beg = 0, end = 0, weight = -1;	//边的起点和终点
	for (int i = 0; i < graph.arcNum; i++) {
		cout << "输入边的起点和终点并输入权值" << endl;
		cin >> beg >> end >> weight;
		if ((beg < 0 || beg >= graph.vexNum) || (end < 0 || end >= graph.vexNum)) {	//如果输入不正确，重新输入
			cout << "请输入正确数据" << endl;
			i--;
			continue;
		}
		graph.Arcs[beg][end] = weight;
	}
}
//输出邻接矩阵
void Digraph::display()
{
	cout << "邻接矩阵为：" << endl;
	for (int i = 0; i < graph.vexNum; i++) {
		for (int j = 0; j < graph.vexNum; j++) {
			cout << setw(10) << setiosflags(ios::left) << graph.Arcs[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

Dhelp* Dhp = new Dhelp[vexMax];// 狄克斯特拉(Dijkstra)算法辅助结构
//狄克斯特拉(Dijkstra)算法求最短路径
void Digraph::shortestPath_DIJ(int n)
{
	if (n < 0 || n >= graph.vexNum) {
		cout << "n是不正确数据" << endl;
		return;
	}
	/*-----------------------------先初始化辅助数组---------------------------*/
	for (int i = 0; i < graph.vexNum; i++) {
		if (graph.Arcs[n][i] != wMax)	//如果 n 和 i 之间有弧
			Dhp[i] = { false,n,graph.Arcs[n][i] };
		else		//如果 n 和 i 之间无弧，则前驱初始化为 -1
		{
			Dhp[i] = { false,-1,graph.Arcs[n][i] };
		}
	}
	Dhp[n] = { true,-1,0, };	//n到n之间权值置为零

	for (int i = 0; i < graph.vexNum - 1; i++) {	//依次算出n到每个点的最短路径
		int min = wMax;	//存放最小值
		int v = n;//存放最小值的点
		for (int j = 0; j < graph.vexNum; j++) {
			if (!Dhp[j].S && Dhp[j].cost < min) {	//如果点未算出最短路径且权值小于最小值
				min = Dhp[j].cost;
				v = j;
			}

		}//for(j)

		Dhp[v].S = true;	//已算出最短路径
		for (int k = 0; k < graph.vexNum; k++) {	//加入一个新点，更新最短路径
			//如果已新加入点为中转点，权值更小则更换
			if ((!Dhp[k].S) && (Dhp[k].cost > Dhp[v].cost + graph.Arcs[v][k])) {
				Dhp[k] = { false,v,Dhp[v].cost + graph.Arcs[v][k] };
			}
		}//for(k)



	}//for(i)



}

//输出每个最短路径
void Digraph::displayShortestPath()
{
	int v = -1;//输出v到每个点的最短路径
	for (int i = 0; i < graph.vexNum; i++) {	//找出v点
		if (Dhp[i].path == -1) {
			v = i;
			break;
		}
	}

	for (int i = 0; i < graph.vexNum; i++) {
		if (i != v) {
			cout << "<" << v << "," << i << "> 最短路径为：" << Dhp[i].cost << endl;
		}
	}
}

void Delete() {	//删除辅助动态内存
	delete[]closedge;
	delete[]Dhp;
};

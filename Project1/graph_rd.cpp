/*
* 有向图
* 链式结构
*/
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::setiosflags;
using std::setw;
using std::ios;
using std::queue;
using std::vector;
using std::sort;


#define vexmax 100 //图中点的最大数

typedef int vex;	//描述点的位置，如Vex[0]是第一个点
typedef int weight;	//边的权值
//边
struct ArcNode
{
	vex ivex;//起点
	vex jvex;//终点
	ArcNode* ilink;//同一起点的相邻的下一条边
	ArcNode* jlink;//同一种点的相邻的下一条边
	weight cost;//边的权值
};


typedef int vexType;	//点的信息
//点
struct VexNode
{
	vexType info;//点的信息
	ArcNode* firstarc;//指向此点的边
	ArcNode* firstout;//从此点出发的边
};
//图
struct Graph
{
	int vexnum;//点的数量
	int arcnum;//边的数量
	VexNode* Vex;//点
};

//创建图
void createGraph(Graph& G)
{
	G.Vex = new VexNode[vexmax];
	cout << "请输入创建图的点数和边数\n";
	cin >> G.vexnum >> G.arcnum;
	//初始化点集合
	for (int i = 0; i < vexmax; i++)
	{
		G.Vex[i].info = i;
		G.Vex[i].firstarc = nullptr;
		G.Vex[i].firstout = nullptr;
	}
	//创建边
	int f = -1, e = -1, cost = 0;//边的起点、终点和权值
	for (int i = 0; i < G.arcnum; i++)
	{
		cout << "请输入边的起点、终点和权值\n";
		cin >> f >> e >> cost;
		if (f < 0 || f >= G.vexnum || e < 0 || e >= G.vexnum) {//非法数据
			i--;
			continue;
		}
		ArcNode* arc = new ArcNode;	//动态创建边
		arc->ivex = f;
		arc->jvex = e;
		arc->cost = cost;
		arc->ilink = G.Vex[f].firstout;	//与同起点的边相链接
		G.Vex[f].firstout = arc;
		arc->jlink = G.Vex[f].firstarc;	//与同终点的边相链接
		G.Vex[f].firstarc = arc;
	}
}



//析构，回收动态内存
void Delete(Graph& G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode* arc = G.Vex[i].firstout;
		if (!arc)	continue;	//此点没边
		else {
			while (arc) {
				ArcNode* d = arc;
				arc = arc->ilink;
				cout << "删除<" << d->ivex << "," << d->jvex << ">边\n";
				delete d;
			}
		}
	}
	delete[]G.Vex;
}

//对联通图进行深度优先遍历
bool visited[vexmax] = { false };//是否访问过的标记
//从n点开始遍历
void DFS(const Graph& G, int n)
{
	if (!visited[n]) {
		cout << G.Vex[n].info << " ";
		visited[n] = true;
		ArcNode* p = G.Vex[n].firstout;
		while (p) {
			DFS(G, p->jvex);
			p = p->ilink;
		}
	}

}
//有向图的联通图如果一个点没有出度就停在这个点了
//对非联通图进行深度优先遍历
void DFSTraverse(const Graph& G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		DFS(G, i);
	}
}

//对联通图进行广度优先遍历
void BFS(const Graph& G, int n)
{
	queue<VexNode> vque;
	vque.push(G.Vex[n]);
	while (!vque.empty())
	{
		VexNode vext = vque.front();
		vque.pop();
		if (!visited[vext.info]) {	//还未访问
			cout << G.Vex[vext.info].info << " ";
			visited[vext.info] = true;
		}
		ArcNode* arct = vext.firstout;
		while (arct) {	//将相链接的入队
			vque.push(G.Vex[arct->jvex]);
			arct = arct->ilink;
		}
	}
}
//对非联通图进行广度优先遍历
void BFSTraverse(const Graph& G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		BFS(G, i);
	}
}
//Kruskal算法--最小生成树
//辅助结构
struct Help
{
	weight cost;//权值
	vex first;//起点
	vex end;//终点
};

void MiniSpanTree_Kruskal(const Graph& G)
{
	Help* H = new Help[G.arcnum];
	int arcRecord = 0;//记录已存储的边
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode* p = G.Vex[i].firstout;
		while (p) {	//将每条边的信息存放到Help中
			if (arcRecord < G.arcnum) {
				H[arcRecord].cost = p->cost;
				H[arcRecord].first = p->ivex;
				H[arcRecord].end = p->jvex;
				p = p->ilink;
				arcRecord++;
			}

		}

	}
	//快排，将边权值从小到大排
	sort(H, H + G.arcnum, [](const Help& a, const Help& b) {
		return a.cost < b.cost;
		});
	int* vexset = new int[G.vexnum];//记录点的阵容，防止成环
	for (int i = 0; i < G.vexnum; i++)
	{
		vexset[i] = i;
	}
	for (int i = 0; i < G.arcnum; i++)
	{
		if (vexset[H[i].first] != vexset[H[i].end])	//如果当前边的起点和终点不是同一阵容，不会成环
		{
			cout << "<" << H[i].first << "," << H[i].end << "> ";
			for (int j = 0; j < G.vexnum; j++)	//统一加入first阵容
			{
				if (vexset[j] == H[i].end) {
					vexset[j] = H[i].first;
				}
			}//for (int j = 0)
		}//if
	}//for (int i = 0)

	delete[]vexset;
	delete[]H;
}















int main()
{
	Graph G;
	createGraph(G);
	DFSTraverse(G);
	for (int i = 0; i < vexmax; i++)	visited[i] = false;	//置零方便重复使用
	cout << endl;
	BFSTraverse(G);
	for (int i = 0; i < vexmax; i++)	visited[i] = false;	//置零方便重复使用
	cout << endl;
	MiniSpanTree_Kruskal(G);
	cout << endl;
	Delete(G);

}
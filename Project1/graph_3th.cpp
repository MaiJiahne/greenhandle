/*
* 无向图
* 链式结构
* 多重邻接表，不会用邻接表
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
	bool mark;//标记
	vex ivex, jvex;//两个顶点
	ArcNode* ilink;//i顶点下一条边
	ArcNode* jlink;//j顶下一条边
	weight cost;//边的权值
};


typedef int vexType;	//点的信息
//点
struct VexNode
{
	vexType info;//点的信息
	ArcNode* firstarc;//此点的第一条边
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
	}
	//创建边
	int f = -1, e = -1, cost = 0;//边的起点、终点和权值
	for (int i = 0; i < G.arcnum; i++)
	{
		cout << "请输入边的起点、终点和权值\n";
		cin >> f >> e >> cost;
		if (f < 0 || f >= G.vexnum || e < 0 || e >= G.vexnum) {//非法数据
			i--;
			cout << "非法数据，请重新输入！\n";
			continue;
		}
		ArcNode* arc = new ArcNode;	//动态创建边
		arc->cost = cost;
		arc->ivex = f;
		arc->jvex = e;
		arc->ilink = G.Vex[f].firstarc;	//输入 <0,1> 和 <1,0>可以创两条边，但与多重邻接表不同，邻接表是输入一边创建了两个	
		G.Vex[f].firstarc = arc;		//多重邻接表则输入两个是条不同边
		arc->jlink = G.Vex[e].firstarc;
		G.Vex[e].firstarc = arc;
		arc->mark = false;
	}
}



//析构，回收动态内存
/*
* 利用好信息，比如都以ivex为删除，那么arc->ivex必为当前点 if（arc->ivex != i）
*/
void Delete(Graph& G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode* arc = G.Vex[i].firstarc;
		if (!arc)	continue;	//此点没边
		else {
			//只删除一条边，目的是删除以这个点为ivex的每条边，	需要找前驱才能删除
			while (arc)
			{
				ArcNode* parc = nullptr;//作为arc的前驱点
				while (arc) {	//删除以i为ivex的边
					if (arc->ivex != i) {
						parc = arc;
						arc = arc->jlink;
					}
					else
					{
						break;
					}
				}
				if (!arc) {	//点i都是以jvex存在
					break;//等会外层while注意下	这里出错了但arc为空一直重复
				}
				else      //找到要删除的边了
				{
					if (!parc) {	//要删除是firstarc
						G.Vex[i].firstarc = arc->ilink;
					}
					else {	//不是firstarc，让parc为前驱
						if (parc->ivex == i) {	//是ivex还是jvex
							parc->ilink = arc->ilink;
						}
						else  parc->jlink = arc->ilink;
					}
					ArcNode* del = arc;//用来删除边
					ArcNode* p = G.Vex[arc->jvex].firstarc;//一条边结点有指针指向，一个删除，另一个指向改变
					if (p->ivex == i) {	//如果第一条边就是要删除的
						G.Vex[arc->jvex].firstarc = p->jlink;//改变指向
					}
					else
					{
						ArcNode* q = p;				//p不一定，也可以p = p->ilink
						if (p->ivex == arc->jvex) {
							p = p->ilink;
						}
						else
						{
							p = p->jlink;
						}
						while (p) {
							if (p->ivex == i) {	//找到要删除的边
								if (q->ivex == arc->jvex) {	//没有必要的判断
									q->ilink = p->jlink;
								}
								else
								{
									q->jlink = p->jlink;
								}
								p = nullptr;
								break;
							}
							else        //不是接着往下找
							{
								if (p->ivex == arc->jvex) {//判断要改指向的点是ivex还是jvex
									q = p;
									p = p->ilink;
								}
								else
								{
									q = p;
									p = p->jlink;
								}
							}

						}//while(p)

					}//else	
					arc = arc->ilink;
					cout << "删除<" << G.Vex[i].info << "," << del->jvex << ">边\n";
					delete del;
				}//else [if (!arc)]

			}





		}//esle [if (!arc)]外层的
	}//for (int i)


	delete[]G.Vex;
}

////对联通图进行深度优先遍历
//bool visited[vexmax] = { false };//是否访问过的标记
////从n点开始遍历
//void DFS(const Graph& G, int n)
//{
//	if (!visited[n]) {
//		cout << G.Vex[n].info << " ";
//		visited[n] = true;
//		ArcNode* p = G.Vex[n].firstout;
//		while (p) {
//			DFS(G, p->adjvex);
//			p = p->next;
//		}
//	}
//
//}
////有向图的联通图如果一个点没有出度就停在这个点了
////对非联通图进行深度优先遍历
//void DFSTraverse(const Graph& G)
//{
//	for (int i = 0; i < G.vexnum; i++)
//	{
//		DFS(G, i);
//	}
//}
//
////对联通图进行广度优先遍历
//void BFS(const Graph& G, int n)
//{
//	queue<VexNode> vque;
//	vque.push(G.Vex[n]);
//	while (!vque.empty())
//	{
//		VexNode vext = vque.front();
//		vque.pop();
//		if (!visited[vext.info]) {	//还未访问
//			cout << G.Vex[vext.info].info << " ";
//			visited[vext.info] = true;
//		}
//		ArcNode* arct = vext.firstout;
//		while (arct) {	//将相链接的入队
//			vque.push(G.Vex[arct->adjvex]);
//			arct = arct->next;
//		}
//	}
//}
////对非联通图进行广度优先遍历
//void BFSTraverse(const Graph& G)
//{
//	for (int i = 0; i < G.vexnum; i++)
//	{
//		BFS(G, i);
//	}
//}
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
		ArcNode* p = G.Vex[i].firstarc;
		while (p) {	//将每条边的信息存放到Help中
			if (p->ivex == i) {	//统一以ivex为i的边存入
				if (arcRecord >= G.arcnum)	break;
				H[arcRecord].cost = p->cost;
				H[arcRecord].first = p->ivex;
				H[arcRecord].end = p->jvex;
				p = p->ilink;
				arcRecord++;
			}
			else
			{
				p = p->jlink;
			}
		}

	}//for (int i = 0)
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
				if (vexset[j] == vexset[H[i].end]) {
					vexset[j] = vexset[H[i].first];	
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
	cout << "最小生成树：";
	MiniSpanTree_Kruskal(G);
	cout << endl;
	Delete(G);

}
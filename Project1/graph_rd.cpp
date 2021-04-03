/*
* ����ͼ
* ��ʽ�ṹ
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


#define vexmax 100 //ͼ�е�������

typedef int vex;	//�������λ�ã���Vex[0]�ǵ�һ����
typedef int weight;	//�ߵ�Ȩֵ
//��
struct ArcNode
{
	vex ivex;//���
	vex jvex;//�յ�
	ArcNode* ilink;//ͬһ�������ڵ���һ����
	ArcNode* jlink;//ͬһ�ֵ�����ڵ���һ����
	weight cost;//�ߵ�Ȩֵ
};


typedef int vexType;	//�����Ϣ
//��
struct VexNode
{
	vexType info;//�����Ϣ
	ArcNode* firstarc;//ָ��˵�ı�
	ArcNode* firstout;//�Ӵ˵�����ı�
};
//ͼ
struct Graph
{
	int vexnum;//�������
	int arcnum;//�ߵ�����
	VexNode* Vex;//��
};

//����ͼ
void createGraph(Graph& G)
{
	G.Vex = new VexNode[vexmax];
	cout << "�����봴��ͼ�ĵ����ͱ���\n";
	cin >> G.vexnum >> G.arcnum;
	//��ʼ���㼯��
	for (int i = 0; i < vexmax; i++)
	{
		G.Vex[i].info = i;
		G.Vex[i].firstarc = nullptr;
		G.Vex[i].firstout = nullptr;
	}
	//������
	int f = -1, e = -1, cost = 0;//�ߵ���㡢�յ��Ȩֵ
	for (int i = 0; i < G.arcnum; i++)
	{
		cout << "������ߵ���㡢�յ��Ȩֵ\n";
		cin >> f >> e >> cost;
		if (f < 0 || f >= G.vexnum || e < 0 || e >= G.vexnum) {//�Ƿ�����
			i--;
			continue;
		}
		ArcNode* arc = new ArcNode;	//��̬������
		arc->ivex = f;
		arc->jvex = e;
		arc->cost = cost;
		arc->ilink = G.Vex[f].firstout;	//��ͬ���ı�������
		G.Vex[f].firstout = arc;
		arc->jlink = G.Vex[f].firstarc;	//��ͬ�յ�ı�������
		G.Vex[f].firstarc = arc;
	}
}



//���������ն�̬�ڴ�
void Delete(Graph& G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode* arc = G.Vex[i].firstout;
		if (!arc)	continue;	//�˵�û��
		else {
			while (arc) {
				ArcNode* d = arc;
				arc = arc->ilink;
				cout << "ɾ��<" << d->ivex << "," << d->jvex << ">��\n";
				delete d;
			}
		}
	}
	delete[]G.Vex;
}

//����ͨͼ����������ȱ���
bool visited[vexmax] = { false };//�Ƿ���ʹ��ı��
//��n�㿪ʼ����
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
//����ͼ����ͨͼ���һ����û�г��Ⱦ�ͣ���������
//�Է���ͨͼ����������ȱ���
void DFSTraverse(const Graph& G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		DFS(G, i);
	}
}

//����ͨͼ���й�����ȱ���
void BFS(const Graph& G, int n)
{
	queue<VexNode> vque;
	vque.push(G.Vex[n]);
	while (!vque.empty())
	{
		VexNode vext = vque.front();
		vque.pop();
		if (!visited[vext.info]) {	//��δ����
			cout << G.Vex[vext.info].info << " ";
			visited[vext.info] = true;
		}
		ArcNode* arct = vext.firstout;
		while (arct) {	//�������ӵ����
			vque.push(G.Vex[arct->jvex]);
			arct = arct->ilink;
		}
	}
}
//�Է���ͨͼ���й�����ȱ���
void BFSTraverse(const Graph& G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		BFS(G, i);
	}
}
//Kruskal�㷨--��С������
//�����ṹ
struct Help
{
	weight cost;//Ȩֵ
	vex first;//���
	vex end;//�յ�
};

void MiniSpanTree_Kruskal(const Graph& G)
{
	Help* H = new Help[G.arcnum];
	int arcRecord = 0;//��¼�Ѵ洢�ı�
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode* p = G.Vex[i].firstout;
		while (p) {	//��ÿ���ߵ���Ϣ��ŵ�Help��
			if (arcRecord < G.arcnum) {
				H[arcRecord].cost = p->cost;
				H[arcRecord].first = p->ivex;
				H[arcRecord].end = p->jvex;
				p = p->ilink;
				arcRecord++;
			}

		}

	}
	//���ţ�����Ȩֵ��С������
	sort(H, H + G.arcnum, [](const Help& a, const Help& b) {
		return a.cost < b.cost;
		});
	int* vexset = new int[G.vexnum];//��¼������ݣ���ֹ�ɻ�
	for (int i = 0; i < G.vexnum; i++)
	{
		vexset[i] = i;
	}
	for (int i = 0; i < G.arcnum; i++)
	{
		if (vexset[H[i].first] != vexset[H[i].end])	//�����ǰ�ߵ������յ㲻��ͬһ���ݣ�����ɻ�
		{
			cout << "<" << H[i].first << "," << H[i].end << "> ";
			for (int j = 0; j < G.vexnum; j++)	//ͳһ����first����
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
	for (int i = 0; i < vexmax; i++)	visited[i] = false;	//���㷽���ظ�ʹ��
	cout << endl;
	BFSTraverse(G);
	for (int i = 0; i < vexmax; i++)	visited[i] = false;	//���㷽���ظ�ʹ��
	cout << endl;
	MiniSpanTree_Kruskal(G);
	cout << endl;
	Delete(G);

}
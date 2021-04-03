/*
* ����ͼ
* ��ʽ�ṹ
* �����ڽӱ��������ڽӱ�
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
	bool mark;//���
	vex ivex, jvex;//��������
	ArcNode* ilink;//i������һ����
	ArcNode* jlink;//j����һ����
	weight cost;//�ߵ�Ȩֵ
};


typedef int vexType;	//�����Ϣ
//��
struct VexNode
{
	vexType info;//�����Ϣ
	ArcNode* firstarc;//�˵�ĵ�һ����
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
	}
	//������
	int f = -1, e = -1, cost = 0;//�ߵ���㡢�յ��Ȩֵ
	for (int i = 0; i < G.arcnum; i++)
	{
		cout << "������ߵ���㡢�յ��Ȩֵ\n";
		cin >> f >> e >> cost;
		if (f < 0 || f >= G.vexnum || e < 0 || e >= G.vexnum) {//�Ƿ�����
			i--;
			cout << "�Ƿ����ݣ����������룡\n";
			continue;
		}
		ArcNode* arc = new ArcNode;	//��̬������
		arc->cost = cost;
		arc->ivex = f;
		arc->jvex = e;
		arc->ilink = G.Vex[f].firstarc;	//���� <0,1> �� <1,0>���Դ������ߣ���������ڽӱ�ͬ���ڽӱ�������һ�ߴ���������	
		G.Vex[f].firstarc = arc;		//�����ڽӱ�����������������ͬ��
		arc->jlink = G.Vex[e].firstarc;
		G.Vex[e].firstarc = arc;
		arc->mark = false;
	}
}



//���������ն�̬�ڴ�
/*
* ���ú���Ϣ�����綼��ivexΪɾ������ôarc->ivex��Ϊ��ǰ�� if��arc->ivex != i��
*/
void Delete(Graph& G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode* arc = G.Vex[i].firstarc;
		if (!arc)	continue;	//�˵�û��
		else {
			//ֻɾ��һ���ߣ�Ŀ����ɾ���������Ϊivex��ÿ���ߣ�	��Ҫ��ǰ������ɾ��
			while (arc)
			{
				ArcNode* parc = nullptr;//��Ϊarc��ǰ����
				while (arc) {	//ɾ����iΪivex�ı�
					if (arc->ivex != i) {
						parc = arc;
						arc = arc->jlink;
					}
					else
					{
						break;
					}
				}
				if (!arc) {	//��i������jvex����
					break;//�Ȼ����whileע����	��������˵�arcΪ��һֱ�ظ�
				}
				else      //�ҵ�Ҫɾ���ı���
				{
					if (!parc) {	//Ҫɾ����firstarc
						G.Vex[i].firstarc = arc->ilink;
					}
					else {	//����firstarc����parcΪǰ��
						if (parc->ivex == i) {	//��ivex����jvex
							parc->ilink = arc->ilink;
						}
						else  parc->jlink = arc->ilink;
					}
					ArcNode* del = arc;//����ɾ����
					ArcNode* p = G.Vex[arc->jvex].firstarc;//һ���߽����ָ��ָ��һ��ɾ������һ��ָ��ı�
					if (p->ivex == i) {	//�����һ���߾���Ҫɾ����
						G.Vex[arc->jvex].firstarc = p->jlink;//�ı�ָ��
					}
					else
					{
						ArcNode* q = p;				//p��һ����Ҳ����p = p->ilink
						if (p->ivex == arc->jvex) {
							p = p->ilink;
						}
						else
						{
							p = p->jlink;
						}
						while (p) {
							if (p->ivex == i) {	//�ҵ�Ҫɾ���ı�
								if (q->ivex == arc->jvex) {	//û�б�Ҫ���ж�
									q->ilink = p->jlink;
								}
								else
								{
									q->jlink = p->jlink;
								}
								p = nullptr;
								break;
							}
							else        //���ǽ���������
							{
								if (p->ivex == arc->jvex) {//�ж�Ҫ��ָ��ĵ���ivex����jvex
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
					cout << "ɾ��<" << G.Vex[i].info << "," << del->jvex << ">��\n";
					delete del;
				}//else [if (!arc)]

			}





		}//esle [if (!arc)]����
	}//for (int i)


	delete[]G.Vex;
}

////����ͨͼ����������ȱ���
//bool visited[vexmax] = { false };//�Ƿ���ʹ��ı��
////��n�㿪ʼ����
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
////����ͼ����ͨͼ���һ����û�г��Ⱦ�ͣ���������
////�Է���ͨͼ����������ȱ���
//void DFSTraverse(const Graph& G)
//{
//	for (int i = 0; i < G.vexnum; i++)
//	{
//		DFS(G, i);
//	}
//}
//
////����ͨͼ���й�����ȱ���
//void BFS(const Graph& G, int n)
//{
//	queue<VexNode> vque;
//	vque.push(G.Vex[n]);
//	while (!vque.empty())
//	{
//		VexNode vext = vque.front();
//		vque.pop();
//		if (!visited[vext.info]) {	//��δ����
//			cout << G.Vex[vext.info].info << " ";
//			visited[vext.info] = true;
//		}
//		ArcNode* arct = vext.firstout;
//		while (arct) {	//�������ӵ����
//			vque.push(G.Vex[arct->adjvex]);
//			arct = arct->next;
//		}
//	}
//}
////�Է���ͨͼ���й�����ȱ���
//void BFSTraverse(const Graph& G)
//{
//	for (int i = 0; i < G.vexnum; i++)
//	{
//		BFS(G, i);
//	}
//}
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
		ArcNode* p = G.Vex[i].firstarc;
		while (p) {	//��ÿ���ߵ���Ϣ��ŵ�Help��
			if (p->ivex == i) {	//ͳһ��ivexΪi�ıߴ���
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
	cout << "��С��������";
	MiniSpanTree_Kruskal(G);
	cout << endl;
	Delete(G);

}
#include "graph_Cdesign.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::setiosflags;
using std::setw;
using std::ios;
using std::to_string;
using std::queue;

//创建图
Graph::Graph()
{
	vexnum = rand() % 20 + 10;//随机生成11~20个村庄
	arcnum = 0;//先初始化为零
	Dhp = nullptr;
	village = new Village[vexMax];
	for (int i = 0; i < vexnum; i++)
	{
		village[i] = { "村庄" + to_string(i),i };//赋上序号,村庄名字
	}
	//创建二维数组
	Arcs = new Arc * [vexMax];
	for (int st = 0; st < vexMax; st++) {
		Arcs[st] = new Arc[vexMax];
	}

	srand(int(time(0)));
	//初始化邻接矩阵
	for (int i = 0; i < vexMax; i++) {
		for (int j = 0; j < vexMax; j++) {
			if (i == j) {
				Arcs[i][j] = 0;	//自己到自己路径为0
			}
			else
			{
				Arcs[i][j] = wMax;
			}

		}
	}//for(i)
	for (int i = 0; i < vexnum; i++) {	//邻接上矩阵
		for (int j = i; j < vexnum; j++) {
			if (i == j)	continue;
			else
			{
				int temp = rand() & 10 + 1;//随机生成1~10的数，小于等于2则两个点不相邻,即2成概率
				if (temp > 2) {
					Arcs[i][j] = rand() % 100 + 1;	//随机生成1~100的路径
					Arcs[j][i] = rand() % 100 + 1;
					arcnum += 2;//生成了两条边
				}
			}
		}//for (int j = i)
	}//for (int i)

}
//析构图
Graph::~Graph()
{
	if (village) {
		delete[]village;
		village = nullptr;
	}
	if (Dhp) {
		delete[]Dhp;
		Dhp = nullptr;
	}

	for (int st = 0; st < vexMax; st++) {
		if (Arcs[st]) {
			delete[]Arcs[st];
			Arcs[st] = nullptr;
		}

	}
	if (Arcs) {
		delete[]Arcs;
		Arcs = nullptr;
	}

}
//输出图的信息
void Graph::display()
{
	cout << "图的边数为：" << vexnum << "图的点数为：" << arcnum << endl;
	/*for (int i = 0; i < vexnum; i++) {
		cout << "村庄序号：" << setw(3) << setiosflags(ios::left) << village[i].pos
			<< "   村庄名字：" << setw(3) << setiosflags(ios::left) << village[i].name << endl;
	}*/

	cout << "邻接矩阵为：" << endl;
	for (int i = 0; i < vexnum; i++) {
		for (int j = 0; j < vexnum; j++) {
			if (Arcs[i][j] == wMax) {	//如果无路径输出∞
				cout << setw(3) << setiosflags(ios::left) << "∞" << " ";
			}
			else
			{
				cout << setw(3) << setiosflags(ios::left) << Arcs[i][j] << " ";
			}

		}
		cout << endl;
	}
	cout << endl;
}
//添加点
void Graph::addVex() {
	vexnum++;
	village[vexnum - 1] = { "村庄" + to_string(vexnum - 1),vexnum - 1 };
	for (int st = 0; st < vexnum; st++) {
		if (st != vexnum - 1) {	//点自己路径为0
			int temp = rand() & 10 + 1;//随机生成1~10的数，小于等于2则两个点不相邻,即2成概率
			if (temp > 2) {
				Arcs[vexnum - 1][st] = rand() % 100 + 1;	//随机生成1~100的路径
				Arcs[st][vexnum - 1] = rand() % 100 + 1;
				arcnum += 2;//生成了两条边
			}
		}

	}
}
//删除点
bool Graph::delVex(int n) {
	if (n < 0 || n >= vexnum) {
		cout << "请输入正确的点\n";
		return false;
	}
	else
	{
		int sub_arcnum = 0;//减去边的数量
		for (int st = 0; st < vexnum; st++) {//统计要删除的边数
			if (Arcs[n][st] != wMax && Arcs[n][st] != 0) {
				sub_arcnum += 2;
			}
		}
		//要删除的点及相关边与最后的点交换，然后点数减1，避免移动
		Village temp = village[n];
		village[n] = village[vexnum - 1];
		village[vexnum - 1] = temp;
		for (int st = 0; st < vexnum; st++) {
			Arc temp = Arcs[n][st];
			Arcs[n][st] = Arcs[vexnum - 1][st];
			Arcs[vexnum - 1][st] = Arcs[n][st];

			temp = Arcs[st][n];
			Arcs[st][n] = Arcs[st][vexnum - 1];
			Arcs[st][vexnum - 1] = temp;
		}
		arcnum -= sub_arcnum;//减去边数
		vexnum--;//减去点数
		return true;
	}
}
//狄克斯特拉(Dijkstra)算法求最短路径
void Graph::shortestPath_DIJ(int n)
{
	if (n < 0 || n >= vexnum) {
		cout << "n是不正确数据" << endl;
		return;
	}
	/*-----------------------------先初始化辅助数组---------------------------*/
	Dhp = new Dhelp[vexMax];
	for (int i = 0; i < vexnum; i++) {
		if (Arcs[n][i] != wMax)	//如果 n 和 i 之间有弧
			Dhp[i] = { false,n,Arcs[n][i] };
		else		//如果 n 和 i 之间无弧，则前驱初始化为 -1
		{
			Dhp[i] = { false,-1,Arcs[n][i] };
		}
	}
	Dhp[n] = { true,-1,0, };	//n到n之间权值置为零

	for (int i = 0; i < vexnum - 1; i++) {	//依次算出n到每个点的最短路径
		int min = wMax;	//存放最小值
		int v = n;//存放最小值的点
		for (int j = 0; j < vexnum; j++) {
			if (!Dhp[j].S && Dhp[j].cost < min) {	//如果点未算出最短路径且权值小于最小值
				min = Dhp[j].cost;
				v = j;
			}

		}//for(j)

		Dhp[v].S = true;	//已算出最短路径
		for (int k = 0; k < vexnum; k++) {	//加入一个新点，更新最短路径
			//如果已新加入点为中转点，权值更小则更换
			if ((!Dhp[k].S) && (Dhp[k].cost > Dhp[v].cost + Arcs[v][k])) {
				Dhp[k] = { false,v,Dhp[v].cost + Arcs[v][k] };
			}
		}//for(k)



	}//for(i)



}

//输出每个最短路径
void Graph::displayShortestPath()
{
	int v = -1;//输出v到每个点的最短路径
	for (int i = 0; i < vexnum; i++) {	//找出v点
		if (Dhp[i].path == -1) {
			v = i;
			break;
		}
	}

	for (int i = 0; i < vexnum; i++) {
		if (i != v) {
			cout << "从村庄" << setw(3) << setiosflags(ios::left) << v << "到村庄"
				<< setw(3) << setiosflags(ios::left) << i << "最短路径长度为："
				<< setw(3) << setiosflags(ios::left) << Dhp[i].cost
				<< "   从村庄" << setw(3) << setiosflags(ios::left) << i << "到村庄"
				<< setw(3) << setiosflags(ios::left) << v << "的路径为";
			queue<int> ique;//创建一个队列，把路径入队再输出既为村庄i到有医院的路径
			for (int t = Dhp[i].path; t != -1; t = Dhp[t].path) {
				ique.push(t);
			}
			cout << i;
			while (!ique.empty()) {
				cout << "-->" << ique.front();
				ique.pop();
			}
			cout << endl;
		}
	}
	//清空方便后面使用
	if (Dhp) {
		delete[]Dhp;
		Dhp = nullptr;
	}

}

//把医院设置每个村庄，算出最短路径，选出最合适的
void Graph::AllshortestPath()
{
	int* sumPathLength = new int[vexnum];//路径长度和
	for (int i = 0; i < vexnum; i++) {	//初始化数组
		sumPathLength[i] = 0;
	}
	cout << "--------------------------------------------------------------------------------------\n";
	for (int st = 0; st < vexnum; st++)
	{
		cout << "医院选在村庄" << st << "的情况\n\n";
		shortestPath_DIJ(st);
		for (int rd = 0; rd < vexnum; rd++) {
			sumPathLength[st] += Dhp[rd].cost;//算出路径之和
		}
		displayShortestPath();
		cout << "\n医院选在村庄" << st << "所有最短路径和为：" << sumPathLength[st] << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}
	int hospitalPos = -1;//医院选择的位置
	int minCost = wMax;//最小值
	for (int st = 0; st < vexnum; st++) {//求出路径和最小的
		if (sumPathLength[st] < minCost) {
			hospitalPos = st;
			minCost = sumPathLength[st];
		}
	}
	for (int st = 0; st < vexnum; st++) {
		cout << "医院选择在村庄" << setw(2) << setiosflags(ios::left) << st
			<< "时路径总长度为：" << setw(3) << setiosflags(ios::left) << sumPathLength[st] << endl;
	}
	cout << "\n医院选择在村庄" << hospitalPos << "最合适，最短总长度为：" << minCost << endl;
	delete[]sumPathLength;//回收内存
}

//主函数
void Main()
{
	bool start = true;
	int option = 0;
	Graph* G = nullptr;
	while (start) {//循环，start为false时结束
		cout << "---------------------------\n";
		cout << "请输入选择\n";
		cout << "输入 1 创建一个图\n";
		cout << "输入 2 输出图的信息\n";
		cout << "输入 3 输出医院选址情况\n";
		cout << "输入 4 添加点\n";
		cout << "输入 5 结束程序\n";
		cout << "---------------------------\n";
		cin >> option;
		if (option < 1 || option > 5) {
			cout << "请输入正确数据\n";
			continue;
		}
		switch (option)
		{
		case 1:
		{
			if (G) {
				delete G;
			}
			G = new Graph;
			cout << "成功创建一个图\n";
			break;
		}
		case 2:
		{
			if (!G) {
				cout << "当前未创建图\n";
			}
			else
			{
				G->display();
			}

			break;
		}
		case 3:
		{
			if (!G) {
				cout << "当前未创建图\n";
			}
			else
			{
				G->AllshortestPath();
			}
			break;
		}
		case 4:
		{
			if (!G) {
				cout << "当前未创建图\n";
			}
			else
			{
				G->addVex();
				cout << "成功添加一个点\n";
			}
			break;
		}
		//case 5:
		//{
		//	if (!G) {
		//		cout << "当前未创建图\n";
		//	}
		//	else
		//	{
		//		int n = 0;
		//		cout << "请输入要删除的点\n";
		//		cin >> n;
		//		if (G->delVex(n)) {
		//			cout << "成功删除一个点\n";
		//		}
		//	}
		//	break;
		//}
		case 5:
		{
			cout << "程序结束\n";
			start = false;
			break;
		}
		default:
			break;
		}
	}//while
	if (G) {
		delete G;
	}

}


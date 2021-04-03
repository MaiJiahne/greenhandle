#pragma once
#include <string>

using std::string;

#define vexMax 50		//�����ֵ
#define	wMax	32767	//���·����Ȩֵ��

struct Village
{
	string name;//��ׯ����
	int pos = 0;//��ׯ���
};

struct Dhelp	//�ҿ�˹����(Dijkstra)�㷨�����ṹ
{
	bool S;	//���Ƿ���������·��
	int path;	//���·���ϵ�ֱ��ǰ����
	int cost;	//��ĳ������·��Ȩֵ
};

typedef int Arc;//��

class Graph
{
public:
	Graph();
	void display();//���ͼ��Ϣ
	void addVex();//��ӵ�
	bool delVex(int);//ɾ����
	void shortestPath_DIJ(int);//�õҿ�˹����(Dijkstra)�㷨�����·��
	void displayShortestPath();//������·��
	void AllshortestPath();//ÿ���㶼������·��
	~Graph();

private:
	int vexnum;//������
	int arcnum;//������
	Village* village;//��ׯ
	Arc** Arcs;//�ٽ�����
	Dhelp* Dhp;// �ҿ�˹����(Dijkstra)�㷨�����ṹ
};

//���е�������
void Main();


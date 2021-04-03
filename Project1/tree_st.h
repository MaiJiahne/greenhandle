#pragma once
#include<string>
using std::string;

struct treeNode
{
	char ch;
	treeNode* lchild;
	treeNode* rchild;
	bool LTag;//线索标志
	bool RTag;
	treeNode() :ch('\0'), lchild(nullptr), rchild(nullptr), LTag(false), RTag(false) {}
	treeNode(char c) :ch(c), lchild(nullptr), rchild(nullptr), LTag(false), RTag(false) {}
	treeNode(char c, treeNode* lc, treeNode* rc) :ch(c), lchild(lc), rchild(rc), LTag(false), RTag(false) {}
	~treeNode() = default;
};

class BiTree {
public:
	BiTree() :tree(nullptr), Node_num(0), head(nullptr) {}
	~BiTree();
	void createTree(string);
	//void Insert(char);
	bool empty();
	void Find_out(char);
	bool isFind(char);
	void showTree();
	int treeHigh();
	int nodeNum();
	int leafNum();
	int treeDegree();
	void treeInfo();
	void preOrderTraverse();
	void inOrderTraverse();
	void postOrderTraverse();
	void preOrderTraverseStack();
	void inOrderTraverseStack();
	void postOrderTraverseStack();
	void InOrderThread();	//线索化后不在调用之前树的基本操作
	void InOrderThread_show();
	void find_preOrsuc();
private:
	treeNode* tree;
	int Node_num;//结点数量
	treeNode* head;//head为头结点
	//静态函数用于递归
	static void deleteNode(treeNode*&);
	static void show(treeNode*);
	static bool Find(treeNode*, char);
	static void Find_char(treeNode*, char);
	static int Tree_High(treeNode*);
	static int NodeNum(treeNode*);
	static void TreeDegree(treeNode*, int&);
	static int LeafNum(treeNode*);
	static void PreOrderTraverse(treeNode*);
	static void InOrderTraverse(treeNode*);
	static void PostOrderTraverse(treeNode*);
	static void Threading(treeNode*);
	static treeNode* pre;
};
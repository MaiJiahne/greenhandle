#include "tree_st.h"
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::vector;


BiTree::~BiTree()
{
	deleteNode(tree);
	if (head) {
		head->lchild = nullptr;
		head->rchild = nullptr;
		delete head;
		cout << "创建了头结点，已删除" << endl;
	}
}

//删除结点，并递归调用左右子树
void BiTree::deleteNode(treeNode*& tr)
{
	if (tr) {
		if (!tr->LTag)		//当标签是false时才可以删除
			deleteNode(tr->lchild);
		if (!tr->RTag)
			deleteNode(tr->rchild);
		cout << "删除值为" << tr->ch << "的结点" << endl;
		delete tr;
		tr = nullptr;
	}

}

//以字符串内容创建二叉树
void BiTree::createTree(string str)
{
	stack<treeNode*> TreeSta;
	treeNode* p = nullptr;
	int option = 0;	//选择插入的左右子树，1插入左子树，2插入右子树
	//bool isEmptyTree = false;
	for (auto ch : str) {
		switch (ch)
		{
			//想以空格做空树(用空对象即可)
			//case ' ':
			//	tree = new treeNode(ch);
			//	isEmptyTree = true;
			//	break;
		case '(':
			TreeSta.push(p);
			option = 1;
			break;
		case ')':
			TreeSta.pop();
			break;
		case ',':
			option = 2;
			break;
		default:
			p = new treeNode(ch);
			Node_num++;
			if (!tree) {
				tree = p;
			}
			else {
				switch (option)
				{
				case 1:
					TreeSta.top()->lchild = p;
					break;
				case 2:
					TreeSta.top()->rchild = p;
					break;
				default:
					break;
				}//内层switch
			}//else
			break;
		}//外层switch
	}//for
}


////插入数据到树中
//void BiTree::Insert(char c)
//{
//	if (!tree) {	//此树为空，创建一颗树
//		tree = new treeNode(c);
//		Node_num++;
//	}
//	else {
//		int i = 0;
//		treeNode* p = tree->lchild;//分别指向左右子树
//		treeNode* q = tree->rchild;
//		do {
//			cout << "输入 1 插入左子树，输入 2 插入右子树" << endl;
//			cin >> i;
//			if (i == 1) {		//如果左子树为空，可以插入,循环结束，不为空，继续选择
//				if (p) {
//					p = p->lchild;
//					continue;
//				}
//			}
//			else if (i == 2) {		//如果右子树为空，可以插入，不为空，继续选择
//				if (p) {
//					p = p->rchild;
//					continue;
//				}
//			}
//			else {
//				cout << "请输入正确选择" << endl;
//				continue;
//			}
//		}//while
//		while (p);
//		p = new treeNode(c);
//		Node_num++;
//	}//最外层else
//}


//输出结点，并递归调用它的左右子树
void BiTree::show(treeNode* tr)
{
	if (tr) {
		cout << tr->ch << " ";
		if (tr->lchild || tr->rchild) {	//如果左右子树为空就不输出括号
			cout << "(";
			if (tr->lchild)
				show(tr->lchild);
			cout << ",";
			if (tr->rchild)
				show(tr->rchild);
			cout << ")";
		}
	}
}

//遍历二叉树
void BiTree::showTree()
{
	if (!tree) {
		cout << "此树为空" << endl;
	}
	else {
		show(tree);
		cout << endl;
	}

}

//判断树是否为空
bool BiTree::empty()
{
	if (!Node_num) {
		return true;
	}
	return false;
}

//查找树是有有含有参数的结点，没有返回false
bool BiTree::Find(treeNode* tr, char ch)
{
	bool bo1 = false;
	bool bo2 = false;
	if (!tr) {
		return false;
	}
	else if (tr->ch == ch) {
		return true;
	}
	else {
		bo1 = Find(tr->lchild, ch);
		bo2 = Find(tr->rchild, ch);
	}
	if (!bo1 && !bo2)	//左右子树都找不到
		return false;
	else {
		return true;
	}
}

//查找树是有有含有参数的结点，没有返回false
bool BiTree::isFind(char ch)
{
	return Find(tree, ch);
}

//输出树中ch结点的左右孩子树
void BiTree::Find_char(treeNode* tr, char ch)
{
	if (tr) {
		if (tr->ch == ch) {
			cout << tr->ch << " " << "(" << tr->lchild->ch << "," << tr->rchild->ch << ")";
			cout << endl;
		}
		else {
			Find_char(tr->lchild, ch);
			Find_char(tr->rchild, ch);
		}
	}
}

//输出ch的左右孩子结点，没有则不输出
void BiTree::Find_out(char ch)
{
	if (!isFind(ch)) {	//如果在树没有ch结点
		cout << "树没有" << ch << "结点" << endl;
	}
	else {
		Find_char(tree, ch);
	}
}

//计算树的高度
int BiTree::Tree_High(treeNode* tr)
{
	if (!tr)
		return 0;
	else {
		return (Tree_High(tr->lchild) > Tree_High(tr->rchild)) ? Tree_High(tr->lchild) + 1 : Tree_High(tr->rchild) + 1;
	}
}

//返回树的高度
int BiTree::treeHigh()
{
	return Tree_High(tree);
}

//返回树的结点数
int BiTree::NodeNum(treeNode* tr)
{
	if (!tr)
		return 0;
	else {
		return NodeNum(tr->lchild) + NodeNum(tr->rchild) + 1;
	}
}

//返回树的结点数
int BiTree::nodeNum()
{
	//cout << "树的结点数:" << Node_num << endl;
	return NodeNum(tree);
}

//返回树的叶子结点数
int BiTree::LeafNum(treeNode* tr)
{
	if (!tr)
		return 0;
	else if (!tr->lchild && !tr->rchild)
		return 1;
	else {
		return LeafNum(tr->lchild) + LeafNum(tr->rchild);
	}
}

//返回树的叶子结点数
int BiTree::leafNum()
{
	return LeafNum(tree);
}

//返回二叉树的度
void BiTree::TreeDegree(treeNode* tr, int& degree)
{
	if (!tr || (!tr->lchild && !tr->rchild));	//如果空树或者树只有一个结点，度为零
	else if ((tr->lchild && !tr->rchild) || (!tr->lchild && tr->rchild)) {			//如果有左右子树中一颗，度为1
		degree = 1;
	}
	else {										//如含有左右子树，度为2，二叉树度最大为2
		degree = 2;
		return;
	}
	if (tr) {
		if (tr->lchild)
			TreeDegree(tr->lchild, degree);
		if (tr->rchild)
			TreeDegree(tr->lchild, degree);
	}

}

//返回二叉树的度
int BiTree::treeDegree()
{
	int degree = 0;		//度初始化为0
	TreeDegree(tree, degree);
	return degree;
}


//返回树的相关信息
void BiTree::treeInfo()
{
	cout << "树的结点数:" << nodeNum() << endl;
	cout << "树的叶结点数:" << leafNum() << endl;
	cout << "树的高度:" << treeHigh() << endl;
	cout << "树的度数:" << treeDegree() << endl;
}

//递归先序输出二叉树
void BiTree::PreOrderTraverse(treeNode* tr)
{
	if (tr) {
		cout << tr->ch << " ";
		PreOrderTraverse(tr->lchild);
		PreOrderTraverse(tr->rchild);
	}
}

void BiTree::preOrderTraverse()
{
	if (!tree) {
		cout << "此树为空" << endl;
	}
	else {
		PreOrderTraverse(tree);
		cout << endl;
	}
}

//递归中序输出二叉树
void BiTree::InOrderTraverse(treeNode* tr)
{
	if (tr) {
		InOrderTraverse(tr->lchild);
		cout << tr->ch << " ";
		InOrderTraverse(tr->rchild);
	}
}

void BiTree::inOrderTraverse()
{
	if (!tree) {
		cout << "此树为空" << endl;
	}
	else {
		InOrderTraverse(tree);
		cout << endl;
	}
}

//递归后序输出二叉树
void BiTree::PostOrderTraverse(treeNode* tr)
{
	if (tr) {
		PostOrderTraverse(tr->lchild);
		PostOrderTraverse(tr->rchild);
		cout << tr->ch << " ";
	}
}

void BiTree::postOrderTraverse()
{
	if (!tree) {
		cout << "此树为空" << endl;
	}
	else {
		PostOrderTraverse(tree);
		cout << endl;
	}
}

//非递归先序输出二叉树
void BiTree::preOrderTraverseStack()
{
	if (!tree) {
		cout << "此树为空" << endl;
	}
	else {
		treeNode* p = tree;
		stack<treeNode*> tvec;
		while (p || !tvec.empty()) {
			if (p) {
				tvec.push(p);
				cout << p->ch << " ";
				p = p->lchild;
			}
			else {
				p = tvec.top();
				tvec.pop();
				p = p->rchild;
			}
		}
		cout << endl;
	}
}

//非递归中序输出二叉树
void BiTree::inOrderTraverseStack()
{
	if (!tree) {
		cout << "此树为空" << endl;
	}
	else {
		treeNode* p = tree;
		stack<treeNode*> tvec;
		while (p || !tvec.empty()) {	// p为空和栈为空时结束循环
			if (p) {
				tvec.push(p);
				p = p->lchild;
			}
			else {
				p = tvec.top();
				tvec.pop();
				cout << p->ch << " ";
				p = p->rchild;
			}
		}
		cout << endl;
	}
}

//非递归后序输出二叉树
//void BiTree::postOrderTraverseStack()
//{
//	if (!tree) {
//		cout << "此树为空" << endl;
//	}
//	else {
//		//stack<treeNode*> tvec;
//		treeNode* stack[50] = { nullptr };//栈，第一个点不用
//		bool isRight[50] = { false };	//右子树是否已遍历
//		int top = 0;	//栈顶位置
//		treeNode* p = tree;
//		while (p || top != 0) {
//			if (p) {
//				top++;
//				stack[top] = p;
//				isRight[top] = false;
//				p = p->lchild;
//			}
//			else if (isRight[top]) {
//				cout << stack[top--]->ch << " ";	//可以访问并出栈
//			}
//			else if (top > 0) {
//				//右子树还未访问
//				p = stack[top]->rchild;
//				isRight[top] = true;
//			}
//
//		}//while
//
//		cout << endl;
//
//	}//最外层else
//
//}
//非递归后序输出二叉树
void BiTree::postOrderTraverseStack()
{
	if (!tree) {
		cout << "此树为空" << endl;
	}
	else {
		stack<treeNode*> trStack;//栈
		bool tag[50] = { false };	//标记右子树是否已遍历
		int top = -1;	//栈顶位置,-1时栈为空
		treeNode* p = tree;
		while (p || top >= 0) {
			if (p) {
				top++;
				trStack.push(p);
				tag[top] = false;
				p = p->lchild;
			}
			else if (tag[top]) {	//可以访问并出栈
				cout << trStack.top()->ch << " ";
				trStack.pop();
				top--;
			}
			else if (top >= 0) {	//右子树还未访问

				p = trStack.top()->rchild;
				tag[top] = true;
			}

		}//while

		cout << endl;

	}//最外层else

}

//全局变量
treeNode* BiTree::pre = nullptr;

//线索化二叉树
void BiTree::Threading(treeNode* tr)
{
	if (tr) {
		Threading(tr->lchild);
		if (!tr->lchild) {
			tr->lchild = pre;
			tr->LTag = true;
		}
		else
			tr->LTag = false;
		if (!pre->rchild) {
			pre->rchild = tr;
			pre->RTag = true;
		}
		else
			pre->RTag = false;
		pre = tr;
		Threading(tr->rchild);
	}
}

void BiTree::InOrderThread()
{
	head = new treeNode();	//创建头结点
	if (!tree) {
		head->lchild = head;	//树为空，左子树指向自己
		head->rchild = head;	//右子树指向自己		
	}
	else {
		//false：指针不保存，pre递归回来还是head，递归回一层，指针已回去就是无法正确连接
		head->lchild = tree;
		head->LTag = true;
		pre = head;
		Threading(tree);
		pre->rchild = head;		//最后一个结点(没有后继结点了)后驱指向头结点，头结点右子树指向最后一个结点
		pre->RTag = true;
		head->rchild = pre;
		head->RTag = true;
	}
}

//中序线索二叉树遍历
void BiTree::InOrderThread_show()
{
	if (!head) {
		cout << "此树并未线索化" << endl;
	}
	else if (!head->lchild) {
		cout << "此树为空" << endl;
	}
	else {
		treeNode* p = head->lchild;
		while (p != head) {
			while (!p->LTag)	p = p->lchild;//指向最先访问的结点
			cout << p->ch << " ";
			while (p->RTag && p->rchild != head) {
				p = p->rchild;
				cout << p->ch << " ";
			}
			p = p->rchild;
		}
		cout << endl;
	}

}

//输出根的前驱和后继
void BiTree::find_preOrsuc()
{
	if (!tree) {
		cout << "此树为空" << endl;
	}
	else {
		treeNode* p = tree;
		if (p->LTag) {	//如果左标签为true，左子树是前驱，如果为false，最左下是前驱。
			cout << "根结点的前驱为：" << p->lchild->ch << endl;
		}
		else {
			while (!p->LTag) {
				p = p->lchild;
			}
			cout << "根结点的前驱为：" << p->ch << endl;
		}
		p = tree;
		if (p->RTag) {
			cout << "根结点的后继为：" << p->rchild->ch << endl;
		}
		else {
			p = p->rchild;
			while (!p->LTag) {
				p = p->lchild;
			}
			cout << "根结点的后继为：" << p->ch << endl;
		}
	}

}


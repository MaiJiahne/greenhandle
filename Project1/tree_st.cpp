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
		cout << "������ͷ��㣬��ɾ��" << endl;
	}
}

//ɾ����㣬���ݹ������������
void BiTree::deleteNode(treeNode*& tr)
{
	if (tr) {
		if (!tr->LTag)		//����ǩ��falseʱ�ſ���ɾ��
			deleteNode(tr->lchild);
		if (!tr->RTag)
			deleteNode(tr->rchild);
		cout << "ɾ��ֵΪ" << tr->ch << "�Ľ��" << endl;
		delete tr;
		tr = nullptr;
	}

}

//���ַ������ݴ���������
void BiTree::createTree(string str)
{
	stack<treeNode*> TreeSta;
	treeNode* p = nullptr;
	int option = 0;	//ѡ����������������1������������2����������
	//bool isEmptyTree = false;
	for (auto ch : str) {
		switch (ch)
		{
			//���Կո�������(�ÿն��󼴿�)
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
				}//�ڲ�switch
			}//else
			break;
		}//���switch
	}//for
}


////�������ݵ�����
//void BiTree::Insert(char c)
//{
//	if (!tree) {	//����Ϊ�գ�����һ����
//		tree = new treeNode(c);
//		Node_num++;
//	}
//	else {
//		int i = 0;
//		treeNode* p = tree->lchild;//�ֱ�ָ����������
//		treeNode* q = tree->rchild;
//		do {
//			cout << "���� 1 ���������������� 2 ����������" << endl;
//			cin >> i;
//			if (i == 1) {		//���������Ϊ�գ����Բ���,ѭ����������Ϊ�գ�����ѡ��
//				if (p) {
//					p = p->lchild;
//					continue;
//				}
//			}
//			else if (i == 2) {		//���������Ϊ�գ����Բ��룬��Ϊ�գ�����ѡ��
//				if (p) {
//					p = p->rchild;
//					continue;
//				}
//			}
//			else {
//				cout << "��������ȷѡ��" << endl;
//				continue;
//			}
//		}//while
//		while (p);
//		p = new treeNode(c);
//		Node_num++;
//	}//�����else
//}


//�����㣬���ݹ����������������
void BiTree::show(treeNode* tr)
{
	if (tr) {
		cout << tr->ch << " ";
		if (tr->lchild || tr->rchild) {	//�����������Ϊ�վͲ��������
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

//����������
void BiTree::showTree()
{
	if (!tree) {
		cout << "����Ϊ��" << endl;
	}
	else {
		show(tree);
		cout << endl;
	}

}

//�ж����Ƿ�Ϊ��
bool BiTree::empty()
{
	if (!Node_num) {
		return true;
	}
	return false;
}

//�����������к��в����Ľ�㣬û�з���false
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
	if (!bo1 && !bo2)	//�����������Ҳ���
		return false;
	else {
		return true;
	}
}

//�����������к��в����Ľ�㣬û�з���false
bool BiTree::isFind(char ch)
{
	return Find(tree, ch);
}

//�������ch�������Һ�����
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

//���ch�����Һ��ӽ�㣬û�������
void BiTree::Find_out(char ch)
{
	if (!isFind(ch)) {	//�������û��ch���
		cout << "��û��" << ch << "���" << endl;
	}
	else {
		Find_char(tree, ch);
	}
}

//�������ĸ߶�
int BiTree::Tree_High(treeNode* tr)
{
	if (!tr)
		return 0;
	else {
		return (Tree_High(tr->lchild) > Tree_High(tr->rchild)) ? Tree_High(tr->lchild) + 1 : Tree_High(tr->rchild) + 1;
	}
}

//�������ĸ߶�
int BiTree::treeHigh()
{
	return Tree_High(tree);
}

//�������Ľ����
int BiTree::NodeNum(treeNode* tr)
{
	if (!tr)
		return 0;
	else {
		return NodeNum(tr->lchild) + NodeNum(tr->rchild) + 1;
	}
}

//�������Ľ����
int BiTree::nodeNum()
{
	//cout << "���Ľ����:" << Node_num << endl;
	return NodeNum(tree);
}

//��������Ҷ�ӽ����
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

//��������Ҷ�ӽ����
int BiTree::leafNum()
{
	return LeafNum(tree);
}

//���ض������Ķ�
void BiTree::TreeDegree(treeNode* tr, int& degree)
{
	if (!tr || (!tr->lchild && !tr->rchild));	//�������������ֻ��һ����㣬��Ϊ��
	else if ((tr->lchild && !tr->rchild) || (!tr->lchild && tr->rchild)) {			//���������������һ�ţ���Ϊ1
		degree = 1;
	}
	else {										//�纬��������������Ϊ2�������������Ϊ2
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

//���ض������Ķ�
int BiTree::treeDegree()
{
	int degree = 0;		//�ȳ�ʼ��Ϊ0
	TreeDegree(tree, degree);
	return degree;
}


//�������������Ϣ
void BiTree::treeInfo()
{
	cout << "���Ľ����:" << nodeNum() << endl;
	cout << "����Ҷ�����:" << leafNum() << endl;
	cout << "���ĸ߶�:" << treeHigh() << endl;
	cout << "���Ķ���:" << treeDegree() << endl;
}

//�ݹ��������������
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
		cout << "����Ϊ��" << endl;
	}
	else {
		PreOrderTraverse(tree);
		cout << endl;
	}
}

//�ݹ��������������
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
		cout << "����Ϊ��" << endl;
	}
	else {
		InOrderTraverse(tree);
		cout << endl;
	}
}

//�ݹ�������������
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
		cout << "����Ϊ��" << endl;
	}
	else {
		PostOrderTraverse(tree);
		cout << endl;
	}
}

//�ǵݹ��������������
void BiTree::preOrderTraverseStack()
{
	if (!tree) {
		cout << "����Ϊ��" << endl;
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

//�ǵݹ��������������
void BiTree::inOrderTraverseStack()
{
	if (!tree) {
		cout << "����Ϊ��" << endl;
	}
	else {
		treeNode* p = tree;
		stack<treeNode*> tvec;
		while (p || !tvec.empty()) {	// pΪ�պ�ջΪ��ʱ����ѭ��
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

//�ǵݹ�������������
//void BiTree::postOrderTraverseStack()
//{
//	if (!tree) {
//		cout << "����Ϊ��" << endl;
//	}
//	else {
//		//stack<treeNode*> tvec;
//		treeNode* stack[50] = { nullptr };//ջ����һ���㲻��
//		bool isRight[50] = { false };	//�������Ƿ��ѱ���
//		int top = 0;	//ջ��λ��
//		treeNode* p = tree;
//		while (p || top != 0) {
//			if (p) {
//				top++;
//				stack[top] = p;
//				isRight[top] = false;
//				p = p->lchild;
//			}
//			else if (isRight[top]) {
//				cout << stack[top--]->ch << " ";	//���Է��ʲ���ջ
//			}
//			else if (top > 0) {
//				//��������δ����
//				p = stack[top]->rchild;
//				isRight[top] = true;
//			}
//
//		}//while
//
//		cout << endl;
//
//	}//�����else
//
//}
//�ǵݹ�������������
void BiTree::postOrderTraverseStack()
{
	if (!tree) {
		cout << "����Ϊ��" << endl;
	}
	else {
		stack<treeNode*> trStack;//ջ
		bool tag[50] = { false };	//����������Ƿ��ѱ���
		int top = -1;	//ջ��λ��,-1ʱջΪ��
		treeNode* p = tree;
		while (p || top >= 0) {
			if (p) {
				top++;
				trStack.push(p);
				tag[top] = false;
				p = p->lchild;
			}
			else if (tag[top]) {	//���Է��ʲ���ջ
				cout << trStack.top()->ch << " ";
				trStack.pop();
				top--;
			}
			else if (top >= 0) {	//��������δ����

				p = trStack.top()->rchild;
				tag[top] = true;
			}

		}//while

		cout << endl;

	}//�����else

}

//ȫ�ֱ���
treeNode* BiTree::pre = nullptr;

//������������
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
	head = new treeNode();	//����ͷ���
	if (!tree) {
		head->lchild = head;	//��Ϊ�գ�������ָ���Լ�
		head->rchild = head;	//������ָ���Լ�		
	}
	else {
		//false��ָ�벻���棬pre�ݹ��������head���ݹ��һ�㣬ָ���ѻ�ȥ�����޷���ȷ����
		head->lchild = tree;
		head->LTag = true;
		pre = head;
		Threading(tree);
		pre->rchild = head;		//���һ�����(û�к�̽����)����ָ��ͷ��㣬ͷ���������ָ�����һ�����
		pre->RTag = true;
		head->rchild = pre;
		head->RTag = true;
	}
}

//������������������
void BiTree::InOrderThread_show()
{
	if (!head) {
		cout << "������δ������" << endl;
	}
	else if (!head->lchild) {
		cout << "����Ϊ��" << endl;
	}
	else {
		treeNode* p = head->lchild;
		while (p != head) {
			while (!p->LTag)	p = p->lchild;//ָ�����ȷ��ʵĽ��
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

//�������ǰ���ͺ��
void BiTree::find_preOrsuc()
{
	if (!tree) {
		cout << "����Ϊ��" << endl;
	}
	else {
		treeNode* p = tree;
		if (p->LTag) {	//������ǩΪtrue����������ǰ�������Ϊfalse����������ǰ����
			cout << "������ǰ��Ϊ��" << p->lchild->ch << endl;
		}
		else {
			while (!p->LTag) {
				p = p->lchild;
			}
			cout << "������ǰ��Ϊ��" << p->ch << endl;
		}
		p = tree;
		if (p->RTag) {
			cout << "�����ĺ��Ϊ��" << p->rchild->ch << endl;
		}
		else {
			p = p->rchild;
			while (!p->LTag) {
				p = p->lchild;
			}
			cout << "�����ĺ��Ϊ��" << p->ch << endl;
		}
	}

}


#include "tree_st.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;


int main()
{
	BiTree bitree;
	string str("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	bitree.createTree(str);
	cout << "����Ϊ��"; bitree.showTree();
	char ch = 'H';
	cout << ch << "�������Һ���Ϊ��"; bitree.Find_out(ch);
	bitree.treeInfo();

	cout << "--------------------------------------------------------------" << endl;
	cout << "���������Ϊ��"; bitree.preOrderTraverse();
	cout << "���ǵݹ��������Ϊ��"; bitree.preOrderTraverseStack();
	cout << "���������Ϊ��"; bitree.inOrderTraverse();
	cout << "���ǵݹ��������Ϊ��"; bitree.inOrderTraverseStack();
	cout << "���������Ϊ��"; bitree.postOrderTraverse();
	cout << "���ǵݹ�������Ϊ��"; bitree.postOrderTraverseStack();

	cout << "--------------------------------------------------------------" << endl;
	bitree.InOrderThread();
	cout << "��������������Ϊ��"; bitree.InOrderThread_show();
	bitree.find_preOrsuc();

	cout << "--------------------------------------------------------------" << endl;
	/*cout << "���������Ϊ��"; bitree.preOrderTraverse();
	cout << "���������Ϊ��"; bitree.inOrderTraverse();
	cout << "���������Ϊ��"; bitree.postOrderTraverse();*/
	/*BiTree bitree1;
	bitree1.showTree();
	cout << "���ĸ߶�:" << bitree1.treeHigh() << endl;
	cout << "���Ľ����:" << bitree1.nodeNum() << endl;
	cout << "����Ҷ�����:" << bitree1.leafNum() << endl;
	cout << "���Ķ���:" << bitree1.treeDegree() << endl;*/
}
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
	cout << "此树为："; bitree.showTree();
	char ch = 'H';
	cout << ch << "结点的左右孩子为："; bitree.Find_out(ch);
	bitree.treeInfo();

	cout << "--------------------------------------------------------------" << endl;
	cout << "树先序输出为："; bitree.preOrderTraverse();
	cout << "树非递归先序输出为："; bitree.preOrderTraverseStack();
	cout << "树中序输出为："; bitree.inOrderTraverse();
	cout << "树非递归中序输出为："; bitree.inOrderTraverseStack();
	cout << "树后序输出为："; bitree.postOrderTraverse();
	cout << "树非递归后序输出为："; bitree.postOrderTraverseStack();

	cout << "--------------------------------------------------------------" << endl;
	bitree.InOrderThread();
	cout << "中序遍历线索输出为："; bitree.InOrderThread_show();
	bitree.find_preOrsuc();

	cout << "--------------------------------------------------------------" << endl;
	/*cout << "树先序输出为："; bitree.preOrderTraverse();
	cout << "树中序输出为："; bitree.inOrderTraverse();
	cout << "树后序输出为："; bitree.postOrderTraverse();*/
	/*BiTree bitree1;
	bitree1.showTree();
	cout << "树的高度:" << bitree1.treeHigh() << endl;
	cout << "树的结点数:" << bitree1.nodeNum() << endl;
	cout << "树的叶结点数:" << bitree1.leafNum() << endl;
	cout << "树的度数:" << bitree1.treeDegree() << endl;*/
}
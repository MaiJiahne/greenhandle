#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::setiosflags;
using std::setw;
using std::ios;
using std::vector;

/*--------------------------------------------顺序查找-----------------------------------------------------*/
#define Size 17 //数组大小，0不存放数据

//初始化数组
void getVaule(char(&ch)[Size])
{
	ch[0] = ' ';
	vector<int> ivec;//用于生成不重复随机数
	for (int i = 0; i < 26; i++) {	//把 0~26 放入向量中，再打乱，形成不重复数
		ivec.push_back(i);
	}
	std::random_shuffle(ivec.begin(), ivec.end());//打乱向量
	for (int i = 1; i < Size; i++)
	{
		ch[i] = ivec[i] + 97;//加上97形成a~z 的ASCII
	}
}
//输出数组
void display(char(&ch)[Size])
{
	cout << "数组为：";
	for (int i = 1; i < Size; i++)
	{
		cout << ch[i] << "  ";
	}
	cout << endl;
}
//顺序查找
int searchSe(char* ar, char ch)
{
	int cmp = 0;//比较次数
	ar[0] = ch;//查找的字母先存放在ar[0]中
	int i = Size - 1;
	cmp++;//比较次数++
	for (i; ar[i] != ar[0]; i--, cmp++);	//如果找到返回位置，没有返回0
	cout << "比较次数为" << cmp << endl;
	return i;
}
/*--------------------------------------------顺序查找-----------------------------------------------------*/

/*--------------------------------------------折半查找-----------------------------------------------------*/
#define iMax 16		//数组大小

//初始化数组
void init(int* ar)
{
	srand(int(time(0)));
	ar[0] = 32767;//ar[0]不存放数据
	for (int i = 1; i < iMax; i++)
	{
		ar[i] = rand() % 1000;	//生成 0~999 的数
	}
}
//输出数组
void display(int* ar)
{
	cout << "数组为：";
	for (int i = 1; i < iMax; i++)
	{
		cout << ar[i] << "  ";
	}
	cout << endl;
}
//采用双向冒泡排序
void deBubbleSort(int(&ar)[iMax])
{
	bool exchange = true;//是否发生交换
	int head = 0;	//未完成排序数组的起始
	int tail = sizeof(ar) / sizeof(ar[0]); ////未完成排序数组的结尾
	int i = head + 1;	//用于比较交换
	int time = 0;//记录第几趟排序
	while (exchange) {
		exchange = false;
		while (i + 1 < tail) {	//从前往后冒泡
			if (ar[i] > ar[i + 1]) {
				int temp = ar[i];		//交换ar[i] 和 ar[i + 1]
				ar[i] = ar[i + 1];
				ar[i + 1] = temp;
				exchange = true;//发生交换
			}
			i++;
		}//while (i + 1 <= tail)
		tail = i + 1;	//更新结尾
		while (exchange && i - 1 > head) {	//从后往前冒泡
			if (ar[i] < ar[i - 1]) {
				int temp = ar[i];		//交换ar[i] 和 ar[i - 1]
				ar[i] = ar[i - 1];
				ar[i - 1] = temp;
				exchange = true;//发生交换
			}
			i--;
		}//while (exchange && i - 1 > head)
		head = i - 1;
	}//while (exchange)
}
int cmp_BS;//比较次数
//折半查找
int BiSearch(int* ar, int n)
{
	int low = 1, high = iMax - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		cmp_BS++;//比较次数++
		if (ar[mid] == n)	return mid;
		else if (ar[mid] < n)	low = mid + 1;
		else	high = mid - 1;
	}
	return 0;
}


/*--------------------------------------------折半查找-----------------------------------------------------*/

/*--------------------------------------------二叉查找树-----------------------------------------------------*/
struct BiSearchTree
{
	char key;
	BiSearchTree* lchild;
	BiSearchTree* rchild;
	BiSearchTree() = default;
	BiSearchTree(char ch) :key(ch), lchild(nullptr), rchild(nullptr) {}
	~BiSearchTree() = default;
};

typedef BiSearchTree BTree;
int cmp_T;//二叉查找比较次数
//插入新结点到二叉排序树
void insertTree(BTree*& T, char ch)
{
	if (!T) {
		T = new BTree(ch);
	}
	else {
		if (ch < T->key) {
			insertTree(T->lchild, ch);
		}
		else
		{
			insertTree(T->rchild, ch);
		}
	}
}
//创建二叉排序树
void createTree(BTree*& T)
{
	char ch;
	while (true)
	{
		cout << "请输入字母，输入'#'创建空结点\n";
		cin >> ch;
		if (ch == '#') break;
		insertTree(T, ch);
	}
}
//二叉树查找
bool BiTreeSearch(BTree* T, char ch)
{
	if (!T) {
		cout << "树为空，没有比较" << endl;
		return false;
	}
	else {
		cmp_T++;//比较次数++
		if (T->key == ch) {
			return true;
		}
		else if (ch < T->key)	return BiTreeSearch(T->lchild, ch);
		else return BiTreeSearch(T->rchild, ch);
		return false;
	}

}
//从二叉排序树删除结点
void deleteTreeNode(BTree*& T, char ch)
{
	if (!BiTreeSearch(T, ch))
	{
		cout << "树中没有" << ch << "结点\n";
		return;
	}
	BTree* D = T;
	BTree* f = nullptr;	//指向D的父母结点
	while (D->key != ch) {
		f = D;	//p指向它的父母结点
		if (ch < D->key) {	//往左子树找，

			D = D->lchild;
		}
		else {//往右子树找
			D = D->lchild;
		}
	}
	if (D->lchild && D->rchild) {	//如果左右子树都不为空
		BTree* s = D->lchild;//指向比D小于且最接近D的结点
		BTree* q = nullptr;	//指向s的父母结点
		while (s->rchild) {	//先找到s最右下的点
			q = s;
			s = s->rchild;
		}
		D->key = s->key;//替换掉要删除的结点
		if (!q) {//比D小于且最接近D的结点直接是D的左子
			D->lchild = s->lchild;	//s无右子树
			delete s;
		}
		else {
			q->rchild = s->lchild;//s的父母结点原本指向s的孩子指针指向s的左子树
			delete s;
		}
	}//else if (D->lchild && D->rchild)
	else if ((D->lchild && !D->rchild) || (!D->lchild && D->rchild) || (!D->lchild && !D->rchild)) {//只有一个孩子结点或者没有孩子结点
		BTree* p = D;//暂存D
		if (D->lchild) {	//D左子树不为空
			D = D->lchild;
		}
		else if (D->rchild) {	//D右子树不为空
			D = D->rchild;
		}
		if (!f) {	//删除结点为根结点
			T = D;
		}
		else {
			if (f->lchild == p) {	//要删除的结点时左孩子，则接上删除结点的孩子
				f->lchild = D;
			}
			else if (f->rchild == p) {
				f->rchild = D;
			}

		}
		delete p;//删除刚才暂存的D

	}//else if ((D->lchild && !D->rchild) || (!D->lchild && D->rchild))
}


//回收动态内存
void DeleteTree(BTree*& T)
{
	if (T) {
		DeleteTree(T->lchild);
		DeleteTree(T->rchild);
		cout << "删除" << T->key << "结点" << endl;
		delete T;
	}
}
//先序遍历
void PreOrderTraverse(BTree* T)
{
	if (T) {
		cout << T->key << " ";
		if (T->lchild || T->rchild)
			cout << "(";
		PreOrderTraverse(T->lchild);
		if (T->lchild || T->rchild)
			cout << ",";
		PreOrderTraverse(T->rchild);
		if (T->lchild || T->rchild)
			cout << ")";
	}
}
//中序遍历
void InOrderTraverse(BTree* T)
{
	if (T) {
		InOrderTraverse(T->lchild);
		cout << T->key << " ";
		InOrderTraverse(T->rchild);
	}
}



/*--------------------------------------------二叉查找树-----------------------------------------------------*/




int main()
{

	//char ar[Size];
	//getVaule(ar);
	//display(ar);
	//char ch;
	//cout << "请输入查找的字母\n";
	//cin >> ch;
	//int re = 0;//结果
	//if (!(re = searchSe(ar, ch))) {
	//	cout << "数组中没有" << ch << "元素" << endl;
	//}
	//else {
	//	cout << ch << "元素在 " << re << " 位置" << endl;
	//}
	//cout << "请输入查找的字母\n";
	//cin >> ch;
	//if (!(re = searchSe(ar, ch))) {
	//	cout << "数组中没有" << ch << "元素" << endl;
	//}
	//else {
	//	cout << ch << "元素在 " << re << " 位置" << endl;
	//}



	int array[iMax];
	init(array);
	display(array);
	deBubbleSort(array);
	cout << "数组排序后" << endl;
	display(array);
	int f = 0, result = 0;
	cout << "请输入要找到的数据：\n";
	cin >> f;
	if (!(result = BiSearch(array, f))) {
		cout << "数组中没有" << f << "元素" << endl;
	}
	else {
		cout << f << "元素在 " << result << " 位置" << endl;
	}
	cout << "折半查找比较次数为" << cmp_BS << endl;
	cmp_BS = 0;//置空方便后面调用
	cout << "请输入要找到的数据：\n";
	cin >> f;
	if (!(result = BiSearch(array, f))) {
		cout << "数组中没有" << f << "元素" << endl;
	}
	else {
		cout << f << "元素在 " << result << " 位置" << endl;
	}
	cout << "折半查找比较次数为" << cmp_BS << endl;
	cmp_BS = 0;//置空方便后面调用
	/*BTree* head = nullptr;
	createTree(head);
	PreOrderTraverse(head);
	cout << endl;
	InOrderTraverse(head);
	cout << endl;
	char ch;
	cout << "输入要查找的字母\n";
	cin >> ch;
	if (BiTreeSearch(head, ch)) {
		cout << "查找成功\n";
	}
	else {
		cout << "查找失败\n";
	}
	cout << "二叉查找树的比较次数为：" << cmp_T++ << endl;
	cmp_T = 0;//置空方便后面调用
	cout << "输入要查找的字母\n";
	cin >> ch;
	if (BiTreeSearch(head, ch)) {
		cout << "查找成功\n";
	}
	else {
		cout << "查找失败\n";
	}
	cout << "二叉查找树的比较次数为：" << cmp_T++ << endl;
	cmp_T = 0;//置空方便后面调用
	DeleteTree(head);*/
}



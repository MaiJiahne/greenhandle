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

/*--------------------------------------------˳�����-----------------------------------------------------*/
#define Size 17 //�����С��0���������

//��ʼ������
void getVaule(char(&ch)[Size])
{
	ch[0] = ' ';
	vector<int> ivec;//�������ɲ��ظ������
	for (int i = 0; i < 26; i++) {	//�� 0~26 ���������У��ٴ��ң��γɲ��ظ���
		ivec.push_back(i);
	}
	std::random_shuffle(ivec.begin(), ivec.end());//��������
	for (int i = 1; i < Size; i++)
	{
		ch[i] = ivec[i] + 97;//����97�γ�a~z ��ASCII
	}
}
//�������
void display(char(&ch)[Size])
{
	cout << "����Ϊ��";
	for (int i = 1; i < Size; i++)
	{
		cout << ch[i] << "  ";
	}
	cout << endl;
}
//˳�����
int searchSe(char* ar, char ch)
{
	int cmp = 0;//�Ƚϴ���
	ar[0] = ch;//���ҵ���ĸ�ȴ����ar[0]��
	int i = Size - 1;
	cmp++;//�Ƚϴ���++
	for (i; ar[i] != ar[0]; i--, cmp++);	//����ҵ�����λ�ã�û�з���0
	cout << "�Ƚϴ���Ϊ" << cmp << endl;
	return i;
}
/*--------------------------------------------˳�����-----------------------------------------------------*/

/*--------------------------------------------�۰����-----------------------------------------------------*/
#define iMax 16		//�����С

//��ʼ������
void init(int* ar)
{
	srand(int(time(0)));
	ar[0] = 32767;//ar[0]���������
	for (int i = 1; i < iMax; i++)
	{
		ar[i] = rand() % 1000;	//���� 0~999 ����
	}
}
//�������
void display(int* ar)
{
	cout << "����Ϊ��";
	for (int i = 1; i < iMax; i++)
	{
		cout << ar[i] << "  ";
	}
	cout << endl;
}
//����˫��ð������
void deBubbleSort(int(&ar)[iMax])
{
	bool exchange = true;//�Ƿ�������
	int head = 0;	//δ��������������ʼ
	int tail = sizeof(ar) / sizeof(ar[0]); ////δ�����������Ľ�β
	int i = head + 1;	//���ڱȽϽ���
	int time = 0;//��¼�ڼ�������
	while (exchange) {
		exchange = false;
		while (i + 1 < tail) {	//��ǰ����ð��
			if (ar[i] > ar[i + 1]) {
				int temp = ar[i];		//����ar[i] �� ar[i + 1]
				ar[i] = ar[i + 1];
				ar[i + 1] = temp;
				exchange = true;//��������
			}
			i++;
		}//while (i + 1 <= tail)
		tail = i + 1;	//���½�β
		while (exchange && i - 1 > head) {	//�Ӻ���ǰð��
			if (ar[i] < ar[i - 1]) {
				int temp = ar[i];		//����ar[i] �� ar[i - 1]
				ar[i] = ar[i - 1];
				ar[i - 1] = temp;
				exchange = true;//��������
			}
			i--;
		}//while (exchange && i - 1 > head)
		head = i - 1;
	}//while (exchange)
}
int cmp_BS;//�Ƚϴ���
//�۰����
int BiSearch(int* ar, int n)
{
	int low = 1, high = iMax - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		cmp_BS++;//�Ƚϴ���++
		if (ar[mid] == n)	return mid;
		else if (ar[mid] < n)	low = mid + 1;
		else	high = mid - 1;
	}
	return 0;
}


/*--------------------------------------------�۰����-----------------------------------------------------*/

/*--------------------------------------------���������-----------------------------------------------------*/
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
int cmp_T;//������ұȽϴ���
//�����½�㵽����������
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
//��������������
void createTree(BTree*& T)
{
	char ch;
	while (true)
	{
		cout << "��������ĸ������'#'�����ս��\n";
		cin >> ch;
		if (ch == '#') break;
		insertTree(T, ch);
	}
}
//����������
bool BiTreeSearch(BTree* T, char ch)
{
	if (!T) {
		cout << "��Ϊ�գ�û�бȽ�" << endl;
		return false;
	}
	else {
		cmp_T++;//�Ƚϴ���++
		if (T->key == ch) {
			return true;
		}
		else if (ch < T->key)	return BiTreeSearch(T->lchild, ch);
		else return BiTreeSearch(T->rchild, ch);
		return false;
	}

}
//�Ӷ���������ɾ�����
void deleteTreeNode(BTree*& T, char ch)
{
	if (!BiTreeSearch(T, ch))
	{
		cout << "����û��" << ch << "���\n";
		return;
	}
	BTree* D = T;
	BTree* f = nullptr;	//ָ��D�ĸ�ĸ���
	while (D->key != ch) {
		f = D;	//pָ�����ĸ�ĸ���
		if (ch < D->key) {	//���������ң�

			D = D->lchild;
		}
		else {//����������
			D = D->lchild;
		}
	}
	if (D->lchild && D->rchild) {	//���������������Ϊ��
		BTree* s = D->lchild;//ָ���DС������ӽ�D�Ľ��
		BTree* q = nullptr;	//ָ��s�ĸ�ĸ���
		while (s->rchild) {	//���ҵ�s�����µĵ�
			q = s;
			s = s->rchild;
		}
		D->key = s->key;//�滻��Ҫɾ���Ľ��
		if (!q) {//��DС������ӽ�D�Ľ��ֱ����D������
			D->lchild = s->lchild;	//s��������
			delete s;
		}
		else {
			q->rchild = s->lchild;//s�ĸ�ĸ���ԭ��ָ��s�ĺ���ָ��ָ��s��������
			delete s;
		}
	}//else if (D->lchild && D->rchild)
	else if ((D->lchild && !D->rchild) || (!D->lchild && D->rchild) || (!D->lchild && !D->rchild)) {//ֻ��һ�����ӽ�����û�к��ӽ��
		BTree* p = D;//�ݴ�D
		if (D->lchild) {	//D��������Ϊ��
			D = D->lchild;
		}
		else if (D->rchild) {	//D��������Ϊ��
			D = D->rchild;
		}
		if (!f) {	//ɾ�����Ϊ�����
			T = D;
		}
		else {
			if (f->lchild == p) {	//Ҫɾ���Ľ��ʱ���ӣ������ɾ�����ĺ���
				f->lchild = D;
			}
			else if (f->rchild == p) {
				f->rchild = D;
			}

		}
		delete p;//ɾ���ղ��ݴ��D

	}//else if ((D->lchild && !D->rchild) || (!D->lchild && D->rchild))
}


//���ն�̬�ڴ�
void DeleteTree(BTree*& T)
{
	if (T) {
		DeleteTree(T->lchild);
		DeleteTree(T->rchild);
		cout << "ɾ��" << T->key << "���" << endl;
		delete T;
	}
}
//�������
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
//�������
void InOrderTraverse(BTree* T)
{
	if (T) {
		InOrderTraverse(T->lchild);
		cout << T->key << " ";
		InOrderTraverse(T->rchild);
	}
}



/*--------------------------------------------���������-----------------------------------------------------*/




int main()
{

	//char ar[Size];
	//getVaule(ar);
	//display(ar);
	//char ch;
	//cout << "��������ҵ���ĸ\n";
	//cin >> ch;
	//int re = 0;//���
	//if (!(re = searchSe(ar, ch))) {
	//	cout << "������û��" << ch << "Ԫ��" << endl;
	//}
	//else {
	//	cout << ch << "Ԫ���� " << re << " λ��" << endl;
	//}
	//cout << "��������ҵ���ĸ\n";
	//cin >> ch;
	//if (!(re = searchSe(ar, ch))) {
	//	cout << "������û��" << ch << "Ԫ��" << endl;
	//}
	//else {
	//	cout << ch << "Ԫ���� " << re << " λ��" << endl;
	//}



	int array[iMax];
	init(array);
	display(array);
	deBubbleSort(array);
	cout << "���������" << endl;
	display(array);
	int f = 0, result = 0;
	cout << "������Ҫ�ҵ������ݣ�\n";
	cin >> f;
	if (!(result = BiSearch(array, f))) {
		cout << "������û��" << f << "Ԫ��" << endl;
	}
	else {
		cout << f << "Ԫ���� " << result << " λ��" << endl;
	}
	cout << "�۰���ұȽϴ���Ϊ" << cmp_BS << endl;
	cmp_BS = 0;//�ÿշ���������
	cout << "������Ҫ�ҵ������ݣ�\n";
	cin >> f;
	if (!(result = BiSearch(array, f))) {
		cout << "������û��" << f << "Ԫ��" << endl;
	}
	else {
		cout << f << "Ԫ���� " << result << " λ��" << endl;
	}
	cout << "�۰���ұȽϴ���Ϊ" << cmp_BS << endl;
	cmp_BS = 0;//�ÿշ���������
	/*BTree* head = nullptr;
	createTree(head);
	PreOrderTraverse(head);
	cout << endl;
	InOrderTraverse(head);
	cout << endl;
	char ch;
	cout << "����Ҫ���ҵ���ĸ\n";
	cin >> ch;
	if (BiTreeSearch(head, ch)) {
		cout << "���ҳɹ�\n";
	}
	else {
		cout << "����ʧ��\n";
	}
	cout << "����������ıȽϴ���Ϊ��" << cmp_T++ << endl;
	cmp_T = 0;//�ÿշ���������
	cout << "����Ҫ���ҵ���ĸ\n";
	cin >> ch;
	if (BiTreeSearch(head, ch)) {
		cout << "���ҳɹ�\n";
	}
	else {
		cout << "����ʧ��\n";
	}
	cout << "����������ıȽϴ���Ϊ��" << cmp_T++ << endl;
	cmp_T = 0;//�ÿշ���������
	DeleteTree(head);*/
}



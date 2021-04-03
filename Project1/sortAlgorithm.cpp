#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::setiosflags;
using std::setw;
using std::ios;

//��С����Ϊ��
#define size 17		//�����С	
typedef int sortType;//���������

sortType ar[size];	//˳�������ݣ�ar[0]��Ϊ�ڱ���

//�����ɵ�16���������������
void getValue(sortType(&ar)[size])
{
	srand(int(time(0)));
	ar[0] = -32767;
	for (int i = 1; i < size; i++) {
		ar[i] = rand() % 90 + 10;	//����2λ������
	}
}

//�������
void display(sortType(&ar)[size])
{
	cout << "����������Ϊ:";
	for (int i = 1; i < size; i++) {
		cout << ar[i] << " ";
	}
	cout << endl;
}

//�򵥲�������
void insertSort(sortType(&ar)[size])
{
	int move = 0, cmp = 0;	//�ƶ��ͱȽϴ���
	for (int i = 2; i < size; i++) {
		cout << "��" << setw(2) << setiosflags(ios::left) << i - 1 << "������ǰ";	//�����һ������ǰ������
		for (int k = 1; k <= i; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		ar[0] = ar[i];	//ar[0]��Ϊ�ڱ���
		cmp++;//�Ƚϴ���,ar[0] �� ar[i-1]��
		if (ar[0] < ar[i - 1]) {	//�������С��֮ǰ�����ݣ���ôǰ������ƶ��ڳ�λ�ò���
			ar[i] = ar[i - 1];
			move++;	//�ƶ�����
			for (int j = i - 1; j >= 1; j--) {
				if (ar[0] < ar[j - 1]) {
					ar[j] = ar[j - 1];
					move++;//�ƶ�����
					cmp++;//�Ƚϴ���
				}
				else
				{
					ar[j] = ar[0];
					break;
				}
			}
		}//if (ar[0] < ar[i - 1])
		cout << "��" << setw(2) << setiosflags(ios::left) << i - 1 << "�������";//�����һ������������
		for (int k = 1; k <= i; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}//for(i)
	cout << "�򵥲�������  �ƶ�������" << move << "  �Ƚϴ���" << cmp << endl;
}

//�۰��������
void midInsSort(sortType(&ar)[size])
{
	int move = 0, cmp = 0;//�ƶ��ͱȽϴ���
	for (int i = 2; i < size; i++) {
		cout << "��" << setw(2) << setiosflags(ios::left) << i - 1 << "������ǰ";	//�����һ������ǰ������
		for (int k = 1; k <= i; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		ar[0] = ar[i];
		if (ar[0] < ar[i - 1]) {
			int low = 1, high = i - 1;
			cmp++;//�Ƚϴ���
			while (low <= high) {	//low<=highʱѭ������
				int mid = (low + high) / 2;
				if (ar[mid] > ar[0])	high = mid - 1;	//������ = ���԰Ѳ���̶���high+1��
				else	low = mid + 1;

				cmp++;
			}
			for (int j = i; j > high + 1; j--) {	//�����ƶ�
				ar[j] = ar[j - 1];
				move++;
			}
			ar[high + 1] = ar[0];
		}//if

		cout << "��" << setw(2) << setiosflags(ios::left) << i - 1 << "�������";//�����һ������������
		for (int k = 1; k <= i; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}//for(i)

	cout << "�۰��������  �ƶ�������" << move << "  �Ƚϴ���" << cmp << endl;
}

//ϣ������
void shellSort(sortType(&ar)[size])
{
	//��ȡHibbard��������
	int num = sizeof(ar) / sizeof(ar[0]) - 1;//��ȡ�����С����Ϊar[0]��������ݣ�����-1
	int HibbardSize = log(num) / log(2);//��ȡHibbard�������д�С  ������������Ϊ 15 7 3 1
	int move = 0, cmp = 0;//�ƶ��ͱȽϴ���
	for (int i = HibbardSize; i >= 1; i--) {	//ִ���������д�С��
		int gap = pow(2, i) - 1;	//ÿһ����������
		cout << "����" << setw(2) << setiosflags(ios::left) << gap << "������������ǰ";	//�����������������ǰ������
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		for (int j = 1 + gap; j <= num; j++) {
			cmp++;//�Ƚϴ���
			if (ar[j] < ar[j - gap]) {
				ar[0] = ar[j];
				ar[j] = ar[j - gap];
				move++;//�ƶ�����
				for (int k = j - gap; k >= 1; k -= gap) {
					cmp++;//�Ƚϴ���
					if (ar[k - gap] <= ar[0]) {	//����ҵ�����λ�ã�����ѭ��ֹͣ
						ar[k] = ar[0];
						break;
					}
					move++;//�ƶ�����
					ar[k] = ar[k - gap];	//�����ƶ����ڳ�λ��
				}//for(k)

			}

		}//for(j)
		cout << "����" << setw(2) << setiosflags(ios::left) << gap << "�������������";	//�����������������������
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}//for(i)


	cout << "ϣ������  �ƶ�������" << move << "  �Ƚϴ���" << cmp << endl;
}

//ð������
void bubbleSort(sortType(&ar)[size])
{
	int move = 0, cmp = 0;	//�ƶ��ͱȽϴ���
	bool exchange = true;	//�ж��Ƿ��н���
	int temp;	//��ʱ����
	for (int i = 1; i < size - 1 && exchange; i++) {	//ѭ�������С-1�Σ�����ar[0]���������
		cout << "��" << setw(2) << setiosflags(ios::left) << i << "������ǰ";	//�����һ������ǰ������
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		exchange = false;
		for (int j = 1; j <= size - i - 1; j++) {
			cmp++;
			if (ar[j] > ar[j + 1]) {
				temp = ar[j];	//���ar[j]С��ar[j+1]���򽻻�
				ar[j] = ar[j + 1];
				ar[j + 1] = temp;
				exchange = true;
				move++;//�ƶ�����++
			}
		}//for(j)
		if (exchange) {
			cout << "��" << setw(2) << setiosflags(ios::left) << i << "�������";//�����һ������������
			for (int k = 1; k < size; k++) {
				cout << ar[k] << "  ";
			}
		}
		else {
			cout << "�����ѽ���";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}//for(i)

	cout << "ð������  �ƶ�������" << move << "  �Ƚϴ���" << cmp << endl;
}

//˫��ð������
void deBubbleSort(sortType(&ar)[size])
{
	int move = 0, cmp = 0;	//�ƶ��ͱȽϴ���
	bool exchange = true;//�Ƿ�������
	int head = 0;	//δ��������������ʼ
	int tail = sizeof(ar) / sizeof(ar[0]); ////δ�����������Ľ�β,���⿪ʼΪ17
	int i = 1;	//���ڱȽϽ���
	int time = 0;//��¼�ڼ�������
	while (exchange) {
		exchange = false;
		time++;
		cout << "��" << setw(2) << setiosflags(ios::left) << time << "������ǰ";	//�����һ������ǰ������
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		while (i + 1 < tail) {	//��ǰ����ð��
			cmp++;//�Ƚϴ���++
			if (ar[i] > ar[i + 1]) {
				int temp = ar[i];		//����ar[i] �� ar[i + 1]
				ar[i] = ar[i + 1];
				ar[i + 1] = temp;
				exchange = true;//��������
				move++;//�ƶ�����++
			}
			i++;
		}//while (i + 1 <= tail)
		tail = i + 1;	//���½�β
		while (exchange && i - 1 > head) {	//�Ӻ���ǰð��
			cmp++;//�Ƚϴ���++
			if (ar[i] < ar[i - 1]) {
				int temp = ar[i];		//����ar[i] �� ar[i - 1]
				ar[i] = ar[i - 1];
				ar[i - 1] = temp;
				exchange = true;//��������
				move++;//�ƶ�����++
			}
			i--;
		}//while (exchange && i - 1 > head)
		head = i - 1;

		if (exchange) {
			cout << "��" << setw(2) << setiosflags(ios::left) << time << "�������";//�����һ������������
			for (int k = 1; k < size; k++) {
				cout << ar[k] << "  ";
			}
		}
		else {
			cout << "�����ѽ���";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";

	}//while (exchange)

	cout << "˫��ð������  �ƶ�������" << move << "  �Ƚϴ���" << cmp << endl;
}

//���������㷨
int move_qs, cmp_qs;//�������������ƶ��ͱȽϴ���
int quickSort(sortType(&ar)[size], int low, int high) {

	ar[0] = ar[low];	//��ar[low]��Ϊ����
	while (low < high) {
		if (ar[high] < ar[0])	cmp_qs++;//�Ƚϴ���++�������һ���ͷ��ϣ��������ѭ��������+1
		while ((low < high) && ar[high] >= ar[0]) {	//���ұ��ҵ���һ��С��ar[0]����
			high--;
			cmp_qs++;//�Ƚϴ���++
		}
		cmp_qs++;//�Ƚϴ���++�������ֹѭ��û��1
		if (low != high) {
			ar[low] = ar[high];
			move_qs++;//�ƶ�����++
		}
		if (ar[low] > ar[0])	cmp_qs++;//�Ƚϴ���++�������һ���ͷ��ϣ��������ѭ��������+1
		while ((low < high) && ar[low] <= ar[0]) {	//������ҵ���һ������ar[0]����
			low++;
			cmp_qs++;//�Ƚϴ���++
		}
		cmp_qs++;//�Ƚϴ���++�������ֹѭ��û��1
		if (low != high) {
			ar[high] = ar[low];
			move_qs++;//�ƶ�����++
		}


	}//while (low < high)
	//���ѭ��������low = high
	ar[low] = ar[0]; //����ֵ��������
	return low;

}

void QuickSort(sortType(&ar)[size], int low, int high)
{
	if (low < high) {	//�ݹ���ֹ����Ϊ low = high	(if(low != higj)��������ܳ���low>high���)
		cout << "��" << low << "��" << high << "��һ���ֿ�������ǰΪ��";	//������ֶε��������
		for (int k = low; k <= high; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		int pivotloc = quickSort(ar, low, high);	//�������Ϊ�ܶ��ȥ�ݹ���ÿ�������
		cout << "��" << low << "��" << high << "��һ���ֿ��������Ϊ��";	//������ֶε��������
		for (int k = low; k <= high; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
		QuickSort(ar, low, pivotloc - 1);
		QuickSort(ar, pivotloc + 1, high);
	}
}

//��ѡ������
void chooseSort(sortType(&ar)[size])
{
	int move = 0, cmp = 0;	//�ƶ��ͱȽϴ���
	for (int i = 1; i < size - 1; i++) {
		int t = i;
		cout << "��" << setw(2) << setiosflags(ios::left) << i << "������ǰ  ";	//�����һ������ǰ������
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		for (int j = i + 1; j <= size - 1; j++) {
			cmp++;//�Ƚϴ���++
			if (ar[j] < ar[t]) {
				t = j;	//ѡ����С�����t
			}

		}
		if (i != t) {	//������ϣ�����
			int temp = ar[i];
			ar[i] = ar[t];
			ar[t] = temp;
			move++;//�ƶ�����++
		}
		cout << "��" << setw(2) << setiosflags(ios::left) << i << "�������  ";//�����һ������������
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}//for(i)

	cout << "��ѡ������  �ƶ�������" << move << "  �Ƚϴ���" << cmp << endl;
}

//--------------------------������-----------------------------------------------
int move_heap, cmp_heap;//�ƶ��ͱȽϴ���
//�����ѣ�ֻ�и�����п��ܲ�����
void heapAdjust(sortType(&ar)[size], int n, int e)
{
	int root = n;//���ø����Ϊar[n]
	ar[0] = ar[root];
	for (int s = root * 2; s <= e; s *= 2) {	//���ֱ�����������Ƚ�
		cmp_heap++;//�Ƚϴ���++
		if ((s + 1 <= e) && ar[s] < ar[s + 1]) {
			s++;	//�������������������
		}
		cmp_heap++;//�Ƚϴ���++
		if (ar[s] > ar[0]) {//�������ڸ�
			ar[root] = ar[s];
			move_heap++;//�ƶ�����++
			root = s;	//�����������µ���
		}
		else {	//�������С�ڸ������ѭ��	

			break;
		}
	}//for(s)
	ar[root] = ar[0];

}
//������
void createHeap(sortType(&ar)[size])
{	//��logN��2Ϊ������ȡ�����濪ʼ��ΪҶ�ӽ�㣬�ӷ�Ҷ�����һ����ǰһ�ε�����
	for (int i = (size - 1) / 2; i >= 1; i--) {//log(size - 1) / log(2)
		heapAdjust(ar, i, size - 1);
	}
}

//������
void heapSort(sortType(&ar)[size])
{
	createHeap(ar);//�ȴ�����
	for (int i = size - 1; i > 1; i--) {//�������ηŵ�������棬�γ�����
		cout << "��ar[" << i << "]���ݣ�����ǰ  ";	//�����һ������ǰ������
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		int temp = ar[i];
		ar[i] = ar[1];
		ar[1] = temp;
		heapAdjust(ar, 1, i - 1);
		move_heap++;//�ƶ�����++

		cout << "��ar[" << i << "]���ݣ������  ";	//�����һ������ǰ������
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}

	cout << "������  �ƶ�������" << move_heap << "  �Ƚϴ���" << cmp_heap << endl;
}

//�鲢����
//�������Ϊ����һ����й鲢������
int move_merge = 0, cmp_merge = 0;	//�ƶ��ͱȽϴ���
void mergeSort(sortType S[size], sortType T[size], int low, int high)
{
	if (low < high) {

		int mid = (low + high) / 2;
		mergeSort(S, T, low, mid);//�ݹ�ֳ���С������һ��
		mergeSort(S, T, mid + 1, high);
		cout << "��" << setw(2) << setiosflags(ios::left) << low << "��" <<
			setw(2) << setiosflags(ios::left) << high << "��һ���ֹ鲢����ǰΪ��";//������ֶε��������
		for (int k = low; k <= high; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		int beg1 = low, beg2 = mid + 1;//S���������ֵĿ�ʼ
		int k = low;//T����Ŀ�ʼ��T�����Ǹ�������
		//S����������С���Ƚ���T
		while ((beg1 <= mid) && (beg2 <= high)) {
			cmp_merge++;//�Ƚϴ���++
			if (S[beg1] <= S[beg2]) {
				T[k++] = S[beg1++];
				move_merge++;//�ƶ�����++
			}
			else {
				T[k++] = S[beg2++];
				move_merge++;//�ƶ�����++
			}
		}
		//ѭ����������һ�����Ƚ�����û�����ǲ���ȫ������T
		while (beg1 <= mid)
		{
			T[k++] = S[beg1++];
			move_merge++;//�ƶ�����++
		}
		while (beg2 <= high)
		{
			T[k++] = S[beg2++];
			move_merge++;//�ƶ�����++
		}
		//���ź������¸�������
		for (int i = low; i <= high; i++) {
			S[i] = T[i];
			move_merge++;//�ƶ�����++
		}
		cout << "��" << setw(2) << setiosflags(ios::left) << low << "��"
			<< setw(2) << setiosflags(ios::left) << high << "��һ���ֹ鲢�����Ϊ��";	//������ֶε��������
		for (int k = low; k <= high; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}
}
//�鲢����
void MergeSort(sortType(&ar)[size])
{
	//�����ռ�����
	sortType R[size] = { 0 };
	mergeSort(ar, R, 1, size - 1);
	cout << "�鲢����  �ƶ�������" << move_merge << "  �Ƚϴ���" << cmp_merge << endl;
}

//--------------------------��������-----------------------------------------------

//���þ�̬����
#define key_num 17		//���������С��0���������
#define radix_num 10	//ÿһ������������
#define radixMax 5	//��������λ���������ʮ��ǧ�򡤡���
#define radixSortNum 2	//����Ŀֻ�и���ʮλ

struct RadixType
{
	int key;
	char radix[radixMax];//����������radix[0]Ϊ��λ��ar[1]Ϊʮλ�������ֱ���A B C��������
	int next;//��̬������¸����
};

RadixType array[key_num];	//�����������
typedef int List[radix_num];
List first, end;	//�����ݰ�ĳһ�������䣬first �� end �ֱ�ָ����һ��������������յ�

//��ʼ�������������
void getValue_rSort(RadixType(&ar)[key_num])
{
	srand(int(time(0)));
	ar[0].key = -32767;
	ar[0].next = 1;
	for (int i = 1; i < key_num; i++) {
		ar[i].key = rand() % 90 + 10;	//����2λ������
		ar[i].next = i + 1;
		for (int k = 0; k < radixMax; k++) {
				ar[i].radix[k] = 65 + k;
		}
	}
	ar[key_num - 1].next = 0;//���һλָ����
}

//�������
void display_rSort(RadixType(&ar)[key_num])
{
	cout << "����Ϊ��";
	for (int i = ar[0].next; i; i = ar[i].next)
	{
		cout << ar[i].key << " ";
	}
	cout << endl;
}

//���keyӦ�÷������飬�����λ��77����ar[7]
int posRadix(int key, char ch)
{
	switch (ch)
	{
	case 'A':	//�����λ
		return key % 10;
		break;
	case 'B':	//����ʮλ
		return key / 10;
		break;
	case 'C':	//����ʮλ
		return key / 100;
		break;
	case 'D':	//����ʮλ
		return key / 1000;
		break;
	case 'E':	//����ʮλ
		return key / 10000;
		break;
	default:
		break;
	}
}
//����
void contribute(RadixType (&array)[key_num], List f, List e, int radixNum)
{
	for (int p = array[0].next; p != 0; p = array[p].next)
	{
		int pos = posRadix(array[p].key, array[p].radix[radixNum]);//����������Ӧ�����ĸ�����
		if (f[pos] == 0) {									//������Ǹ�λ����ô��λΪ8�ͷ���f[8]��e[0]���У�
			f[pos] = p;
		}
		else {
			array[e[pos]].next = p;			//�½���Ĳ����β
		}
		e[pos] = p;
	}
}
//�ռ�
void collect(RadixType(&ar)[key_num], List f, List e)
{
	bool ar0 = false;	//�ж��Ƿ�ar[0].next�Ѿ�����ֵ
	int t = 0;	//��¼ÿ��λ�����һ���������Ӻ����λ
	for (int i = 0; i < radix_num; i++) {
		if (f[i]) {		//ar[0].next��û��ֵ
			if (!ar0) {
				ar[0].next = f[i];
				t = e[i];
				ar0 = true;
			}
			else {	//ÿ�����յ�������
				ar[t].next = f[i];
				t = e[i];
			}
		}
	}
	ar[t].next = 0;//�������ar[0]
	for (int j = 0; j < radix_num; j++) {	//��first��end��λ
		first[j] = 0;
		end[j] = 0;
	}

}
//��������
void radixSort(RadixType(&ar)[key_num])
{
	for (int i = 0; i < radixSortNum; i++) {
		contribute(ar, first, end, i);
		collect(ar, first, end);
		cout << "��" << i + 1 << "�˷����ռ�����Ϊ��\n";
		display_rSort(ar);
	}
}


//--------------------------��������-----------------------------------------------

int main()
{
	getValue(ar);
	display(ar);
	cout << "--------------------------------------------------------------------------------------\n";
	/*insertSort(ar);
	display(ar);
	midInsSort(ar);
	display(ar);
	shellSort(ar);
	display(ar);
	bubbleSort(ar);
	display(ar);
	deBubbleSort(ar);
	display(ar);
	QuickSort(ar, 1, size - 1);
	display(ar);
	cout << "��������  �ƶ�������" << move_qs << "  �Ƚϴ���" << cmp_qs << endl;
	move_qs = 0, cmp_qs = 0;//��0�����������ʹ��
	chooseSort(ar);
	display(ar);
	heapSort(ar);
	move_heap = 0, cmp_heap = 0;//��0�����������ʹ��
	display(ar);
	MergeSort(ar);
	move_merge = 0, cmp_merge = 0;//��0�����������ʹ��
	display(ar);*/
	/*getValue_rSort(array);
	cout << "��������ǰ  \n";
	display_rSort(array);
	radixSort(array);
	cout << "��������ǰ  \n";
	display_rSort(array);*/

}
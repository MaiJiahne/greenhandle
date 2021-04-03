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

//从小到大为序
#define size 17		//数组大小	
typedef int sortType;//分类的类型

sortType ar[size];	//顺序存放数据，ar[0]做为哨兵点

//将生成的16个随机数存入数组
void getValue(sortType(&ar)[size])
{
	srand(int(time(0)));
	ar[0] = -32767;
	for (int i = 1; i < size; i++) {
		ar[i] = rand() % 90 + 10;	//生成2位正整数
	}
}

//输出数据
void display(sortType(&ar)[size])
{
	cout << "此数组数据为:";
	for (int i = 1; i < size; i++) {
		cout << ar[i] << " ";
	}
	cout << endl;
}

//简单插入排序
void insertSort(sortType(&ar)[size])
{
	int move = 0, cmp = 0;	//移动和比较次数
	for (int i = 2; i < size; i++) {
		cout << "第" << setw(2) << setiosflags(ios::left) << i - 1 << "趟排序前";	//输出这一趟排序前的序列
		for (int k = 1; k <= i; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		ar[0] = ar[i];	//ar[0]做为哨兵点
		cmp++;//比较次数,ar[0] 和 ar[i-1]比
		if (ar[0] < ar[i - 1]) {	//如果插入小于之前的数据，那么前面向后移动腾出位置插入
			ar[i] = ar[i - 1];
			move++;	//移动次数
			for (int j = i - 1; j >= 1; j--) {
				if (ar[0] < ar[j - 1]) {
					ar[j] = ar[j - 1];
					move++;//移动次数
					cmp++;//比较次数
				}
				else
				{
					ar[j] = ar[0];
					break;
				}
			}
		}//if (ar[0] < ar[i - 1])
		cout << "第" << setw(2) << setiosflags(ios::left) << i - 1 << "趟排序后";//输出这一趟排序后的序列
		for (int k = 1; k <= i; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}//for(i)
	cout << "简单插入排序  移动次数：" << move << "  比较次数" << cmp << endl;
}

//折半插入排序
void midInsSort(sortType(&ar)[size])
{
	int move = 0, cmp = 0;//移动和比较次数
	for (int i = 2; i < size; i++) {
		cout << "第" << setw(2) << setiosflags(ios::left) << i - 1 << "趟排序前";	//输出这一趟排序前的序列
		for (int k = 1; k <= i; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		ar[0] = ar[i];
		if (ar[0] < ar[i - 1]) {
			int low = 1, high = i - 1;
			cmp++;//比较次数
			while (low <= high) {	//low<=high时循环继续
				int mid = (low + high) / 2;
				if (ar[mid] > ar[0])	high = mid - 1;	//不含有 = 可以把插入固定在high+1处
				else	low = mid + 1;

				cmp++;
			}
			for (int j = i; j > high + 1; j--) {	//往后移动
				ar[j] = ar[j - 1];
				move++;
			}
			ar[high + 1] = ar[0];
		}//if

		cout << "第" << setw(2) << setiosflags(ios::left) << i - 1 << "趟排序后";//输出这一趟排序后的序列
		for (int k = 1; k <= i; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}//for(i)

	cout << "折半插入排序  移动次数：" << move << "  比较次数" << cmp << endl;
}

//希尔排序
void shellSort(sortType(&ar)[size])
{
	//获取Hibbard增量序列
	int num = sizeof(ar) / sizeof(ar[0]) - 1;//获取数组大小，因为ar[0]不存放数据，所以-1
	int HibbardSize = log(num) / log(2);//获取Hibbard增量序列大小  本题增量序列为 15 7 3 1
	int move = 0, cmp = 0;//移动和比较次数
	for (int i = HibbardSize; i >= 1; i--) {	//执行增量序列大小次
		int gap = pow(2, i) - 1;	//每一个增量序列
		cout << "经过" << setw(2) << setiosflags(ios::left) << gap << "增量序列排序前";	//输出这增利序列排序前的序列
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		for (int j = 1 + gap; j <= num; j++) {
			cmp++;//比较次数
			if (ar[j] < ar[j - gap]) {
				ar[0] = ar[j];
				ar[j] = ar[j - gap];
				move++;//移动次数
				for (int k = j - gap; k >= 1; k -= gap) {
					cmp++;//比较次数
					if (ar[k - gap] <= ar[0]) {	//如果找到插入位置，插入循环停止
						ar[k] = ar[0];
						break;
					}
					move++;//移动次数
					ar[k] = ar[k - gap];	//往后移动，腾出位置
				}//for(k)

			}

		}//for(j)
		cout << "经过" << setw(2) << setiosflags(ios::left) << gap << "增量序列排序后";	//输出这增利序列排序后的序列
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}//for(i)


	cout << "希尔排序  移动次数：" << move << "  比较次数" << cmp << endl;
}

//冒泡排序
void bubbleSort(sortType(&ar)[size])
{
	int move = 0, cmp = 0;	//移动和比较次数
	bool exchange = true;	//判断是否有交换
	int temp;	//临时变量
	for (int i = 1; i < size - 1 && exchange; i++) {	//循环数组大小-1次，数组ar[0]不存放数据
		cout << "第" << setw(2) << setiosflags(ios::left) << i << "趟排序前";	//输出这一趟排序前的序列
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		exchange = false;
		for (int j = 1; j <= size - i - 1; j++) {
			cmp++;
			if (ar[j] > ar[j + 1]) {
				temp = ar[j];	//如果ar[j]小于ar[j+1]，则交换
				ar[j] = ar[j + 1];
				ar[j + 1] = temp;
				exchange = true;
				move++;//移动次数++
			}
		}//for(j)
		if (exchange) {
			cout << "第" << setw(2) << setiosflags(ios::left) << i << "趟排序后";//输出这一趟排序后的序列
			for (int k = 1; k < size; k++) {
				cout << ar[k] << "  ";
			}
		}
		else {
			cout << "排序已结束";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}//for(i)

	cout << "冒泡排序  移动次数：" << move << "  比较次数" << cmp << endl;
}

//双向冒泡排序
void deBubbleSort(sortType(&ar)[size])
{
	int move = 0, cmp = 0;	//移动和比较次数
	bool exchange = true;//是否发生交换
	int head = 0;	//未完成排序数组的起始
	int tail = sizeof(ar) / sizeof(ar[0]); ////未完成排序数组的结尾,此题开始为17
	int i = 1;	//用于比较交换
	int time = 0;//记录第几趟排序
	while (exchange) {
		exchange = false;
		time++;
		cout << "第" << setw(2) << setiosflags(ios::left) << time << "趟排序前";	//输出这一趟排序前的序列
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		while (i + 1 < tail) {	//从前往后冒泡
			cmp++;//比较次数++
			if (ar[i] > ar[i + 1]) {
				int temp = ar[i];		//交换ar[i] 和 ar[i + 1]
				ar[i] = ar[i + 1];
				ar[i + 1] = temp;
				exchange = true;//发生交换
				move++;//移动次数++
			}
			i++;
		}//while (i + 1 <= tail)
		tail = i + 1;	//更新结尾
		while (exchange && i - 1 > head) {	//从后往前冒泡
			cmp++;//比较次数++
			if (ar[i] < ar[i - 1]) {
				int temp = ar[i];		//交换ar[i] 和 ar[i - 1]
				ar[i] = ar[i - 1];
				ar[i - 1] = temp;
				exchange = true;//发生交换
				move++;//移动次数++
			}
			i--;
		}//while (exchange && i - 1 > head)
		head = i - 1;

		if (exchange) {
			cout << "第" << setw(2) << setiosflags(ios::left) << time << "趟排序后";//输出这一趟排序后的序列
			for (int k = 1; k < size; k++) {
				cout << ar[k] << "  ";
			}
		}
		else {
			cout << "排序已结束";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";

	}//while (exchange)

	cout << "双向冒泡排序  移动次数：" << move << "  比较次数" << cmp << endl;
}

//快速排序算法
int move_qs, cmp_qs;//计算快速排序的移动和比较次数
int quickSort(sortType(&ar)[size], int low, int high) {

	ar[0] = ar[low];	//以ar[low]作为枢轴
	while (low < high) {
		if (ar[high] < ar[0])	cmp_qs++;//比较次数++，如果第一个就符合，不会进入循环，所以+1
		while ((low < high) && ar[high] >= ar[0]) {	//从右边找到第一个小于ar[0]的数
			high--;
			cmp_qs++;//比较次数++
		}
		cmp_qs++;//比较次数++，最后终止循环没加1
		if (low != high) {
			ar[low] = ar[high];
			move_qs++;//移动次数++
		}
		if (ar[low] > ar[0])	cmp_qs++;//比较次数++，如果第一个就符合，不会进入循环，所以+1
		while ((low < high) && ar[low] <= ar[0]) {	//从左边找到第一个大于ar[0]的数
			low++;
			cmp_qs++;//比较次数++
		}
		cmp_qs++;//比较次数++，最后终止循环没加1
		if (low != high) {
			ar[high] = ar[low];
			move_qs++;//移动次数++
		}


	}//while (low < high)
	//结点循环条件是low = high
	ar[low] = ar[0]; //枢轴值赋回数组
	return low;

}

void QuickSort(sortType(&ar)[size], int low, int high)
{
	if (low < high) {	//递归终止条件为 low = high	(if(low != higj)会出错，可能出现low>high情况)
		cout << "从" << low << "到" << high << "这一部分快速排序前为：";	//输出部分段的排序过程
		for (int k = low; k <= high; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		int pivotloc = quickSort(ar, low, high);	//将数组分为很多段去递归调用快速排序
		cout << "从" << low << "到" << high << "这一部分快速排序后为：";	//输出部分段的排序过程
		for (int k = low; k <= high; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
		QuickSort(ar, low, pivotloc - 1);
		QuickSort(ar, pivotloc + 1, high);
	}
}

//简单选择排序
void chooseSort(sortType(&ar)[size])
{
	int move = 0, cmp = 0;	//移动和比较次数
	for (int i = 1; i < size - 1; i++) {
		int t = i;
		cout << "第" << setw(2) << setiosflags(ios::left) << i << "趟排序前  ";	//输出这一趟排序前的序列
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		for (int j = i + 1; j <= size - 1; j++) {
			cmp++;//比较次数++
			if (ar[j] < ar[t]) {
				t = j;	//选出最小存放在t
			}

		}
		if (i != t) {	//如果符合，交换
			int temp = ar[i];
			ar[i] = ar[t];
			ar[t] = temp;
			move++;//移动次数++
		}
		cout << "第" << setw(2) << setiosflags(ios::left) << i << "趟排序后  ";//输出这一趟排序后的序列
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}//for(i)

	cout << "简单选择排序  移动次数：" << move << "  比较次数" << cmp << endl;
}

//--------------------------堆排序-----------------------------------------------
int move_heap, cmp_heap;//移动和比较次数
//调整堆，只有根结点有可能不符合
void heapAdjust(sortType(&ar)[size], int n, int e)
{
	int root = n;//设置根结点为ar[n]
	ar[0] = ar[root];
	for (int s = root * 2; s <= e; s *= 2) {	//根分别和左右子树比较
		cmp_heap++;//比较次数++
		if ((s + 1 <= e) && ar[s] < ar[s + 1]) {
			s++;	//如果右子树大于左子树
		}
		cmp_heap++;//比较次数++
		if (ar[s] > ar[0]) {//子树大于根
			ar[root] = ar[s];
			move_heap++;//移动次数++
			root = s;	//接着往子树下调整
		}
		else {	//如果子树小于根则结束循环	

			break;
		}
	}//for(s)
	ar[root] = ar[0];

}
//创建堆
void createHeap(sortType(&ar)[size])
{	//从logN以2为底向下取整后面开始都为叶子结点，从非叶子最后一个往前一次调整树
	for (int i = (size - 1) / 2; i >= 1; i--) {//log(size - 1) / log(2)
		heapAdjust(ar, i, size - 1);
	}
}

//堆排序
void heapSort(sortType(&ar)[size])
{
	createHeap(ar);//先创建堆
	for (int i = size - 1; i > 1; i--) {//最大的依次放到数组后面，形成排序
		cout << "排ar[" << i << "]数据，排序前  ";	//输出这一趟排序前的序列
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		int temp = ar[i];
		ar[i] = ar[1];
		ar[1] = temp;
		heapAdjust(ar, 1, i - 1);
		move_heap++;//移动次数++

		cout << "排ar[" << i << "]数据，排序后  ";	//输出这一趟排序前的序列
		for (int k = 1; k < size; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}

	cout << "堆排序  移动次数：" << move_heap << "  比较次数" << cmp_heap << endl;
}

//归并排序
//将数组分为两两一组进行归并并排序
int move_merge = 0, cmp_merge = 0;	//移动和比较次数
void mergeSort(sortType S[size], sortType T[size], int low, int high)
{
	if (low < high) {

		int mid = (low + high) / 2;
		mergeSort(S, T, low, mid);//递归分成最小的两个一组
		mergeSort(S, T, mid + 1, high);
		cout << "从" << setw(2) << setiosflags(ios::left) << low << "到" <<
			setw(2) << setiosflags(ios::left) << high << "这一部分归并排序前为：";//输出部分段的排序过程
		for (int k = low; k <= high; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		int beg1 = low, beg2 = mid + 1;//S数组两部分的开始
		int k = low;//T数组的开始，T数组是辅助数组
		//S数组两部分小的先进入T
		while ((beg1 <= mid) && (beg2 <= high)) {
			cmp_merge++;//比较次数++
			if (S[beg1] <= S[beg2]) {
				T[k++] = S[beg1++];
				move_merge++;//移动次数++
			}
			else {
				T[k++] = S[beg2++];
				move_merge++;//移动次数++
			}
		}
		//循环结束，有一部分先结束，没结束那部分全部进入T
		while (beg1 <= mid)
		{
			T[k++] = S[beg1++];
			move_merge++;//移动次数++
		}
		while (beg2 <= high)
		{
			T[k++] = S[beg2++];
			move_merge++;//移动次数++
		}
		//将排好序重新赋回数组
		for (int i = low; i <= high; i++) {
			S[i] = T[i];
			move_merge++;//移动次数++
		}
		cout << "从" << setw(2) << setiosflags(ios::left) << low << "到"
			<< setw(2) << setiosflags(ios::left) << high << "这一部分归并排序后为：";	//输出部分段的排序过程
		for (int k = low; k <= high; k++) {
			cout << ar[k] << "  ";
		}
		cout << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}
}
//归并排序
void MergeSort(sortType(&ar)[size])
{
	//辅助空间数组
	sortType R[size] = { 0 };
	mergeSort(ar, R, 1, size - 1);
	cout << "归并排序  移动次数：" << move_merge << "  比较次数" << cmp_merge << endl;
}

//--------------------------基数排序-----------------------------------------------

//采用静态链表
#define key_num 17		//排序数组大小，0不存放数据
#define radix_num 10	//每一个基数的数量
#define radixMax 5	//基数最大的位数，比如个十百千万···
#define radixSortNum 2	//本题目只有个和十位

struct RadixType
{
	int key;
	char radix[radixMax];//基数，比如radix[0]为个位，ar[1]为十位··，分别用A B C··代表
	int next;//静态链表的下个结点
};

RadixType array[key_num];	//需排序的数组
typedef int List[radix_num];
List first, end;	//将数据按某一基数分配，first 和 end 分别指向这一基数链表的起点和终点

//初始化需排序的数组
void getValue_rSort(RadixType(&ar)[key_num])
{
	srand(int(time(0)));
	ar[0].key = -32767;
	ar[0].next = 1;
	for (int i = 1; i < key_num; i++) {
		ar[i].key = rand() % 90 + 10;	//生成2位正整数
		ar[i].next = i + 1;
		for (int k = 0; k < radixMax; k++) {
				ar[i].radix[k] = 65 + k;
		}
	}
	ar[key_num - 1].next = 0;//最后一位指向零
}

//输出数组
void display_rSort(RadixType(&ar)[key_num])
{
	cout << "数组为：";
	for (int i = ar[0].next; i; i = ar[i].next)
	{
		cout << ar[i].key << " ";
	}
	cout << endl;
}

//这个key应该分在那组，比如个位，77分在ar[7]
int posRadix(int key, char ch)
{
	switch (ch)
	{
	case 'A':	//分配个位
		return key % 10;
		break;
	case 'B':	//分配十位
		return key / 10;
		break;
	case 'C':	//分配十位
		return key / 100;
		break;
	case 'D':	//分配十位
		return key / 1000;
		break;
	case 'E':	//分配十位
		return key / 10000;
		break;
	default:
		break;
	}
}
//分配
void contribute(RadixType (&array)[key_num], List f, List e, int radixNum)
{
	for (int p = array[0].next; p != 0; p = array[p].next)
	{
		int pos = posRadix(array[p].key, array[p].radix[radixNum]);//求出这个数据应放在哪个链中
		if (f[pos] == 0) {									//（如果是个位，那么个位为8就放在f[8]和e[0]链中）
			f[pos] = p;
		}
		else {
			array[e[pos]].next = p;			//新进入的插入结尾
		}
		e[pos] = p;
	}
}
//收集
void collect(RadixType(&ar)[key_num], List f, List e)
{
	bool ar0 = false;	//判断是否ar[0].next已经赋好值
	int t = 0;	//记录每个位的最后一个，已连接后面的位
	for (int i = 0; i < radix_num; i++) {
		if (f[i]) {		//ar[0].next还没赋值
			if (!ar0) {
				ar[0].next = f[i];
				t = e[i];
				ar0 = true;
			}
			else {	//每个不空的链相连
				ar[t].next = f[i];
				t = e[i];
			}
		}
	}
	ar[t].next = 0;//最后连到ar[0]
	for (int j = 0; j < radix_num; j++) {	//将first，end复位
		first[j] = 0;
		end[j] = 0;
	}

}
//基数排序
void radixSort(RadixType(&ar)[key_num])
{
	for (int i = 0; i < radixSortNum; i++) {
		contribute(ar, first, end, i);
		collect(ar, first, end);
		cout << "第" << i + 1 << "趟分配收集排序为：\n";
		display_rSort(ar);
	}
}


//--------------------------基数排序-----------------------------------------------

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
	cout << "快速排序  移动次数：" << move_qs << "  比较次数" << cmp_qs << endl;
	move_qs = 0, cmp_qs = 0;//置0方便后面重新使用
	chooseSort(ar);
	display(ar);
	heapSort(ar);
	move_heap = 0, cmp_heap = 0;//置0方便后面重新使用
	display(ar);
	MergeSort(ar);
	move_merge = 0, cmp_merge = 0;//置0方便后面重新使用
	display(ar);*/
	/*getValue_rSort(array);
	cout << "基数排序前  \n";
	display_rSort(array);
	radixSort(array);
	cout << "基数排序前  \n";
	display_rSort(array);*/

}
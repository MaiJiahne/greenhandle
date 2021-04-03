//链表
struct ListNode{
	int data;
	ListNode* next;
};

//
class List{
private:
	ListNode * head;

public:
	List():head(nullptr){}
	~List();
	void createList(int);
	void showList();
	int find(int);
	void Insert(int,int);
	void Delete_pos(int);	//删除参数位置数据
	void Delete_value(int);		//删除第一个跟参数数值相同数据
	void Delete_list();
	void AddThreeRandomNum();
	void reverse();
	void sort_value(int);

};

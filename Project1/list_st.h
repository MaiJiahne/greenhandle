//����
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
	void Delete_pos(int);	//ɾ������λ������
	void Delete_value(int);		//ɾ����һ����������ֵ��ͬ����
	void Delete_list();
	void AddThreeRandomNum();
	void reverse();
	void sort_value(int);

};

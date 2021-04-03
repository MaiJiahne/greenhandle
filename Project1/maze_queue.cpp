#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

#define MAXSIZE 100
struct path{
	int x;
	int y;
	int pre;
};
path Queue[MAXSIZE];
int front = 0;
int rear = 0;
int maze[10][10] =
{
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,0,0,1,1,0,0,1},
    {1,0,1,1,1,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,1},  
    {1,0,1,0,1,0,1,1,0,1},
    {1,1,0,0,1,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

vector<path> pvec;


bool search(int xb, int yb, int xe, int ye)
{
    path l;
    l.x = xb;
    l.y = yb;
    l.pre = -1;
    maze[l.x][l.y] = -1;
    Queue[++rear] = l;
    
    while (front != rear) {
        front++;
        int x = Queue[front].x;
        int y = Queue[front].y;
        if (x == xe && y == ye) {
            return true;
        }
        int temp_x, temp_y;
        for (int i = 0; i < 4; i++) {   //探寻四周有无路可走，有路则入队
            switch (i)
            {
            case 0:
                temp_x = x - 1;
                temp_y = y;
                break;
            case 1:
                temp_x = x + 1;
                temp_y = y;
                break;
            case 2:
                temp_x = x ;
                temp_y = y - 1;
                break;
            case 3:
                temp_x = x;
                temp_y = y + 1;
                break;
            default:
                break;
            }//switch
            if (maze[temp_x][temp_y] == 0) {
                rear++;
                Queue[rear].x = temp_x;
                Queue[rear].y = temp_y;
                Queue[rear].pre = front;
                maze[temp_x][temp_y] = -1;
            }
        }//for
        
    }//while
    return false;
}

void show()
{
    if (!search(1,1,8,8))
        cout << "不存在路径" << endl;
    else {
        cout << "最短路径为：" << endl;
        for (int i = front; i > 0; i = Queue[i].pre) {
            pvec.push_back(Queue[i]);
        }
        for (auto p = pvec.crbegin(); p != pvec.crend(); ++p) {
            cout << "(" << p->x << "," << p->y << ")" << " ";
        }
    }
}

int main()
{
    show();
}
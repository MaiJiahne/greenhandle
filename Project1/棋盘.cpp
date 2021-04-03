
#include <stdio.h>
const char* p[2] = { "|||", "   " };

int main()
{
	int x, y;
	// 棋盘
	for (y = 0; y < 10; y++)
	{
		for (x = 0; x < 10; x++)
		{
			if ((x + y) % 2 == 0)	// 条件
			{
				printf("%s", p[0]);
			}
			else
			{
				printf("%s", p[1]);
			}
		}
		printf("\r\n");
	}

	// 方框
	for (y = 0; y < 10; y++)
	{
		for (x = 0; x < 10; x++)
		{
			if (y == 0 || x == 0 || y == 9 || x == 9)	// 条件
			{
				printf("%s", p[0]);
			}
			else
			{
				printf("%s", p[1]);
			}
		}
		printf("\r\n");
	}

	// 条纹
	for (y = 0; y < 10; y++)
	{
		for (x = 0; x < 10; x++)
		{
			if (y % 2 == 0)	// 条件
			{
				printf("%s", p[0]);
			}
			else
			{
				printf("%s", p[1]);
			}
		}
		printf("\r\n");
	}

	// 交叉线
	for (y = 0; y < 10; y++)
	{
		for (x = 0; x < 10; x++)
		{
			if (x == y || (x + y) == 9)	// 条件
			{
				printf("%s", p[0]);
			}
			else
			{
				printf("%s", p[1]);
			}
		}
		printf("\r\n");
	}
	return 0;
}

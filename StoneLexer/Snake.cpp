#include "stdafx.h"
#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>

// 蛇的状态，U-上; D-下; L-左; R-右
#define U 1
#define D 2
#define L 3 
#define R 4

// 蛇身的一个节点
typedef struct SNAKE
{
	int x;
	int y;
	struct SNAKE *next;
}Snake;

//*********全局变量***********
//
// 总得分与每次吃食物得分
int score = 0, add = 10;
// 每次运行的时间间隔
int status, sleeptime = 200;
// 蛇头指针，食物指针
Snake *head, *food;
// 遍历蛇的时候用到的指针
Snake *q;
// 游戏结束的情况，1：撞到墙；2：咬到自己；3：主动退出游戏。
int endGameStatus = 0;

// 声明全部函数
void Pos();
void creatMap();
void initSnake();
int biteSelf();
void createFood();
void cantCrossWall();
void snakeMove();
void pause();
void runGame();
void initGame();
void endGame();
void gameStart();

// 设置光标位置
void Pos(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE hOutput;
	//返回标准的输入、输出或错误的设备的句柄，也就是获得输入、输出/错误的屏幕缓冲区的句柄
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}


// 创建地图
void creatMap()
{
	// 打印上下边框
	int i;
	for (i = 0; i < 58; i += 2)
	{
		Pos(i, 0);
		printf("■"); // 一个方块占两个位置
		Pos(i, 26);
		printf("■");
	}

	// 打印左右边框
	for (i = 1; i < 26; i++)
	{
		Pos(0, i);
		printf("■");
		Pos(56, i);
		printf("■");
	}
}

// 初始化Snake
void initSnake()
{
	// 从蛇尾开始，以x,y设定开始的位置
	Snake *tail;
	tail = (Snake*)malloc(sizeof(Snake));
	tail->x = 24;
	tail->y = 5;
	tail->next = NULL;
	
	// 初始长度为4
	for (int i = 1; i <= 4; i++)
	{
		head = (Snake*)malloc(sizeof(Snake));
		head->next = tail;
		head->x = 24 + 2 * i;
		head->y = 5;
		tail = head;
	}

	// 从头到尾，输出蛇身
	while (tail != NULL)
	{
		Pos(tail->x, tail->y);
		printf("■");
		tail = tail->next;
	}
}

// 判断是否咬到了自己
int biteSelf()
{
	Snake *self;
	self = head->next;
	while (self != NULL)
	{
		if (self->x == head->x && self->y == head->y)
		{
			return 1;
		}

		self = self->next;
	}

	return 0;
}

// 随机出现食物
void createFood()
{
	Snake *food_1;
	// 为了防止每次产生的随机数相同，种子设置为time
	srand((unsigned)time(NULL));
	food_1 = (Snake*)malloc(sizeof(Snake));
	// 保证其为偶数，使得食物能与蛇头对齐
	while ((food_1->x % 2) != 0)    
	{
		food_1->x = rand() % 52 + 2;
	}

	food_1->y = rand() % 24 + 1;
	q = head;

	while (q->next == NULL)
	{
		// 判断蛇身是否与食物重合
		if (q->x == food_1->x && q->y == food_1->y) 
		{
			free(food_1);
			createFood();
		}

		q = q->next;
	}

	Pos(food_1->x, food_1->y);
	food = food_1;
	printf("■");
}

// 不能穿墙
void cantCrossWall()
{
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
	{
		endGameStatus = 1;
		endGame();
	}
}

// 蛇前进,上U,下D,左L,右R
void MoveSnake()
{
	Snake * nextHead;
	cantCrossWall();

	nextHead = (Snake*)malloc(sizeof(Snake));

	// Up
	if (status == U)
	{
		nextHead->x = head->x;
		nextHead->y = head->y - 1;
		// 吃到了食物
		if (nextHead->x == food->x && nextHead->y == food->y)
		{
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}

			score = score + add;
			createFood();
		}
		else
		{
			// 没有食物
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}

			Pos(q->next->x, q->next->y);
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}

	// Down
	if (status == D)
	{
		nextHead->x = head->x;
		nextHead->y = head->y + 1;
		// 吃到了食物
		if (nextHead->x == food->x && nextHead->y == food->y)
		{
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}

			score = score + add;
			createFood();
		}
		else                               
		{
			// 没有食物
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}

			Pos(q->next->x, q->next->y);
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}

	// Left
	if (status == L)
	{
		nextHead->x = head->x - 2;
		nextHead->y = head->y;
		// 吃到了食物
		if (nextHead->x == food->x && nextHead->y == food->y)
		{
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			score = score + add;
			createFood();
		}
		else
		{
			// 没有吃到食物
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}

			Pos(q->next->x, q->next->y);
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}

	// Right
	if (status == R)
	{
		nextHead->x = head->x + 2;
		nextHead->y = head->y;
		// 吃到了食物
		if (nextHead->x == food->x && nextHead->y == food->y)
		{
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}

			score = score + add;
			createFood();
		}
		else
		{
			// 没有吃到食物
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}

			Pos(q->next->x, q->next->y);
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}

	// 判断是否会咬到自己
	if (biteSelf() == 1)       
	{
		endGameStatus = 2;
		endGame();
	}
}

// 暂停
void pause()
{
	while (1)
	{
		Sleep(300);
		if (GetAsyncKeyState(VK_SPACE))
		{
			break;
		}
	}
}

// 控制游戏
void runGame()      
{
	Pos(64, 15);
	printf("不能穿墙，不能咬到自己\n");
	Pos(64, 16);
	printf("用↑.↓.←.→分别控制蛇的移动.\n");
	Pos(64, 17);
	printf("F1 为加速，F2 为减速\n");
	Pos(64, 18);
	printf("ESC ：退出游戏.space：暂停游戏.\n");
	Pos(64, 20);
	printf("==========The C language========");
	status = R;
	while (1)
	{
		Pos(64, 10);
		printf("得分：%d  ", score);
		Pos(64, 11);
		printf("每个食物得分：%d分", add);
		if (GetAsyncKeyState(VK_UP) && status != D)
		{
			status = U;
		}
		else if (GetAsyncKeyState(VK_DOWN) && status != U)
		{
			status = D;
		}
		else if (GetAsyncKeyState(VK_LEFT) && status != R)
		{
			status = L;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && status != L)
		{
			status = R;
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			pause();
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			endGameStatus = 3;
			break;
		}
		else if (GetAsyncKeyState(VK_F1))
		{
			if (sleeptime >= 50)
			{
				sleeptime = sleeptime - 30;
				add = add + 2;
				if (sleeptime == 320)
				{
					// 防止减到1之后再加回来有错
					add = 2;
				}
			}
		}
		else if (GetAsyncKeyState(VK_F2))
		{
			if (sleeptime < 350)
			{
				sleeptime = sleeptime + 30;
				add = add - 2;
				if (sleeptime == 350)
				{
					// 保证最低分为1
					add = 1;
				}
			}
		}

		Sleep(sleeptime);
		MoveSnake();
	}
}

// 初始化游戏界面
void initGame()
{
	Pos(40, 12);

	printf("欢迎来到贪吃蛇游戏！");
	Pos(40, 25);
	system("pause");
	system("cls");
	Pos(25, 12);
	printf("用↑.↓.←.→分别控制蛇的移动，F1 为加速，2 为减速\n");
	Pos(25, 13);
	printf("加速将能得到更高的分数。\n");
	system("pause");
	system("cls");
}

// 结束游戏
void endGame()
{
	system("cls");
	Pos(24, 12);
	if (endGameStatus == 1)
	{
		printf("对不起，您撞到墙了。Game over.");
	}
	else if (endGameStatus == 2)
	{
		printf("对不起，您咬到自己了。Game over.");
	}
	else if (endGameStatus == 3)
	{
		printf("您的已经结束了游戏。");
	}

	Pos(24, 13);
	printf("您的得分是%d\n", score);
	while (getchar() != 'y')
	{
		printf("close?[y]");
	}

	exit(0);
}

// 游戏初始化
void gameStart()
{
	// 显示格子
	system("mode con cols=100 lines=30");
	initGame();
	creatMap();
	initSnake();
	createFood();
}

int main()
{
	gameStart();
	runGame();
	endGame();
	return 0;
}
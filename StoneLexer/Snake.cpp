#include "stdafx.h"
#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>

// �ߵ�״̬��U-��; D-��; L-��; R-��
#define U 1
#define D 2
#define L 3 
#define R 4

// �����һ���ڵ�
typedef struct SNAKE
{
	int x;
	int y;
	struct SNAKE *next;
}Snake;

//*********ȫ�ֱ���***********
//
// �ܵ÷���ÿ�γ�ʳ��÷�
int score = 0, add = 10;
// ÿ�����е�ʱ����
int status, sleeptime = 200;
// ��ͷָ�룬ʳ��ָ��
Snake *head, *food;
// �����ߵ�ʱ���õ���ָ��
Snake *q;
// ��Ϸ�����������1��ײ��ǽ��2��ҧ���Լ���3�������˳���Ϸ��
int endGameStatus = 0;

// ����ȫ������
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

// ���ù��λ��
void Pos(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE hOutput;
	//���ر�׼�����롢����������豸�ľ����Ҳ���ǻ�����롢���/�������Ļ�������ľ��
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}


// ������ͼ
void creatMap()
{
	// ��ӡ���±߿�
	int i;
	for (i = 0; i < 58; i += 2)
	{
		Pos(i, 0);
		printf("��"); // һ������ռ����λ��
		Pos(i, 26);
		printf("��");
	}

	// ��ӡ���ұ߿�
	for (i = 1; i < 26; i++)
	{
		Pos(0, i);
		printf("��");
		Pos(56, i);
		printf("��");
	}
}

// ��ʼ��Snake
void initSnake()
{
	// ����β��ʼ����x,y�趨��ʼ��λ��
	Snake *tail;
	tail = (Snake*)malloc(sizeof(Snake));
	tail->x = 24;
	tail->y = 5;
	tail->next = NULL;
	
	// ��ʼ����Ϊ4
	for (int i = 1; i <= 4; i++)
	{
		head = (Snake*)malloc(sizeof(Snake));
		head->next = tail;
		head->x = 24 + 2 * i;
		head->y = 5;
		tail = head;
	}

	// ��ͷ��β���������
	while (tail != NULL)
	{
		Pos(tail->x, tail->y);
		printf("��");
		tail = tail->next;
	}
}

// �ж��Ƿ�ҧ�����Լ�
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

// �������ʳ��
void createFood()
{
	Snake *food_1;
	// Ϊ�˷�ֹÿ�β������������ͬ����������Ϊtime
	srand((unsigned)time(NULL));
	food_1 = (Snake*)malloc(sizeof(Snake));
	// ��֤��Ϊż����ʹ��ʳ��������ͷ����
	while ((food_1->x % 2) != 0)    
	{
		food_1->x = rand() % 52 + 2;
	}

	food_1->y = rand() % 24 + 1;
	q = head;

	while (q->next == NULL)
	{
		// �ж������Ƿ���ʳ���غ�
		if (q->x == food_1->x && q->y == food_1->y) 
		{
			free(food_1);
			createFood();
		}

		q = q->next;
	}

	Pos(food_1->x, food_1->y);
	food = food_1;
	printf("��");
}

// ���ܴ�ǽ
void cantCrossWall()
{
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
	{
		endGameStatus = 1;
		endGame();
	}
}

// ��ǰ��,��U,��D,��L,��R
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
		// �Ե���ʳ��
		if (nextHead->x == food->x && nextHead->y == food->y)
		{
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("��");
				q = q->next;
			}

			score = score + add;
			createFood();
		}
		else
		{
			// û��ʳ��
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("��");
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
		// �Ե���ʳ��
		if (nextHead->x == food->x && nextHead->y == food->y)
		{
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("��");
				q = q->next;
			}

			score = score + add;
			createFood();
		}
		else                               
		{
			// û��ʳ��
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("��");
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
		// �Ե���ʳ��
		if (nextHead->x == food->x && nextHead->y == food->y)
		{
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("��");
				q = q->next;
			}
			score = score + add;
			createFood();
		}
		else
		{
			// û�гԵ�ʳ��
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("��");
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
		// �Ե���ʳ��
		if (nextHead->x == food->x && nextHead->y == food->y)
		{
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("��");
				q = q->next;
			}

			score = score + add;
			createFood();
		}
		else
		{
			// û�гԵ�ʳ��
			nextHead->next = head;
			head = nextHead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("��");
				q = q->next;
			}

			Pos(q->next->x, q->next->y);
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}

	// �ж��Ƿ��ҧ���Լ�
	if (biteSelf() == 1)       
	{
		endGameStatus = 2;
		endGame();
	}
}

// ��ͣ
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

// ������Ϸ
void runGame()      
{
	Pos(64, 15);
	printf("���ܴ�ǽ������ҧ���Լ�\n");
	Pos(64, 16);
	printf("�á�.��.��.���ֱ�����ߵ��ƶ�.\n");
	Pos(64, 17);
	printf("F1 Ϊ���٣�F2 Ϊ����\n");
	Pos(64, 18);
	printf("ESC ���˳���Ϸ.space����ͣ��Ϸ.\n");
	Pos(64, 20);
	printf("==========The C language========");
	status = R;
	while (1)
	{
		Pos(64, 10);
		printf("�÷֣�%d  ", score);
		Pos(64, 11);
		printf("ÿ��ʳ��÷֣�%d��", add);
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
					// ��ֹ����1֮���ټӻ����д�
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
					// ��֤��ͷ�Ϊ1
					add = 1;
				}
			}
		}

		Sleep(sleeptime);
		MoveSnake();
	}
}

// ��ʼ����Ϸ����
void initGame()
{
	Pos(40, 12);

	printf("��ӭ����̰������Ϸ��");
	Pos(40, 25);
	system("pause");
	system("cls");
	Pos(25, 12);
	printf("�á�.��.��.���ֱ�����ߵ��ƶ���F1 Ϊ���٣�2 Ϊ����\n");
	Pos(25, 13);
	printf("���ٽ��ܵõ����ߵķ�����\n");
	system("pause");
	system("cls");
}

// ������Ϸ
void endGame()
{
	system("cls");
	Pos(24, 12);
	if (endGameStatus == 1)
	{
		printf("�Բ�����ײ��ǽ�ˡ�Game over.");
	}
	else if (endGameStatus == 2)
	{
		printf("�Բ�����ҧ���Լ��ˡ�Game over.");
	}
	else if (endGameStatus == 3)
	{
		printf("�����Ѿ���������Ϸ��");
	}

	Pos(24, 13);
	printf("���ĵ÷���%d\n", score);
	while (getchar() != 'y')
	{
		printf("close?[y]");
	}

	exit(0);
}

// ��Ϸ��ʼ��
void gameStart()
{
	// ��ʾ����
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
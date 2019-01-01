// LRU - Least Recently Used

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LRU_SIZE 20
#define HASH_BASE 20
#define LRU_SUCCESS 0
#define LRU_ERROR  -1
#define LRU_MISS 0
#define LRU_HIT 1
#define LRU_HASH_KEY(_key, _base)       (int)( ((int)_key) % (_base) )

typedef struct _LRU_NODE{
	int Id;
	int key;
	int free;
	int prev;
	int next;
}LRU_NODE, *PLRU_NODE;


typedef struct _LRU_HASH{
	unsigned long   baseSize;
	int				base[HASH_BASE];
}LRU_HASH, *PLRU_HASH;


typedef struct _LRU_LIST{
	int capacity;
	int usage;
	int freeList;
	int head;
	int tail;
	LRU_HASH hash;
	LRU_NODE bucket[LRU_SIZE];
}LRU_LIST, *PLRU_LIST;

int Init(PLRU_LIST list, int capacity, int hashBase)
{
	int i;
	PLRU_NODE node;
	list->capacity = capacity;
	list->usage = 0;
	list->head = -1;
	list->tail = -1;
	list->freeList = -1;

	for (i = capacity - 1; i >= 0; i--)
	{
		list->bucket[i].Id = i;
		list->bucket[i].key = -1;
		list->bucket[i].free = 1;
		list->bucket[i].prev = -1;
		list->bucket[i].next = -1;
		if (list->freeList == -1)
		{
			list->freeList = list->bucket[i].Id;
		}
		else
		{
			node = &(list->bucket[list->freeList]);
			node->prev = list->bucket[i].Id;
			list->bucket[i].next = node->Id;
			list->freeList = list->bucket[i].Id;
		}
	}

	for (i = 0; i < hashBase; i++)
	{
		list->hash.base[i] = -1;
	}

	list->hash.baseSize = hashBase;
	return LRU_SUCCESS;
}

int LRU_SetHead(PLRU_LIST list, PLRU_NODE node)
{
	PLRU_NODE tempNode;
	if (node->free)
		return LRU_SUCCESS;

	if (node->Id == list->head)
		return LRU_SUCCESS;

	if (list->head == -1)
	{
		list->head = node->Id;
		list->tail = node->Id;
		node->prev = -1;
		node->next = -1;
	}
	else
	{
		if (list->tail == node->Id)
		{
			list->tail = node->prev;
			tempNode = &(list->bucket[list->tail]);
			tempNode->next = -1;

		}
		else
		{
			tempNode = &(list->bucket[node->prev]);
			tempNode->next = node->next;
			tempNode = &(list->bucket[node->next]);
			tempNode->prev = node->prev;
		}

		tempNode = &(list->bucket[list->head]);
		tempNode->prev = node->Id;
		node->next = list->head;
		node->prev = -1;
		list->head = node->Id;
	}

	return LRU_SUCCESS;
}

int LRU_GetFree(PLRU_LIST list, PLRU_NODE *freeNode)
{
	PLRU_NODE node = NULL;

	if (list->freeList != -1)
	{
		node = &(list->bucket[list->freeList]);
		list->freeList = node->next;

		if (list->freeList != -1)
		{
			list->bucket[list->freeList].prev = -1;
		}

		node->free = 1;
		*freeNode = node;
		return LRU_SUCCESS;
	}
	else
	{
		*freeNode = NULL;
		return LRU_ERROR;
	}
}

/*
lru_delete: delete tail lru node
list: lru list
*/
int LRU_Delete(PLRU_LIST list)
{
	PLRU_NODE tempNode;
	int hashkey;
	if (list->tail == -1)
		return LRU_ERROR;

	tempNode = &(list->bucket[list->tail]);

	list->tail = tempNode->prev;

	if (list->tail != -1)
		list->bucket[list->tail].next = -1;
	else
		list->head = -1;

	//删除hash结点
	hashkey = LRU_HASH_KEY(tempNode->key, list->hash.baseSize);
	list->hash.base[hashkey] = -1;

	if (list->freeList != -1)
	{
		tempNode->next = list->freeList;
		list->bucket[list->freeList].prev = tempNode->Id;
		list->freeList = tempNode->Id;
		tempNode->prev = -1;
		tempNode->free = 1;
		tempNode->key = -1;
	}
	else
	{
		list->freeList = tempNode->Id;
		tempNode->key = -1;
		tempNode->free = 1;
		tempNode->prev = -1;
		tempNode->next = -1;
	}

	list->usage--;
	return LRU_SUCCESS;
}

int LRU_Insert(PLRU_LIST list, PLRU_NODE node)
{
	//对于list满的情况和插入有相同key的node
	//在函数调用之前作判断
	PLRU_NODE tempnode;
	int key;
	int hashkey;

	//插入lru hash表
	key = node->key;
	hashkey = LRU_HASH_KEY(key, list->hash.baseSize);
	list->hash.base[hashkey] = node->Id;

	if (list->head == -1)
	{
		list->head = node->Id;
		list->tail = node->Id;
		node->prev = -1;
		node->next = -1;
	}
	else
	{
		tempnode = &(list->bucket[list->head]);
		node->next = list->head;
		tempnode->prev = node->Id;
		list->head = node->Id;
		node->prev = -1;
	}

	node->free = 0;
	list->usage++;

	return LRU_SUCCESS;
}

int LRU_Inquiry(PLRU_LIST list, int key)
{
	PLRU_NODE tempNode;
	int hashKey;

	if (list->head == -1)
		return LRU_MISS;

	hashKey = LRU_HASH_KEY(key, list->hash.baseSize);

	if (list->hash.base[hashKey] == -1)
		return LRU_MISS;
	else
	{
		tempNode = &(list->bucket[list->hash.base[hashKey]]);
	}

	LRU_SetHead(list, tempNode);

	return LRU_HIT;
}

// 显示LRU结构
int LRU_Show(PLRU_LIST list)
{
	PLRU_NODE node;

	if (list->head == -1)
	{
		printf("list is empty!\n");
		return LRU_ERROR;
	}

	node = &(list->bucket[list->head]);

	while (node)
	{
		printf("  id: %2d, key: %2d\n", node->Id, node->key);

		if (node->next == -1)
			node = NULL;
		else
			node = &(list->bucket[node->next]);
	}

	return LRU_SUCCESS;
}

int LRU_Clear(PLRU_LIST list)
{
	PLRU_NODE tempNode, node;
	unsigned long j;

	if (list->head == -1)
		return LRU_SUCCESS;

	tempNode = &(list->bucket[list->head]);

	while (tempNode)
	{
		if (tempNode->next == -1)
			node = NULL;
		else
			node = &(list->bucket[tempNode->next]);

		if (list->freeList == -1)
		{
			list->freeList = tempNode->Id;
			tempNode->free = 1;
			tempNode->key = -1;
			tempNode->next = -1;
			tempNode->prev = -1;
		}
		else
		{
			tempNode->next = list->freeList;
			list->bucket[list->freeList].prev = tempNode->Id;
			list->freeList = tempNode->Id;
			tempNode->prev = -1;
			tempNode->key = -1;
			tempNode->free = 1;
		}

		tempNode = node;
	}

	for (j = 0; j < list->hash.baseSize; j++)
	{
		list->hash.base[j] = -1;
	}

	list->head = -1;
	list->tail = -1;
	list->usage = 0;

	return LRU_SUCCESS;
}

int b_main()
{
	int key_table[LRU_SIZE];
	int i, usage;
	PLRU_LIST list;
	PLRU_NODE node;
	srand(time(NULL));

	for (i = 0; i < LRU_SIZE; i++)
	{
		key_table[i] = rand() % LRU_SIZE;
		printf("key_table[%2d]: %2d\n", i, key_table[i]);
	}

	list = (PLRU_LIST)malloc(sizeof(LRU_LIST));
	if (!list)
		printf("malloc error!\n");

	Init(list, LRU_SIZE, HASH_BASE);

	for (i = 0; i < LRU_SIZE; i++)
	{
		if (LRU_MISS == LRU_Inquiry(list, key_table[i]))
		{
			if (LRU_SUCCESS == LRU_GetFree(list, &node))
			{
				node->key = key_table[i];
				LRU_Insert(list, node);
			}
			else
			{
				printf("lru_GetFree:get no free node!\n");
			}
		}
		else
		{
			printf("***************\n");
			printf("lru_Inquiry hit key_table[%d]: %2d\n", i, key_table[i]);
			LRU_Show(list);
		}
	}

	LRU_Show(list);
	usage = list->usage;

	for (i = 0; i < usage; i++)
	{
		LRU_Delete(list);
		printf("After delete one node!\n");
		LRU_Show(list);
	}

	LRU_Clear(list);

	return 0;
}

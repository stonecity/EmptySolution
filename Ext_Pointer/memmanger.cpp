#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <windows.h>

#define   MLC_MC    1      // MLCmalloc()的标志
#define   MLC_FE    0      // MLCfree()的标志
#define   MLC_Check  -1    // 检测内存的标志

#define   M_SUCCESS	0	 // 内存分配成功
#define   M_FAILED	1	 // 内存分配失败
#define	  M_FREE_ERROR  -1 // 内存释放出错

typedef struct MMemory         //单向链表结构
{
    unsigned int address;
	struct MMemory *next;
}Mem, *LinkMem;


/* 内存管理 */
size_t MemoryControl(size_t addr, char flag)  
{
    static Mem head;        // 静态局部变量，保存链表头
	LinkMem tmp = head.next;
	LinkMem node = &head;
	if (MLC_MC == flag)         //增加链表节点
	{
		// 找到链表尾部最后一个非空节点
		while (tmp)
		{
			node = tmp;
			tmp = tmp->next;
		}

		node->next = (LinkMem)malloc(sizeof(Mem));
		if (node->next == NULL)
		{
			return M_FAILED;   //分配失败!
		}

		node = node->next;
		node->address = addr;
		node->next = NULL;
	}
	else if (MLC_FE == flag)     //删除节点
	{
		while (tmp && (tmp->address != addr))
		{
			node = tmp;
			tmp = tmp->next;
		}

		if (tmp == NULL)
		{
			return M_FREE_ERROR;  //free地址出错!
		}
		else
		{
			node->next = tmp->next;
			free(tmp);
		}
	}
	else
	{
		// 有泄漏就返回泄露的地址，无则返回null
		return (int)(head.next ? head.next->address : 0);
	}
    
	return M_SUCCESS;
}


/* 内存分配 */
void* MMCmalloc(size_t size)
{
	void *pMalc = malloc(size);
	if (NULL == pMalc)
	{
		return NULL;
	}
	else if (MemoryControl((size_t)pMalc, MLC_MC) == M_FAILED)
	{
		free(pMalc);   //动态链建立失败时释放此次分配的空间
		return NULL;
	}
	else
	{
		return pMalc;
	}
}

/* 内存释放 */
void MMCfree(void *ptr)
{
	if (MemoryControl((size_t)ptr, MLC_FE) == M_FREE_ERROR)
	{
		printf("%s\n", "被释放的内存地址错误!");
		return;
	}
	else
	{
		free(ptr);
	}
}


/* 检查泄漏 */
size_t CheckLeak()
{
	return (size_t)(MemoryControl((size_t)0, MLC_Check));
}

void func(int a, ...)
{
	int *temp = &a;
	temp++;

	for (size_t i = 0; i < a; i++)
	{
		std::cout << *temp << std::endl;
		temp++;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	wchar_t* strtest = L"中文测试";
	printf("%s\n", strtest);

	int a = 1, b = 2, c = 3, d = 4;
	int cnt = 4;
	func(cnt, a, b, c, d);

	// 类型提升和转换
	long x = -1;

	if (x < sizeof(x)) 
	{
		printf("OK\n");
	}
	else 
	{
		printf("error\n");
	}

	const char *p1 = "Hello World";
	char p2[] = "Hello World";
	printf("sizeof: %2d, strlen: %d\n", sizeof(p1), strlen(p1));
	printf("sizeof: %2d, strlen: %d\n", sizeof(p2), strlen(p2));

	int memBlockCount = 10;
	char **p = NULL;
	char *str = "1234567890098765432";
	char *tmp, i;

	p = (char**)MMCmalloc(memBlockCount * sizeof(char*));

	printf("分配p=%#x\n", p);

	for (i = 0; i < memBlockCount; i++)
	{
		p[i] = (char*)MMCmalloc(20 * sizeof(char));
		sscanf(str, "%s", p[i]);
	}

	// 显示内存块地址信息
	for (i = 0; i < memBlockCount; i++)
	{
		printf("&p[%d]=%#x  *p[%d]=%s\n", i, p[i], i, p[i]);
	}

	printf("释放 p=%#x\n", p);   // 不按正常顺序释放

	MMCfree(p);

	printf("检测内存是否泄露\n");
	while ((tmp = (char*)CheckLeak()) != 0)  // 检测是否有泄漏内存
	{
		MMCfree(tmp);               // 释放检测到的泄漏空间
		printf("free tmp=%#x\n", tmp);
	}

	return 0;
}

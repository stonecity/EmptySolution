#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <windows.h>

#define   MLC_MC    1      // MLCmalloc()�ı�־
#define   MLC_FE    0      // MLCfree()�ı�־
#define   MLC_Check  -1    // ����ڴ�ı�־

#define   M_SUCCESS	0	 // �ڴ����ɹ�
#define   M_FAILED	1	 // �ڴ����ʧ��
#define	  M_FREE_ERROR  -1 // �ڴ��ͷų���

typedef struct MMemory         //��������ṹ
{
    unsigned int address;
	struct MMemory *next;
}Mem, *LinkMem;


/* �ڴ���� */
size_t MemoryControl(size_t addr, char flag)  
{
    static Mem head;        // ��̬�ֲ���������������ͷ
	LinkMem tmp = head.next;
	LinkMem node = &head;
	if (MLC_MC == flag)         //��������ڵ�
	{
		// �ҵ�����β�����һ���ǿսڵ�
		while (tmp)
		{
			node = tmp;
			tmp = tmp->next;
		}

		node->next = (LinkMem)malloc(sizeof(Mem));
		if (node->next == NULL)
		{
			return M_FAILED;   //����ʧ��!
		}

		node = node->next;
		node->address = addr;
		node->next = NULL;
	}
	else if (MLC_FE == flag)     //ɾ���ڵ�
	{
		while (tmp && (tmp->address != addr))
		{
			node = tmp;
			tmp = tmp->next;
		}

		if (tmp == NULL)
		{
			return M_FREE_ERROR;  //free��ַ����!
		}
		else
		{
			node->next = tmp->next;
			free(tmp);
		}
	}
	else
	{
		// ��й©�ͷ���й¶�ĵ�ַ�����򷵻�null
		return (int)(head.next ? head.next->address : 0);
	}
    
	return M_SUCCESS;
}


/* �ڴ���� */
void* MMCmalloc(size_t size)
{
	void *pMalc = malloc(size);
	if (NULL == pMalc)
	{
		return NULL;
	}
	else if (MemoryControl((size_t)pMalc, MLC_MC) == M_FAILED)
	{
		free(pMalc);   //��̬������ʧ��ʱ�ͷŴ˴η���Ŀռ�
		return NULL;
	}
	else
	{
		return pMalc;
	}
}

/* �ڴ��ͷ� */
void MMCfree(void *ptr)
{
	if (MemoryControl((size_t)ptr, MLC_FE) == M_FREE_ERROR)
	{
		printf("%s\n", "���ͷŵ��ڴ��ַ����!");
		return;
	}
	else
	{
		free(ptr);
	}
}


/* ���й© */
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
	wchar_t* strtest = L"���Ĳ���";
	printf("%s\n", strtest);

	int a = 1, b = 2, c = 3, d = 4;
	int cnt = 4;
	func(cnt, a, b, c, d);

	// ����������ת��
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

	printf("����p=%#x\n", p);

	for (i = 0; i < memBlockCount; i++)
	{
		p[i] = (char*)MMCmalloc(20 * sizeof(char));
		sscanf(str, "%s", p[i]);
	}

	// ��ʾ�ڴ���ַ��Ϣ
	for (i = 0; i < memBlockCount; i++)
	{
		printf("&p[%d]=%#x  *p[%d]=%s\n", i, p[i], i, p[i]);
	}

	printf("�ͷ� p=%#x\n", p);   // ��������˳���ͷ�

	MMCfree(p);

	printf("����ڴ��Ƿ�й¶\n");
	while ((tmp = (char*)CheckLeak()) != 0)  // ����Ƿ���й©�ڴ�
	{
		MMCfree(tmp);               // �ͷż�⵽��й©�ռ�
		printf("free tmp=%#x\n", tmp);
	}

	return 0;
}

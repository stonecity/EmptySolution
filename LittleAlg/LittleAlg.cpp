// LittleAlg.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <malloc.h>
#include <cstdlib>
#include <vector>
#define MAXSIZE 50

using namespace std;

// ��C++�����У������ⲿC����
#define __cplusplus
#ifdef __cplusplus
extern "C" {
#endif

#include "CClass.h"

#ifdef __cplusplus
}
#endif


// ��ӡ�����
void printRandomNum()
{
	srand((unsigned)time(NULL));

	int rMax = 100, rMin = 10;
	for (int i = 0; i < 10; i++)
	{
		int u = (double)rand() / (RAND_MAX + 1) * (rMax - rMin) + rMin;
		printf("%3d\n", u);
	}
}

// ������Сֵ
int findMin(std::vector<int> &num) 
{
	int result = 0;
    for (int i = 0; i < num.size(); i++)
	{
		if (!result)
		{
			result = num[i];
			continue;
		}
        
		if (result > num[i])
		{
			result = num[i];
		}
	}

	return result;
}

vector<int> double_values(const vector<int>& v)
{
	vector<int> new_values(v.size()); // ������new_values�Ĵ�С, v.size()
	//for (auto x : v)
	{
		//new_values.push_back(x * 2);
	}
	
	// ��������ֻ���ģ���˴˴����������
	/*for (auto itr = new_values.begin(), end_itr = new_values.end(); itr != end_itr; ++itr )
    {         
		new_values.push_back( 2 * (*itr) );
    }*/

	return new_values;
}

// �õݹ�ķ�ʽʵ����ͼ���
int sum(int items[], int i)
{
	return i < 0 ? 0 : items[i] + sum(items, i - 1);
}

typedef struct{
	int a;
	short s[2];
} MSG;

int bmain()
{
	MSG* mp, m = { 4, 1, 5 };
	char *fp, *tp;
	mp = (MSG*)malloc(sizeof(MSG));
	for (fp = (char *)m.s, tp = (char *)mp->s; tp < (char *)(mp + 1);)
	{
		*tp++ = *fp++;
	}

	// ����C���Դ����Add����
	int abSum = add(1, 5);
	std::cout << "Using extern C: " << abSum << std::endl;

	int items[] = { 1, 2, 3, 5 };
	int itemSum = sum(items, 3);

	// ʹ��λ����ķ�ʽ���ڶ������������ҳ���Nλ��0����1
	int num = 110100;
	int pos = 5;
	int shiftNum = num >> (pos - 1);
	printf("Shifted Num: %d\n", shiftNum);
	int result = shiftNum & 1;
	printf("     Result: %d\n", result);

	//ʹ��vector
	vector<int> v;
	for (int i = 0; i < 5; i++)
	{
		v.push_back(i);
	}

	v = double_values(v);

	for (auto x : v)
	{
		std::cout << x << std::endl;
	}

	system("pause");

	return 0;
}
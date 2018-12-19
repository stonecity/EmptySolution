// ShellSort.cpp : 定义控制台应用程序的入口点。
//
// Shell排序

#include "stdafx.h"
#include <iostream>
using namespace std;

// print array
void output_array(int data[], int n)
{
    for (int i = 0; i < n; i++)
	{
		cout << data[i] << " ";
	}

	cout << endl;
}

// swap value
void swap(int *a, int *b)
{
    int x;
    x = *a;
    *a = *b;
    *b = x;
}

// 交换数组元素值
void swap(int data[], int n, int inNum)
{
    for (int i = inNum; i < n; i += inNum)
	{
        for (int j = i; j >= inNum && data[j] > data[j-inNum]; j -= inNum)
        {
			swap(&data[j], &data[j - inNum]);
		}
	}
}

void shellsort(int data[], int n)
{
    for (int i = n / 2; i > 2; i /= 2)
	{
		for (int j = 0; j < i; j++)
		{
			swap(data + j, n - j, i);
		}   
	}
    
    swap(data, n, 1);
}

int ss_tmain(int argc, _TCHAR* argv[])
{
	int data[] = { 5, 13, 95, 77, 4, 30 };
	int len = sizeof(data) / sizeof(int);

	// 输出为排序的原始数组
	output_array(data, len);
	// 希尔排序
	shellsort(data, len);
	// 输出排序后的结果
	output_array(data, len); 

	cout << endl;
	return 0;
}

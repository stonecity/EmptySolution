#include "stdafx.h"
#include <iostream>
#include <assert.h>
using namespace std;

// 插入排序
void insertion_sort(int* arr)
{
	assert(arr != NULL);

	// 计算数组的长度	
	int len = 6;

	for (int i = 1; i < len; i++)
	{
		int key = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] < key)
		{
			arr[j + 1] = arr[j];
			j -= 1;
		}

		arr[j + 1] = key;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int arr[6] = { 5, 2, 4, 6, 3, 1 };

	// 使用插入排序算法对数组进行排序
	insertion_sort(arr);

	// Print result
	for (int i = 0; i < 6; i++)
	{
		cout << arr[i] << " ";
	}

	cout << endl;
	system("pause");

	return 0;
}
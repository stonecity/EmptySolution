#include "stdafx.h"
#include <iostream>
#include <assert.h>
using namespace std;

// ��������
void insertion_sort(int* arr)
{
	assert(arr != NULL);

	// ��������ĳ���	
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

	// ʹ�ò��������㷨�������������
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
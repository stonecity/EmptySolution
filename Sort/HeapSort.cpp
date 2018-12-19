#include "stdafx.h"
#include <iostream>
using namespace std;

void exchange(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int parent(int i)
{
	return i / 2;
}

int left(int i)
{
	return 2 * i;
}

int right(int i)
{
	return 2 * i + 1;
}

// Heap Sort
void max_heapify(int *arr, int i)
{
	int lt = left(i);
	int rt = right(i);
	int heapSize = 5;
	int largest = 0;
	if (lt <= heapSize && arr[lt] > arr[i])
	{
		largest = lt;
	}
	else
	{
		largest = i;
	}

	if (rt <= heapSize && arr[rt] > arr[largest])
	{
		largest = rt;
	}

	if (largest != i)
	{
		exchange(&arr[i], &arr[largest]);

		max_heapify(arr, largest);
	}
}

int hs_tmain(int argc, _TCHAR* argv[])
{
	// ¹¹½¨¶Ñ

	return 0;
}
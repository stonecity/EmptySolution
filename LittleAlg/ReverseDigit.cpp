
#include "stdafx.h"
#include <iostream>
using namespace std;

int arr[3];

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;
using std::vector;
void reverse(int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void printer(int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}

	cout << endl;
}

void perm(int i, int len)
{
	if (i < len)
	{
		for (int j = i; j < len; j++)
		{
			reverse(i, j);
			perm(i + 1, len);
			reverse(j, i);
		}
	}
	else
	{
		printer(len);
	}
}

void AllOrders(int *arrays, int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = arrays[i];
	}

	for (int i = 0; i < len; i++)
	{
		reverse(0, i);
		perm(1, len);
		reverse(i, 0);
	}
}

int rev_tmain(int argc, _TCHAR* argv[])
{
	int arrs[] = { 1, 2, 3, 4 };
	// 计算数组长度
	int len = sizeof(arrs) / sizeof(int);

	AllOrders(arrs, len);

	return 0;
}


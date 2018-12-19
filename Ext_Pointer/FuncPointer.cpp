#include "stdafx.h"
#include <iostream>

const double *f1(const double arr[], int n);
const double *f2(const double [], int);
const double *f3(const double *, int);
void foo(void);

typedef void (*pfn)(void);

int Add(int a, int b)
{
	int sum;
	sum = a + b;
	return sum;
}

int a_tmain(int argc, _TCHAR* argv[])
{
	// 查看函数调用反汇编
	int z;
	z = Add(1, 2);
	printf("%d", z);

	double funArr[3] = { 112, 349, 66};

	const double *(*p1)(const double *, int) = f1;
	auto p2 = f2;

	std::cout << "Using Function Pointer, Address Value:" << std::endl;
	std::cout << (*p1)(funArr, 3) << ": " << *(*p1)(funArr, 3) << std::endl;
	std::cout << p2(funArr, 3) << ": " << *p2(funArr, 3) << std::endl;

	const double *(*pa[3])(const double *, int) = { f1, f2, f3};
	auto pb = pa;

	std::cout << "Using an array pointer to function, Address Value:" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		std::cout << pb[i](funArr, 3) << ": " << *pb[i](funArr, 3) << std::endl;
	}

	pfn fun = foo;
	fun();
	(*fun)();

	system("pause");

	return 0;
}

const double *f1(const double ar[], int n)
{
	return ar;
}

const double *f2(const double ar[], int n)
{
	return ar + 1;
}

const double *f3(const double ar[], int n)
{
	return ar + 2;
}

void foo(void)
{
	std::cout << "typedef func..." << std::endl;
}
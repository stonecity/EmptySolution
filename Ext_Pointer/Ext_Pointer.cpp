// Ext_Pointer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

// 慎用using namespace std,这将会导致include的文件增大
//using namespace std;

class Point
{
public:
	Point(){}

	Point(int a)
	{
		this->age = a;
	}

	void print()
	{
		std::cout << "my test--Point p & new Point" << std::endl;
	}

	void TestConstPointer()
	{
		const char* name = "cheng";		//指向常量的普通指针(常量不能变)
		//name[2] = 'a';
		name = "lee";
		std::cout << name << std::endl;

		char *const space = "cheng";	//常量指针(指针不能变)
		//space[2] = 'b';    
		//space = "lee";
		std::cout << space << std::endl;
		
		void* m = malloc(10 * 1000 * 1000 * 1000);
		if (m != nullptr)
		{
			std::cout << "Malloc OK...." << std::endl;
		}
	}

	inline bool operator ==(const Point &ps) const
	{
		if (this->age == ps.age)
			return true;
		return false;
	}

private:
	int inches;
	int age;
};

double betsky(int* lns)
{
	return 0.05 * (*lns);
}

double pam(int* lns)
{
	return 2 * 0.25 * (*lns);
}

// 使用函数指针
void estimate(int* lines, double(*pf)(int*))
{
	std::cout << *lines << " lines will take ";
	std::cout << (*pf)(lines) << " days" << std::endl;
}

int abcd_tmain(int argc, _TCHAR* argv[])
{
	/*
	unsigned char ax1 = -1;
	signed char ax2 = 255;
	std::cout << (int)ax1 << "  " << (int)ax2 << std::endl;
	*/

	char ch[5] = "list";
	const char* pStr1 = ch;

	//*pStr1 = "strong";  //error
	pStr1 = "sun";

	char chr[5] = "list";
	char* const pStr2 = chr;

	//pStr2 = "strong";	//error
	*pStr2 = 's';

	Point *pt = new Point;
	pt->print();
	pt->TestConstPointer();

	Point p;
	p.print();

	Point *xp = nullptr;
	delete xp;

	Point p1(20);
	Point p2(20);
	if (p1 == p2)
	{
		std::cout << "the age is equal!" << std::endl;
	}

	int *aaa = new int;

	int a = 10;
	int *b = (int*)20; // 将一个地址赋给*b
	// 如果这里使用*b会出错，不是一个有效的内存地址
	std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxx " << b << std::endl;

	int iArray[5] = { 1, 3, 5, 6, 9 };
	int a1 = *(iArray + 4);  // Array and Pointer
	std::cout << a1 << std::endl;

	int *ptr = (int*)(&iArray + 1);
	std::cout << &iArray << "   " << *(ptr - 1) << std::endl;

	int *ptr1 = new int[3];
	auto ptr2 = ptr1;
	*ptr1 = 1;
	*(ptr1 + 1) = 55;
	*(ptr1 + 2) = 66;
	// 发生了undefined behavior, 下面的输出和预想的不一样(Side effects)
	std::cout << "Cout: " << *ptr1 << " " << *ptr1++ << std::endl;
	delete ptr2;

	int *pint = NULL;
	void *pvoid = NULL;
	pvoid = pint;

	// 函数指针：函数名可以做参数传递
	int lines;
	std::cout << "How manys lines of code do you needs?\n";
	std::cin >> lines;
	std::cout << "betsky's estimate： ";
	estimate(&lines, betsky);
	std::cout << "   pam's estimate： ";
	estimate(&lines, pam);

	// 输出字符串信息
	char *s = "xyz";
	printf("%c\n", s[1]);
	printf("%c\n", *(s + 1));
	printf("%s\n", s + 1);
	printf("%c\n", *s + 2);

	return 0;
}


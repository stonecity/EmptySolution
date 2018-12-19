// Copy_Constructor.cpp : 定义控制台应用程序的入口点。
// 使用拷贝构造函数

#include "stdafx.h"
#include <iostream>

class Internet
{
public:
	Internet(char *name, char *address)
	{
		// 省略参数检查...
		std::cout << "Loading Constructor" << std::endl;
		strcpy(m_name, name);
		strcpy(m_address, address);
		pname = new char[strlen(name) + 1];
		if (pname != NULL)
			strcpy(pname, name);
	}

	// Copy Constructor
	Internet(Internet &temp)
	{
		std::cout << "Loading Copy Constructor" << std::endl;
		strcpy(m_name, temp.m_name);
		strcpy(m_address, temp.m_address);
		pname = new char[strlen(m_name) + 1];
		if (pname != NULL)
			strcpy(pname, m_name);
	}

	~Internet()
	{
		std::cout << "Destructor: " << pname<< std::endl;
		delete[] pname;
	}
	
	void Show();

protected:
	char m_name[20];
	char m_address[30];
	char *pname;
};

void Internet::Show()
{
	std::cout << "Show Function: " << m_name << ": " << m_address << " " << pname << std::endl;
}

void Test(Internet it)
{
	std::cout << "运行test函数" << std::endl;
}

void TestReference(const int &p)
{
	std::cout << "Test Reference: " << p << std::endl;
}

int c_tmain(int argc, _TCHAR* argv[])
{
	std::cout << "=====Executing Constructor with Parameters" << std::endl;
	Internet inet("emptysln", "0.1.1.1");

	std::cout << "=====Executing COPY Constructor" << std::endl;
	Internet b = inet;

	std::cout << "=====Executing Show Function" << std::endl;
	b.Show();

	std::cout << "=====Executing Test Function" << std::endl;
	// 注意: 在运行Test函数时，执行了一次拷贝构造函数
	Test(b);

	//运行结束时调用析构函数

	// Note: initial value of reference to non-const must be lvalue
	TestReference(2);

	return 0;
}


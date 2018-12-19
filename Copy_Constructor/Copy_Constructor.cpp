// Copy_Constructor.cpp : �������̨Ӧ�ó������ڵ㡣
// ʹ�ÿ������캯��

#include "stdafx.h"
#include <iostream>

class Internet
{
public:
	Internet(char *name, char *address)
	{
		// ʡ�Բ������...
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
	std::cout << "����test����" << std::endl;
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
	// ע��: ������Test����ʱ��ִ����һ�ο������캯��
	Test(b);

	//���н���ʱ������������

	// Note: initial value of reference to non-const must be lvalue
	TestReference(2);

	return 0;
}


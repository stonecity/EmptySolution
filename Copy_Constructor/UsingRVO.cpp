#include "stdafx.h"
#include "RatedPlayer.h"

#include <stdlib.h>
#include <iostream>
#include <memory>

using namespace std;

class Dog {
public:
	Dog()
	{
		cout << "I in Dog Constructor" << endl;
	}

	Dog(const Dog& dog)
	{
		cout << "I am in Dog copy Constructor" << endl;
	}

	~Dog()
	{
		cout << "~Dog Destructor" << endl;
	}

	void PrintSomething()
	{
		cout << "Printing something..." << endl;
	}
};

Dog getDog() 
{
	// 使用auto_ptr<T>智能指针,不推荐使用,很容易出现使用不当导致内存泄露
	std::auto_ptr<Dog> dg(new Dog());
	if (dg.get())
	{
		// auto_ptr不能使用operator=
		auto_ptr<Dog> dg2;
		dg2 = dg; // dg2剥夺了dg的对象所有权,dg变成了悬空指针
		dg2->PrintSomething();
		//dg->PrintSomething(); // error: 访问悬空指针将会出错
	}

	unique_ptr<Dog> dg1(new Dog());
	if (dg1.get())
	{
		unique_ptr<Dog> dg3;
	}

	// 使用shared_ptr<T>智能指针
	std::shared_ptr<Dog> g(new Dog());
	if (g.get())
	{
		std::shared_ptr<Dog> g2;
		g2 = g;
		g2->PrintSomething();
		g->PrintSomething();
	}

	// 使用weak_ptr<T>智能指针
	std::weak_ptr<Dog> g_weak;
	cout << "g_weak reference_count" << g.use_count() << endl;
	g_weak = g;
	cout << "g_weak reference_count" << g.use_count() << endl;

	std::shared_ptr<Dog> sArray(Dog[10]);

	Dog d = Dog();
	auto *temp_d = new Dog();

	return d;
}

class CMyString
{
public:
	// 构造函数
	CMyString(const char *pszSrc = NULL)
	{
		cout << "CMyString(const char *pszSrc = NULL)" << endl;
		if (pszSrc == NULL)
		{
			m_pData = new char[1];
			*m_pData = '\0';
		}
		else
		{
			m_pData = new char[strlen(pszSrc) + 1];
			strcpy(m_pData, pszSrc);
		}
	}

	// 拷贝构造函数
	CMyString(const CMyString &s)
	{
		cout << "CMyString(const CMyString &s)" << endl;
		m_pData = new char[strlen(s.m_pData) + 1];
		strcpy(m_pData, s.m_pData);
	}

	// move(右值引用)构造函数
	CMyString(CMyString &&s)
	{
		cout << "CMyString(CMyString &&s)" << endl;
		m_pData = s.m_pData;
		s.m_pData = NULL;
	}

	// 析构函数
	~CMyString()
	{
		cout << "~CMyString()" << endl;
		delete[] m_pData;
		m_pData = NULL;
	}

	// 拷贝赋值函数
	CMyString &operator =(const CMyString &s)
	{
		cout << "CMyString &operator =(const CMyString &s)" << endl;
		if (this != &s)
		{
			delete[] m_pData;
			m_pData = new char[strlen(s.m_pData) + 1];
			strcpy(m_pData, s.m_pData);
		}

		return *this;
	}

	// move赋值函数
	CMyString& operator =(CMyString&& s)
	{
		cout << "CMyString &operator =(CMyString &&s)" << endl;
		if (this != &s)
		{
			delete[] m_pData;
			m_pData = s.m_pData;
			s.m_pData = NULL;
		}

		return *this;
	}

private:
	char *m_pData;
};

int _tmain(int argc, char** argv)
{
	char ss[] = { 'a', 'b', 'c' };
	cout << strlen(ss) << endl;

	Dog d = getDog();

	system("pause");

	RatedPlayer *rp = new RatedPlayer(2);
	rp->Rate(20);

	return 0;
}
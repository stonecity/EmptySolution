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
	// ʹ��auto_ptr<T>����ָ��,���Ƽ�ʹ��,�����׳���ʹ�ò��������ڴ�й¶
	std::auto_ptr<Dog> dg(new Dog());
	if (dg.get())
	{
		// auto_ptr����ʹ��operator=
		auto_ptr<Dog> dg2;
		dg2 = dg; // dg2������dg�Ķ�������Ȩ,dg���������ָ��
		dg2->PrintSomething();
		//dg->PrintSomething(); // error: ��������ָ�뽫�����
	}

	unique_ptr<Dog> dg1(new Dog());
	if (dg1.get())
	{
		unique_ptr<Dog> dg3;
	}

	// ʹ��shared_ptr<T>����ָ��
	std::shared_ptr<Dog> g(new Dog());
	if (g.get())
	{
		std::shared_ptr<Dog> g2;
		g2 = g;
		g2->PrintSomething();
		g->PrintSomething();
	}

	// ʹ��weak_ptr<T>����ָ��
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
	// ���캯��
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

	// �������캯��
	CMyString(const CMyString &s)
	{
		cout << "CMyString(const CMyString &s)" << endl;
		m_pData = new char[strlen(s.m_pData) + 1];
		strcpy(m_pData, s.m_pData);
	}

	// move(��ֵ����)���캯��
	CMyString(CMyString &&s)
	{
		cout << "CMyString(CMyString &&s)" << endl;
		m_pData = s.m_pData;
		s.m_pData = NULL;
	}

	// ��������
	~CMyString()
	{
		cout << "~CMyString()" << endl;
		delete[] m_pData;
		m_pData = NULL;
	}

	// ������ֵ����
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

	// move��ֵ����
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
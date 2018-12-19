#include "stdafx.h"
#include <iostream>
#include <memory>

#include "TableTennisPlayer.h"
#include "RatedPlayer.h"
#include "NullPtrException.cpp"

using std::cout;
using std::endl;

class A
{
public:
	A() { cout << "A" << endl; }

	~A() { cout << "~A" << endl; }
};

class B : public A
{
public:
	B(){}
	B(A &a) : _a(a)
	{
		cout << "B" << endl;
	}

	~B() { cout << "~B" << endl; }

private:
	A _a;
};

// ����CPP�̳е���Ϊ
void PrintInheritance()
{
	// A a;       //����a��ʱ�������һ�ι��캯��
	// B b(a);    //����b�����_a��ͨ����Ա��ʼ���б���������
	// ������ͨ��copy constructor����,��b�ĳ�Ա����_a�ģ�������Ĭ��.
	// ����ڹ����_aǰ���ȵ��û��๹�캯��
    // Ȼ����ǹ�������,˳�����A()->_a->B()���ֲ���
    // �������������A,һ��B

    /*****************����������������ջ�ϴ����ģ��������˳�����������ʱ���Զ�����destructor********************/
    /*�����ǰ��ն������ķ�˳�����ģ�����ͬһ�������չ���ķ�˳�����ģ����������
    ����bȻ�����a����ôb�Ĺ���˳���������A()->_a->B()���ֲ�����������������B()���ֲ���->_a->A()
    ��˵õ��ľ���~B->~A->~A
    ��b֮���������a
    ��������� ~B->~A->~A->~A
	*/

	cout << "===============Separate==============" << endl;
	std::shared_ptr<A> bb = std::shared_ptr<A>(new B);
	//delete bb;

	//A *x = new B[10];
}

void TestInherit1()
{
	TableTennisPlayer player1("Beckham", "David", true);
	TableTennisPlayer player2("Yining", "Zhang", false);
	
	player1.Name();
	if (player1.HasTable())
	{
		cout << " has a table." << endl;
	}
	else
	{
		cout << " hasn't a table." << endl;
	}
	
	player2.Name();
	if (player2.HasTable())
	{
		cout << " has a table." << endl;
	}
	else
	{
		cout << " hasn't a table." << endl;
	}	
}

void TestInherit2()
{
	cout << "Test Inheritance 2: " << endl;
	TableTennisPlayer player1("Tara", "Boomdea", false);
	RatedPlayer rplayer1(1140, "Mallory", "Duck", true); 

	rplayer1.Name();
	if (rplayer1.HasTable())
	{
		cout << ": has a table." << endl;
	}
	else
	{
		cout << ": hasn't a table." << endl;
	}

	player1.Name();
	if (player1.HasTable())
	{
		cout << ": has a table" << endl;
	}
	else
	{
		cout << ": hasn't a table." << endl;
	}

	cout << "Name: ";
	rplayer1.Name();

	cout << "; Rating: " << rplayer1.Rating() << endl;

	RatedPlayer rplayer2(1212, player1);
	cout << "Name: ";
	rplayer2.Name();
	cout << "; Rating: " << rplayer2.Rating() << endl;

	TableTennisPlayer& rt = rplayer1;
	TableTennisPlayer* pt = &rplayer1;
	rt.Name();
	pt->Name();
}

int b_tmain(int argc, _TCHAR* argv[])
{
	PrintInheritance();
	TestInherit1();
	TestInherit2();

	// Test nullptr exception
	// ���ᴥ����ָ���쳣��û��foo()�����thisָ�������
	// foo()����virtual��.
	NullPtrTest *nullTest = nullptr;
	nullTest->foo();

	/**
	* using std::string
	*/
	std::string line("hello world!");
	for (auto &c : line)
	{
		c = toupper(c);
	}

	cout << line << endl;

	for (decltype(line.size()) i = 0; i != line.size() && !isspace(line[i]); i++)
	{
		line[i] = toupper(line[i]);
	}

	const string hexDigits = "0123456789ABCDEF";
	cout << "Enter a series of number between 0 and 15 seperated by"
		<< " spaces. Hit ENTER when finished." << endl;
	string result;
	string::size_type n;
	while (cin >> n)
	{
		if (n < hexDigits.size())
		{
			result += hexDigits[n];
		}

		if (n == 0x0D)
		{
			break;
		}
	}

	cout << "Your hex number is " << result << endl;

	int punctCount = 0;
	std::string word;
	while (cin >> word)
	{
		cout << word << endl;
		for (auto c : word)
		{
			if (ispunct(c))
			{
				punctCount++;
			}
		}

		cout << punctCount << " punctation characters in '" << word << "'" << endl;
	}

	return 0;
}

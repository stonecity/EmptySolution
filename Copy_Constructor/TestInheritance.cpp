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

// 测试CPP继承的行为
void PrintInheritance()
{
	// A a;       //定义a的时候调用了一次构造函数
	// B b(a);    //这里b里面的_a是通过成员初始化列表构造起来的
	// 而且是通过copy constructor构造,是b的成员对象_a的，编译器默认.
	// 因此在构造好_a前，先调用基类构造函数
    // 然后才是构造自身,顺序就是A()->_a->B()（局部）
    // 因此这里有两个A,一个B

    /*****************上面两个对象是在栈上创建的，所以在退出函数作用域时会自动调用destructor********************/
    /*析构是按照定义对象的反顺序来的，而且同一个对象按照构造的反顺序来的，因此这里先
    析构b然后才是a，那么b的构造顺序是上面的A()->_a->B()（局部），反过来，就是B()（局部）->_a->A()
    因此得到的就是~B->~A->~A
    在b之后就是析构a
    最后结果就是 ~B->~A->~A->~A
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
	// 不会触发空指针异常，没有foo()里面对this指针解引用
	// foo()不是virtual的.
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

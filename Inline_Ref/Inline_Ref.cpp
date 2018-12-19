// Inline_Ref.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <string>

#define A(x) x;x;x;x;x;x;x;x;x;x; 
using namespace std;
 
string modifiable_rvalue() {
    return "cute";
}

const string const_rvalue() {
    return "fluffy";
}

void TestConstReference() 
{
    string modifiable_lvalue("kittens");
    const string const_lvalue("hungry hungry zombies");

    string& a = modifiable_lvalue;          // Line 16
    //string& b = const_lvalue;               // Line 17 - ERROR
    string& c = modifiable_rvalue();        // Line 18 - ERROR
    //string& d = const_rvalue();             // Line 19 - ERROR

    const string& e = modifiable_lvalue;    // Line 21
    const string& f = const_lvalue;         // Line 22
    const string& g = modifiable_rvalue();  // Line 23
    const string& h = const_rvalue();       // Line 24
 
    //string&& i = modifiable_lvalue;         // Line 26
    //string&& j = const_lvalue;              // Line 27 - ERROR
    string&& k = modifiable_rvalue();       // Line 28
    //string&& l = const_rvalue();            // Line 29 - ERROR
 
    //const string&& m = modifiable_lvalue;   // Line 31
    //const string&& n = const_lvalue;        // Line 32
    const string&& o = modifiable_rvalue(); // Line 33
    const string&& p = const_rvalue();      // Line 34
}

class UDT
{
	int data[100];  
public:
	UDT()
	{
		printf("construct\n");
	}

	UDT(const UDT& udt)
	{
		printf("copy constructor...\n");
	}

	UDT& operator = (const UDT& )
	{
		printf("operator =\n");
		return *this;
	}  
};

UDT foo()  
{
	//UDT a = UDT();
	//return a;
	UDT b;
	return b; //UDT();  
}

// �ж�������������д���Ǹ��Ƿ������С���Ǹ���
void isInclude()
{
	long int j, m = 1, n, x, k;
	cout << "Please input two integer numbers: \n";
	cin >> n >> m;

	// �������ĵ�һ�����ȵڶ������󣬽������������û�
	if(n > m)
	{
		k = n;
		n = m;
		m = k;
	}

	k = n;
	x = m;

	while (x)
	{
		j = 10;
		while (k / 10)
		{
			k /= 10;
			j *= 10;
		}

		if ((x - n) % j == 0)
		{
			cout << "True";
			break;
		}
		else
		{
			x /= 10;
		}
	}

	if (x == 0)
	{
		cout << "False";
	}

	cout << endl;
}

inline double cal_square(double num)
{
	return num * num;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// ִ�����������ᵼ�µ������ι��캯����һ���������������Ǳ����������RVO�Ż���
	// �Զ��������ĳ���ֵ���ô���.
	UDT x1 = foo();
	/*UDT obj = x1;
	UDT udt1;
	udt1 = obj;*/

	TestConstReference();
	isInclude();

	double result = cal_square(5);
	cout << "result = " << result << endl;

	//��������ָ��ͬһ����ַ��һ�����е�һ���޸�����һ��Ҳ�ᱻ�޸ġ�
	int a = 3;
	int & b = a;
	a++;
	cout << "ret=" << &a <<"  ref=" << &b << endl;
	cout << a <<" and "<< b << endl;

	//precision
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(4);
	cout << 77.5434113 << endl;
	

	char *str[] = { "welcome","to","boyaa","shenzhen" };
	char**p = str + 1;

	str[0] = (*p++) + 1;
	str[1] = *(p + 1);
	str[2] = p[1] + 3;
	cout << str[2] - str[1] << endl;

	str[3] = p[0] + (str[2] - str[1]);
	cout << str[0] << " " << str[1] << " " << str[2] << " " << str[3] << endl;


	system("pause");

	return 0;
}


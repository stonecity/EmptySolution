// StoneLexer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Lexer.h"
#include "ListLexer.h"
using namespace std;

void Test()
{
	
}

int a_tmain(int argc, _TCHAR* argv[])
{
	int a = 258; // FF FF FF FF
	int *p = &a;
	char *c = (char*)p;
	cout << "Test char* to int*: " << (int)(*c) << endl;

	*p = 12;

	return 0;
}


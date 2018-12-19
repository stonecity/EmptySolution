// StringContains.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

void LoopMove(char *pStr, int steps)
{
	int n = strlen(pStr) - steps;
	char tmp[100];
	strcpy(tmp, pStr + n);
	strcpy(tmp + steps, pStr);
	*(tmp + strlen(pStr)) = '\0';
	strcpy(pStr, tmp);
}

int a;

int _tmain(int argc, _TCHAR* argv[])
{
	char pstr[] = "abcdefghi";
	LoopMove(pstr, 2);
	cout << pstr << endl;

	*(pstr + 1) = 99;

	int i;
	unsigned char *c;
	a = 5;
	c = ((unsigned char *)0x0040815B); // 0040D788;
	for (i = 0; i < 10; i++)
	{
		printf("%02X ", *c);
		c++;
	}

	printf("\n");

	return 0;
}


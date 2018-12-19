#include "stdafx.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int ShowDemo(char* msg, ...)
{
	va_list ap;
	va_start(ap, msg);
	
	char* para;
	for (int i = 0; i < 4; i++)
	{
		para = va_arg(ap, char*);
		printf("Parameter #%d is: %s\n", i, para);
	}

	va_end(ap);
	return 0;
}

int main()
{
	Demo("DEMO", "This", "a", "b", "c");

	system("pause");
	exit(0);

	return 0;
}
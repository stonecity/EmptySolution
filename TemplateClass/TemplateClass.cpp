// TemplateClass.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "QueueItem.h"
#include "QueueItem.cpp"
#include <iostream>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Queue<int> intq;
	for(int i = 0; i < 10; ++i)
	{
		intq.push(i);
	}

	cout << intq.head->next->item << endl;

	return 0;
}


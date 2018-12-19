// SimulateInput.cpp : �������̨Ӧ�ó������ڵ㡣
// ģ����̼����û��������

#include "stdafx.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <Windows.h> 
#include <Winuser.h> 
#include <iostream>
using namespace std;

/* ---------------------------------- 
simulation of Alt-PrintScreen to get current Window image 
* -----------------------------------*/ 
void SnapWin_2_clipboard() 
{ 
	//keybd_event(VK_LMENU, 0, 0, 0); //  ������ 
	keybd_event(VK_SNAPSHOT, 0, 0, 0); //  PrintScreen 
	keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0); // ������
	//keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0); // ������ 
}

int _tmain(int argc, _TCHAR* argv[])
{
	SnapWin_2_clipboard();
	cout << "Snap successfully window image." << endl;

	// Clock Time
	long i = 100000000L;
	clock_t start, finish;
	double costTimes;
	cout << "Cost Times: ";
	
	start = clock();
	
	while (i--)
	{
		// empty
	}

	finish = clock();
	costTimes = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << costTimes << " seconds" << endl;

	return 0;
}


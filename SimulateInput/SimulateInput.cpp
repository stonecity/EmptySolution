// SimulateInput.cpp : 定义控制台应用程序的入口点。
// 模拟键盘键的敲击输入操作

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
	//keybd_event(VK_LMENU, 0, 0, 0); //  鼠标左键 
	keybd_event(VK_SNAPSHOT, 0, 0, 0); //  PrintScreen 
	keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0); // 键弹上
	//keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0); // 键弹上 
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


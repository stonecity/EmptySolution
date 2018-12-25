// TestFindFile.cpp
// ʹ��Windows API���ļ�ϵͳ����ָ�����ļ���

#include "stdafx.h"
#include <stdio.h> 
#include <windows.h> 
#include <iostream>
using namespace std;

BOOL IsRoot(LPCTSTR lpszPath)
{
	TCHAR szRoot[4];
	wsprintf(szRoot, _T("%c:\\"), lpszPath[0]);
	return (lstrcmp(szRoot, lpszPath) == 0);
}

void FindInAll(::LPCTSTR lpszPath)
{
	TCHAR szFind[MAX_PATH];
	lstrcpy(szFind, lpszPath);
	if (!IsRoot(szFind))
		lstrcat(szFind, _T("\\"));
	lstrcat(szFind, _T("*.*")); // �������ļ� 

	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(szFind, &wfd);

	if (hFind == INVALID_HANDLE_VALUE) // ���û���ҵ������ʧ�� 
		return;

	do
	{
		if (wfd.cFileName[0] == '.')
			continue; // ����������Ŀ¼ 
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			TCHAR szFile[MAX_PATH];
			if (IsRoot(lpszPath))
				wsprintf(szFile, _T("%s%s"), lpszPath, wfd.cFileName);
			else
				wsprintf(szFile, _T("%s\\%s"), lpszPath, wfd.cFileName);

			FindInAll(szFile); // ����ҵ�����Ŀ¼��������Ŀ¼���еݹ� 
		}
		else
		{
			TCHAR szFile[MAX_PATH];
			if (IsRoot(lpszPath))
				wsprintf(szFile, _T("%s%s"), lpszPath, wfd.cFileName);
			else
				wsprintf(szFile, _T("%s\\%s"), lpszPath, wfd.cFileName);

			wcout.imbue(locale("chs"));
			wcout << szFile << endl;	//������
		}
	} while (FindNextFile(hFind, &wfd));

	FindClose(hFind); // �رղ��Ҿ�� 
}

int l_tmain(int argc, char* argv[]) 
{ 
	FindInAll(_T("E:\\")); 
	
	return 0; 
}
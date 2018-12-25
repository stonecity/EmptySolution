// SearchFile.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <afxwin.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <windows.h>
using namespace std;

void ShowErrorMessage(DWORD nErrorID)
{
	LPVOID lpBuffer;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		nErrorID, 0, (LPTSTR)&lpBuffer, 0, NULL);
	wcout.imbue(locale("chs"));
	wcout << (LPTSTR)lpBuffer << endl;
	LocalFree(lpBuffer);
}

BOOL IsBackslash(LPCTSTR lpstr)
{
	int idx = wcslen(lpstr) - 1;
	if (lpstr[idx] == '\\')
		return TRUE;
	return FALSE;
}

void ListAllFiles(LPCTSTR lpPath)
{
	TCHAR szFind[MAX_PATH];
	lstrcpy(szFind, lpPath);
	lstrcat(szFind, _T("\\*.*"));

	WIN32_FIND_DATA  data;
	HANDLE hFindFile = FindFirstFile(szFind, &data);

	if (INVALID_HANDLE_VALUE == hFindFile)
	{
		DWORD dError = GetLastError();
		ShowErrorMessage(dError);
		return;
	}

	do {
		if (data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY
			&& lstrcmp(data.cFileName, _T("."))
			&& lstrcmp(data.cFileName, _T("..")))
		{
			lstrcpy(szFind, lpPath);
			lstrcat(szFind, _T("\\"));
			lstrcat(szFind, data.cFileName);
			ListAllFiles(szFind);
		}

		if (data.cFileName[0] != '.')
		{
			wcout.imbue(locale("chs"));
			wcout << lpPath << _T("\\") << data.cFileName << endl;
		}
	} while (FindNextFile(hFindFile, &data));

	FindClose(hFindFile);
}

void SearchFile(CString pstr)
{
	CFileFind finder;
	CString strWildcard(pstr);

	strWildcard += _T("\\*.*");
	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFileW();
		if (finder.IsDots())
			continue;

		if (finder.IsArchived())
			cout << "----";

		CString sFileName = finder.GetFileName();
		wcout.imbue(locale("chs"));

		wcout << (LPCTSTR)sFileName << endl;
	}

	finder.Close();
}


int _tmain(int argc, _TCHAR* argv[])
{
	//SearchFile(_T("e:"));
	ListAllFiles(_T("E:\\project"));
	return 0;
}


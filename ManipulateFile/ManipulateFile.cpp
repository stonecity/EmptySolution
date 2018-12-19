// ManipulateFile.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>


// ���SourceString�Ƿ�����Pattern��Ϊ��β���ַ���
bool endWith(const char *sourceString, const char *pattern)
{
	if (NULL == sourceString || NULL == pattern)
	{
		return false;
	}

	int patternLen = strlen(pattern);
	int srcLen = strlen(sourceString);

	// ���Դ�ַ�������С��ƥ�䴮���ȣ�ֱ�ӷ���false
	if (srcLen < patternLen)
	{
		return false;
	}

	int i = 0;
	while (i < patternLen)
	{
		if (sourceString[srcLen - i - 1] != pattern[patternLen - i - 1])
		{
			return false;
		}

		i++;
	}

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::string s1 = "xxxx", s2 = "yyy";
	s1 = s2;
	printf("%s\n", s1); // printf��C�еĺ�������֧��C++�е�std::string
	char *s3 = new char[3];
	strcpy(s3, s1.c_str());
	printf("%s\n", s3); // ��printf���C++�ַ�������Ҫת����C�����ַ���

	bool result = endWith("windows.exe", ".exe");
	std::string name = "c:\\download\\simplesection.obj";

	// ����ļ��Ƿ���PE��ʽ
	std::ifstream is(name, std::fstream::binary);
	if (is)
	{
		is.seekg(0, is.end);
		// File length
		int len = is.tellg();

		is.seekg(0, is.beg);

		char *buffer = new char[len];
		is.read(buffer, len);

		if (is)
		{
			//auto old_state = is.rdstate;

			std::cout << "all characters read successfully." << std::endl;
			for (int i = 0; i < len; i++)
			{
				printf("%X ", *(buffer + i));
				if (i != 0 && (i % 15) == 0)
				{
					printf("\n");
				}
			}

			std::cout << std::endl;
		}
		else
		{
			std::cout << "Read error.." << std::endl;
		}

		is.close();

		delete[] buffer;
	}

	system("pause");

	return 0;
}


// ManipulateFile.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>


// 检查SourceString是否是以Pattern作为结尾的字符串
bool endWith(const char *sourceString, const char *pattern)
{
	if (NULL == sourceString || NULL == pattern)
	{
		return false;
	}

	int patternLen = strlen(pattern);
	int srcLen = strlen(sourceString);

	// 如果源字符串长度小于匹配串长度，直接返回false
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
	printf("%s\n", s1); // printf是C中的函数，不支持C++中的std::string
	char *s3 = new char[3];
	strcpy(s3, s1.c_str());
	printf("%s\n", s3); // 用printf输出C++字符串，需要转换成C风格的字符串

	bool result = endWith("windows.exe", ".exe");
	std::string name = "c:\\download\\simplesection.obj";

	// 检查文件是否是PE格式
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


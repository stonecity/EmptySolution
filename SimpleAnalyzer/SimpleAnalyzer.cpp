//SimpleAnalyzer.cpp   Simple词法分析器
//


#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <iostream>

// 保存字符当前位置
char ch;
// 保存关键字
char *keywords[] = { "if", "then", "begin", "end", "while", "do" };
// 存储界符
char *delimiter[] = { "+", "*", "/", "=", "-", ";", ">", "<", "!=", "<=", "=<" };

typedef struct{
	int id;
	char value[20];
}TokenType;

// 保存Token的序列号的数组
TokenType token[40];

// 存储Token序列
int tokenSequence = 0;

// 保存行号
int line = 1;

// 输入了关键字的情况
void MarkKeyword()
{
	char str[20] = { "\0" };   // 初始化为空
	int i, j;
	str[0] = ch;
	ch = getchar();

	// 如果是字母
	for (i = 1; isalpha(ch); i++)		
	{
		str[i] = ch;
		ch = getchar();
	}

	for (j = 0; j < 6; j++)
	{
		// 如果是关键字
		if (strcmp(str, keywords[j]) == 0)     
		{
			token[tokenSequence].id = j + 3;
			strcpy(token[tokenSequence].value, str);
			tokenSequence++;
			return;
		}
	}

	// 如果是数字
	for (; isalnum(ch); i++)

	{
		str[i] = ch;
		ch = getchar();
	}

	token[tokenSequence].id = 1;
	strcpy(token[tokenSequence].value, str);
	tokenSequence++;
	return;
}

// 判断是否是界符
void Delimiter()
{
	// 字符串以'\0'结尾的
	char str[2] = { "\0" };  
	str[0] = ch;
	ch = getchar();
	for (int i = 0; i < 7; i++)
	{
		// 如果是分隔符的情况
		if (strcmp(str, delimiter[i]) == 0)   
		{
			token[tokenSequence].id = i + 9;
			strcpy(token[tokenSequence].value, str);
			tokenSequence++;
			return;
		}
	}
}

// 判断是否是常数
void Constant()
{
	char str[20] = { "\0" };
	str[0] = ch;
	ch = getchar();
	for (int i = 1; isdigit(ch); i++)
	{
		str[i] = ch;
		ch = getchar();
	}

	token[tokenSequence].id = 2;
	strcpy(token[tokenSequence].value, str);
	tokenSequence++;
	return;
}

// 显示分析结果
void display()
{
	std::cout << "\n==================================\n";
	for (int i = 0; i < tokenSequence; i++)
	{
		printf("---[%d]\t%s\t%d\n", i + 1, token[i].value, token[i].id);
	}
}

//输出错误
void error()
{
	std::cout << "Error in Line: " << line << " rows" << std::endl;
}

/*
	检查Stream的前缀是否是Text
    是返回true并将Stream偏移strlen(Text)个字符
    否则返回false 
	此函数会过滤Stream开头的空格
*/
bool Is(char*& stream , const char* text)
{
    size_t len = strlen(text);
    // 保存参数
    char* Read = stream;
    // 过滤空格
	while(*Read==' ') 
	{
		Read++;
	}

    if (strncmp(Read, text, len) == 0)
    {
        stream = Read + len;
        return true;
    }
    else
    {
        return false;
    }           
}

/*
	检查Stream是否操作符
    是的话返回操作符的字符并将Stream偏移至操作符之后
    否则返回
*/
char IsOperator(char*& stream)
{
    /*	
		A||B操作符的特性是如果A==true则不对B求值
		所以表达式会在一个检查成功后停下来
    */
    if (Is(stream, "+") || Is(stream, "-") || Is(stream, "*") || Is(stream, "/"))
    {
        // 此时操作符已经被越过，所以返回Read[-1]
        return stream[-1];
    }
    else
    {
        return 0;
    }        
}


int test_main_c()
{
	char *greets = "   +1 2";
	char s = IsOperator(greets);
	std::cout << s << std::endl;

	std::cout << "hello world: \n";
	ch = getchar();
	while (1)
	{
		if (ch == '.')     //'.'表示程序输入终止
			break;

		if (ch == ' ')
		{
			ch = getchar();
			continue;
		}

		if (ch == '\n')
		{
			ch = getchar();
			line++;
			continue;
		}

		if (isalpha(ch))		//如果是字母
		{
			MarkKeyword();
		}
		else if (isdigit(ch))	//如果是数字
		{
			Constant();
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == ';')
		{
			Delimiter();
		}
		else
		{
			error();
			exit(0);
		}
	}

	display();

	system("pause");

	return 0;
}


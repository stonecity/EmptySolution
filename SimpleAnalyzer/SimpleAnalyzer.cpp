//SimpleAnalyzer.cpp   Simple�ʷ�������
//


#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <iostream>

// �����ַ���ǰλ��
char ch;
// ����ؼ���
char *keywords[] = { "if", "then", "begin", "end", "while", "do" };
// �洢���
char *delimiter[] = { "+", "*", "/", "=", "-", ";", ">", "<", "!=", "<=", "=<" };

typedef struct{
	int id;
	char value[20];
}TokenType;

// ����Token�����кŵ�����
TokenType token[40];

// �洢Token����
int tokenSequence = 0;

// �����к�
int line = 1;

// �����˹ؼ��ֵ����
void MarkKeyword()
{
	char str[20] = { "\0" };   // ��ʼ��Ϊ��
	int i, j;
	str[0] = ch;
	ch = getchar();

	// �������ĸ
	for (i = 1; isalpha(ch); i++)		
	{
		str[i] = ch;
		ch = getchar();
	}

	for (j = 0; j < 6; j++)
	{
		// ����ǹؼ���
		if (strcmp(str, keywords[j]) == 0)     
		{
			token[tokenSequence].id = j + 3;
			strcpy(token[tokenSequence].value, str);
			tokenSequence++;
			return;
		}
	}

	// ���������
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

// �ж��Ƿ��ǽ��
void Delimiter()
{
	// �ַ�����'\0'��β��
	char str[2] = { "\0" };  
	str[0] = ch;
	ch = getchar();
	for (int i = 0; i < 7; i++)
	{
		// ����Ƿָ��������
		if (strcmp(str, delimiter[i]) == 0)   
		{
			token[tokenSequence].id = i + 9;
			strcpy(token[tokenSequence].value, str);
			tokenSequence++;
			return;
		}
	}
}

// �ж��Ƿ��ǳ���
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

// ��ʾ�������
void display()
{
	std::cout << "\n==================================\n";
	for (int i = 0; i < tokenSequence; i++)
	{
		printf("---[%d]\t%s\t%d\n", i + 1, token[i].value, token[i].id);
	}
}

//�������
void error()
{
	std::cout << "Error in Line: " << line << " rows" << std::endl;
}

/*
	���Stream��ǰ׺�Ƿ���Text
    �Ƿ���true����Streamƫ��strlen(Text)���ַ�
    ���򷵻�false 
	�˺��������Stream��ͷ�Ŀո�
*/
bool Is(char*& stream , const char* text)
{
    size_t len = strlen(text);
    // �������
    char* Read = stream;
    // ���˿ո�
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
	���Stream�Ƿ������
    �ǵĻ����ز��������ַ�����Streamƫ����������֮��
    ���򷵻�
*/
char IsOperator(char*& stream)
{
    /*	
		A||B�����������������A==true�򲻶�B��ֵ
		���Ա��ʽ����һ�����ɹ���ͣ����
    */
    if (Is(stream, "+") || Is(stream, "-") || Is(stream, "*") || Is(stream, "/"))
    {
        // ��ʱ�������Ѿ���Խ�������Է���Read[-1]
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
		if (ch == '.')     //'.'��ʾ����������ֹ
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

		if (isalpha(ch))		//�������ĸ
		{
			MarkKeyword();
		}
		else if (isdigit(ch))	//���������
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


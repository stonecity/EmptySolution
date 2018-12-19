#pragma once

#include "stdafx.h"
#include "Lexer.h"
#include "Token.h"

class Parser
{
public:
	Parser(void);
	Parser(Lexer& input, int k);
	~Parser(void);

	void Consume();
	Token* LT(int i);
	int LA(int i);
	void Match(int x);
	void Element();

	// ������ʷ���Ԫ����Դ
	Lexer *input;
	// ���λ�����
	Token *lookahead[100];

	// ��ǰ�����Ÿ���
	int k;
	// ���λ�������װ����һ���ʷ���Ԫ��λ��
	int p;
};


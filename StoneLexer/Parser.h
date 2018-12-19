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

	// 待处理词法单元的来源
	Lexer *input;
	// 环形缓冲区
	Token *lookahead[100];

	// 向前看符号个数
	int k;
	// 环形缓冲区中装填下一个词法单元的位置
	int p;
};


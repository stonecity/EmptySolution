#pragma once

#include "stdafx.h"
#include "lexer.h"
#include "Token.h"

class ListLexer : public Lexer
{
public:
	ListLexer(void);
	ListLexer(std::string);
	~ListLexer(void);

	std::string GetTokenName(int x);
	bool IsLetter();
	Token* NextToken();
	void WS();
	Token* Name();

	static int NAME;
	static int COMMA;
	static int LBRACK;
	static int RBRACK;
	static std::string tokenNames[6];
};


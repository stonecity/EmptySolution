#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>

class Lexer
{
public:
	Lexer(void);
	Lexer(std::string input);
	~Lexer(void);

	void consume();
	void match(char x);
	
	char c;
	static const int EOF_TYPE = -1;

private:
	std::string input;
	int p;
};


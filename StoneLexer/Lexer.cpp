#include "stdafx.h"
#include "Lexer.h"
#include <iostream>

using namespace std;

Lexer::Lexer(void)
{
}

Lexer::Lexer(string input)
{
	this->input = input;
	c = input.at(this->p);
}

Lexer::~Lexer(void)
{
}

void Lexer::consume()
{
	p++;

	if (p >= input.length())
	{
		c = EOF;
	}
	else
	{
		c = input.at(p);
	}
}

void Lexer::match(char x)
{
	if (c == x)
	{
		consume();
	}
	else
	{
		string a(&x, 1);
		string b(&c, 1);
		throw "expecting " + a + "; found " + b;
	}
}


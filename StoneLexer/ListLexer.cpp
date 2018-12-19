#include "stdafx.h"
#include "ListLexer.h"

using namespace std;

int ListLexer::NAME = 2;
int ListLexer::COMMA = 3;
int ListLexer::LBRACK = 4;
int ListLexer::RBRACK = 5;

std::string ListLexer::tokenNames[] = { "n/a", "<EOF>", "NAME", "COMMA", "LBRACK", "RBRACK" };

ListLexer::ListLexer(void)
{
	
}

ListLexer::ListLexer(std::string input) : Lexer(input)
{
}

ListLexer::~ListLexer(void)
{
}

std::string ListLexer::GetTokenName(int x)
{
	// TODO 检查数组索引是否越界
	return tokenNames[x];
}

bool ListLexer::IsLetter()
{
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

void ListLexer::WS()
{
	while (c == ' ' || c == '\t' || c == '\n' || c == '\r')
	{
		consume();
	}
}

Token* ListLexer::Name()
{
	std::string s;

	do{
		s.append(1, c);
		consume();
	} while (IsLetter());

	return new Token(NAME, s);
}

Token* ListLexer::NextToken()
{
	while (c != EOF)
	{
		switch (c)
		{
		case ' ':
		case '\t':
		case '\n':
		case '\r':
			WS();
			continue;
		case ',':
			consume();
			return new Token(COMMA, ",");
		case '[':
			consume();
			return new Token(LBRACK, "[");
		case ']':
			consume();
			return new Token(RBRACK, "]");
		default:
			if (IsLetter())
			{
				return Name();
			}

			throw new exception("Invalid character: " + c);
		}
	}

	return new Token(EOF_TYPE, "<EOF>");
}

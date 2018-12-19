#pragma once

#include "stdafx.h"
#include <string>

class Token
{
public:
	Token(void);
	Token(int type, std::string text);
	~Token(void);

	std::string* ToString();

	int Type;
	std::string Text;
};


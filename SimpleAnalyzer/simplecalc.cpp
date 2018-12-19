#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "token.h"

#define LINE_BUF_SIZE (1024)

static Token st_look_ahead_token;
static int st_look_ahead_exists;

static void my_get_token(Token *token)
{
	if (st_look_ahead_exists)
	{
		*token = st_look_ahead_token;
		st_look_ahead_exists = 0;
	}
	else
	{
		get_token(token);
	}
}

static void unget_token(Token *token)
{
	st_look_ahead_token = *token;
	st_look_ahead_exists = 1;
}

double parser_primary_expression(void);
double parser_expression(void);

static double parser_primary_expression()
{
	double value = 0.0;
	int minus_flag = 0;
	Token token;
	my_get_token(&token);

	if (token.kind == SUB_OPERATOR_TOKEN)
	{
		minus_flag = 1;
	}
	else
	{
		unget_token(&token);
	}

	if (token.kind == NUMBER_TOKEN) 
	{
		return token.value;
	}
	else if (token.kind == LEFT_PAREN_TOKEN)
	{
		value = parser_expression();
		my_get_token(&token);
		if (token.kind != RIGHT_PAREN_TOKEN)
		{
			fprintf(stderr, "missing ')' error.\n");
			exit(1);
		}
	}
	else
	{
		unget_token(&token);
	}

	if (minus_flag)
	{
		value = -value;
	}

	//fprintf(stderr, "syntax error.\n");
	//exit(1);
	
	return value;
}

static double parser_term()
{
	double v1;
	double v2;
	Token token;
	
	v1 = parser_primary_expression();
	for (;;)
	{
		my_get_token(&token);

		if (token.kind != MUL_OPERATOR_TOKEN &&
			token.kind != DIV_OPERATOR_TOKEN) 
		{
			unget_token(&token);
			break;
		}

		v2 = parser_primary_expression();

		if (token.kind == MUL_OPERATOR_TOKEN)
		{
			v1 *= v2;
		}
		else if (token.kind == DIV_OPERATOR_TOKEN)
		{
			v1 /= v2;
		}
	}

	return v1;
}

double parser_expression()
{
	double v1;
	double v2;
	Token token;

	v1 = parser_term();
	for (;;)
	{
		my_get_token(&token);

		if (token.kind != ADD_OPERATOR_TOKEN &&
			token.kind != SUB_OPERATOR_TOKEN)
		{
			unget_token(&token);
			break;
		}

		v2 = parser_term();
		if (token.kind == ADD_OPERATOR_TOKEN)
		{
			v1 += v2;
		}
		else if (token.kind == SUB_OPERATOR_TOKEN)
		{
			v1 -= v2;
		}
		else
		{
			unget_token(&token);
		}
	}

	return v1;
}

double parser_line(void)
{
	double value;

	st_look_ahead_exists = 0;
	value = parser_expression();

	return value;
}

int main(int argc, char **argv)
{
	char line[LINE_BUF_SIZE];
	double value;

	while (fgets(line, LINE_BUF_SIZE, stdin) != NULL)
	{
		set_line(line);
		value = parser_line();
		printf(">>%f\n", value);
	}

	return 0;
}
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"

static char *st_line;
static int st_line_pos;

typedef enum {
	INITIAL_STATUS,
	IN_INT_PART_STATUS,
	DOT_STATUS,
	IN_FRAC_PART_STATUS
} LexerStatus;

void get_token(Token *token)
{
	int out_pos = 0;
	LexerStatus status = INITIAL_STATUS;
	char current_char;

	token->kind = BAD_TOKEN;
	
	while (st_line[st_line_pos] != '\0')
	{
		current_char = st_line[st_line_pos];

		if ((status == IN_INT_PART_STATUS || 
			status == IN_FRAC_PART_STATUS) &&
			!isdigit(current_char) && 
			current_char != '.')
		{
			token->kind = NUMBER_TOKEN;
			sscanf(token->str, "%lf", &token->value);
			return;
		}

		if (isspace(current_char))
		{
			if (current_char == '\n')
			{
				token->kind = END_OF_LINE_TOKEN;
				return;
			}

			st_line_pos++;
			continue;
		}

		if (out_pos >= MAX_TOKEN_SIZE)
		{
			fprintf(stderr, "token too long. \n");
			exit(1);
		}

		token->str[out_pos] = st_line[st_line_pos];
		st_line_pos++;
		out_pos++;
		token->str[out_pos] = '\0';
		
		if (current_char == '+') 
		{
			token->kind = ADD_OPERATOR_TOKEN;
			return;
		}
		else if (current_char == '-')
		{
			token->kind = SUB_OPERATOR_TOKEN;
			return;
		}
		else if (current_char == '*') 
		{
			token->kind = MUL_OPERATOR_TOKEN;
			return;
		}
		else if (current_char == '/')
		{
			token->kind = DIV_OPERATOR_TOKEN;
			return;
		}
		else if (isdigit(current_char))
		{
			if (status == INITIAL_STATUS)
			{
				status = IN_INT_PART_STATUS;
			}
			else if (status == DOT_STATUS)
			{
				status = IN_FRAC_PART_STATUS;
			}
		}
		else if (current_char == '.')
		{
			if (status == IN_INT_PART_STATUS)
			{
				status = DOT_STATUS;
			}
			else
			{
				fprintf(stderr, "syntax error.\n");
				exit(1);
			}
		}
		else
		{
			fprintf(stderr, "bad character(%c)\n", current_char);
			exit(1);
		}
	}
}

void set_line(char *line)
{
	st_line = line;
	st_line_pos = 0;
}

void parse_line(char *buff)
{
	Token token;
	set_line(buff);

	for (;;)
	{
		get_token(&token);
		if (token.kind == END_OF_LINE_TOKEN) 
		{
			break;
		}
		else
		{
			printf("Kind..%d, str..%s\n", token.kind, token.str);
		}
	}
}

int test_main(int argc, char **argv)
{
	char buff[1024];
	while (fgets(buff, MAX_TOKEN_SIZE, stdin) != NULL)
	{
		parse_line(buff);
	}

	return 0;
}
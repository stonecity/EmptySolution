#include "tdb.h"
#include "tvm.h"

#include <stdio.h>

#define TOKEN_LENGTH 32
#define MAX_TOKENS 3
#define MAX_INPUT_LENGTH 256

const char *commands[] = {"q", "run", "break", "step", "continue", 0};

static void tokenize(char *str, char **tokens);
static int cmd_to_idx(char *cmd);

void tdb_shell(tvm_t *vm)
{
	int run = 1, i;
	int running = 0;

	char *tokens[MAX_TOKENS];
	char str[MAX_INPUT_LENGTH];

	int num_breakpoints = 0;
	tdb_breakpoint_t *breakpoints = NULL;

	for(i = 0; i < MAX_TOKENS; i++) tokens[i] = malloc(TOKEN_LENGTH);

        vm->pMemory->registers[0x8].i32 = vm->pProgram->start;

	while(run && !feof(stdin))
	{
		int retcode = 0;

		printf(": ");

		for(i = 0; i < MAX_TOKENS; i++) memset(tokens[i], 0, TOKEN_LENGTH);

		if (!fgets(str, MAX_INPUT_LENGTH, stdin))
			break;
		tokenize(str, (char **)tokens);

		switch(cmd_to_idx(tokens[0]))
		{
			case -0x1: printf("WARNING: \"%s\" is not a valid command.\n", tokens[0]); break;
			case  0x0: run = 0; break;
			case  0x1: if(running) printf("The program is already running.\n");
				   else { retcode = tdb_run(vm, breakpoints, num_breakpoints); running = 1; } break;
			case  0x2: breakpoints = realloc(breakpoints, sizeof(tdb_breakpoint_t) * ++num_breakpoints);
				   breakpoints[num_breakpoints - 1].address = tvm_parse_value(tokens[1]); break;
			case  0x3: tvm_step(vm, &vm->pMemory->registers[0x8].i32);
				   vm->pMemory->registers[0x8].i32++;
				   printf("Advancing instruction pointer to %i\n", vm->pMemory->registers[0x8].i32); break;
			case  0x4: tvm_step(vm, &vm->pMemory->registers[0x8].i32);
				   vm->pMemory->registers[0x8].i32++;
				   retcode = tdb_run(vm, breakpoints, num_breakpoints); break;
		};

		if(vm->pProgram->instr[vm->pMemory->registers[0x8].i32] == -0x1) printf("End of program reached\n");
		if(retcode == 1) printf("Breakpoint hit at address: %i\n", vm->pMemory->registers[0x8].i32);
	}

	free(breakpoints);

	for(i = 0; i < MAX_TOKENS; i++) free(tokens[i]);
}

int tdb_run(tvm_t* vm, tdb_breakpoint_t* breakpoints, int num_breakpoints)
{
	for(int *instr_idx = &vm->pMemory->registers[0x8].i32; vm->pProgram->instr[*instr_idx] != -0x1; ++(*instr_idx))
	{
		for(int i = 0; i < num_breakpoints; i++) if(breakpoints[i].address == *instr_idx) return 1; /* Breakpoint hit */
		tvm_step(vm, instr_idx);
	}

	return 0;
}

void tokenize(char *str, char **tokens)
{
	char *nextToken = NULL;
	char *token = strtok_s(str, " 	\n", &nextToken);
	for (int i = 0; token && (i < MAX_TOKENS); i++)
	{
		strcpy(tokens[i], token);
		token = strtok_s(NULL, " 	\n", &nextToken);
	}
}

int cmd_to_idx(char* cmd)
{
	for(int i = 0; commands[i]; i++)
		if(strcmp(cmd, commands[i]) == 0) return i;

	return -1;
}

#include <stdlib.h>
#include <stdio.h>

#include "tvm.h"

int a_main(int argc, char** argv)
{
	tvm_t* vm = tvm_create();
	if (vm != NULL && tvm_interpret(vm, argv[1]) == 0)
	{
		tvm_run(vm);
	}

	tvm_destroy(vm);

	return 0;
}

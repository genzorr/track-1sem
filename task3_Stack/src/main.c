#include <stdio.h>
#include <stdlib.h>


#include "stack.h"


int main()
{
	//	TODO: make dump ready for data_t type
	//	TODO: stack decrease, hash

	//	TODO: HASH: for struct and for buffer
	//	TODO: CANARY for DATA buffer
	//	TODO: canary and hash by ifdefs

	//	TODO: check alignment

	stack stk = {"stk"};

	int error = StackCtor(&stk);
	if (error)
		return ST_NULL_PTR;

	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 15);
	StackPush(&stk, 50);
	StackPush(&stk, 53);
	StackPush(&stk, 52);
	StackPush(&stk, 51);
	StackPush(&stk, 534);
	StackPush(&stk, -2*POISON);
	printf("popped: %lf\n", StackPop(&stk));
	StackDump(&stk);

	StackClear(&stk);
	StackDump(&stk);

	StackDtor(&stk);

	return 0;
}

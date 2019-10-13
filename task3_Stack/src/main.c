#include <stdio.h>
#include <stdlib.h>


#include "stack.h"


int main()
{
	//	TODO: make dump ready for data_t type

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
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackPush(&stk, 5);
	StackDump(&stk);

	StackDtor(&stk);

	return 0;
}

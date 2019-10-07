#include <stdio.h>
#include <stdlib.h>


#include "stack.h"


int main()
{
	//	TODO: HASH: for struct and for buffer
	//	TODO: CANARY for DATA buffer
	//	TODO: canary and hash by ifdefs

	//	TODO: check alignment

	stack stk = {"stk"};

	int error = StackCtor(&stk);
	if (error)
		return ST_NULL_PTR;

//	st->size = 17;
//	stk.canary2 = 0;
	stk.size = 11;
	stk.data[10] = POISON;
	StackDump(&stk);

	StackDtor(&stk);

	return 0;
}

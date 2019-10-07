#include <stdio.h>
#include <stdlib.h>


#include "stack.h"


int main()
{
	//	TODO: CRC
	stack* st = StackCtor();

	st->size = 17;
	StackDump(st);
//	stack* st_ = st;
	st = NULL;
	StackDump(st);

//	st = st_;
	StackDtor(st);

	return 0;
}

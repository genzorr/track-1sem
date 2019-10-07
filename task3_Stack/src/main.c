#include <stdio.h>
#include <stdlib.h>


#include "stack.h"


int main()
{
	//	TODO: HASH: for struct and for buffer
	//	TODO: CANARY for DATA buffer
	//	TODO: canary and hash by ifdefs

	//	TODO: check alignment

	stack st = {"st"};

	int error = StackCtor(&st);
	if (error)
		return ST_NULL_PTR;

//	st->size = 17;
	st.canary1 = 0;
	st.size = 11;
	st.data[10] = POISON;
	StackDump(&st);

	StackDtor(&st);

	return 0;
}

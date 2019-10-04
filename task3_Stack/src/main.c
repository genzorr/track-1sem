#include <stdio.h>
#include <stdlib.h>


#include "stack.h"


int main()
{
	//	TODO: CRC
	stack* s = StackCtor();

	StackDump(s);
	s = NULL;
	StackDump(s);

	StackDtor(s);

	return 0;
}

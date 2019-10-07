//--------------------------------------------------------------------------------------------
//! @file stack_dump.c
//! Here you can find realization of stack dump's function.
//--------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "stack.h"

#define $_s_ret(x)	(#x)
#define SPACE_LEN	100

char* space_h	= "                              ";
char* space 	= "                                                                                                      ";


int printSpaceStr(char* s, char* end_s, int add_l)
{
	char* end = strchr(s, '\0');

	if (MY_assert(end))
		return -1;

	int len = ((int)end - (int)s);
	printf("%.*s%s", SPACE_LEN - len - 2 - add_l, space, end_s);

	return OK;
}


void StackDump(stack* s)
{
	char str[100] = {};

	printf("\n################################# STACK DUMP ######################################################\n");
	printf("+-------------------------------------------------------------------------------------------------+\n");

	char* response	= NULL;
	char* resp_ok	= "(ok)";
	char* resp_err 	= "(ERROR)";
	char* resp_none = "";
	char* col		= reset_col;

/**///	First line.
	printf("|\t%sStack ", yellow_col);
	sprintf(str, "%s%s:%s", $_s_ret(s), reset_col, space_h);	printf("%.*s", 10+reset_l, str);
	sprintf(str, "[%p]%s", (void**)s, space_h);					printf("%.*s", 20, str);

	int len = 0, state = StackOK(s);
	if (!state)
	{response = resp_ok; 	col = green_col;	len = green_l + reset_l;}
	else
	{response = resp_err; 	col = red_col;		len = red_l + reset_l;}

	sprintf(str, "%s%s%s%s", col, response, reset_col, space_h);	printf("%.*s", 10+len, str);
	printf("%.*s|\n", 44, space);

	if (state == ST_NULL_PTR)
		goto end;

/**///	Info about stack's parameters.
	sprintf(str, "|         size: %ld",	s->size);	printf("%s", str);	printSpaceStr(str, "|\n", 0);

	response = (state == ST_INV_SIZE) ? resp_err : resp_none;
	sprintf(str, "|         capacity: %ld  %s",	s->capacity, response);
	printf("%s", str);	printSpaceStr(str, "|\n", 0);

end:
	printf("+-------------------------------------------------------------------------------------------------+\n");
}

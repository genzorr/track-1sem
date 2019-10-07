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

int getStrLen(char* s)
{
	char* end = strchr(s, '\0');
	if (MY_assert(end))
		return -1;

	return ((int)end - (int)s);
}


void StackDump(stack* s)
{
	char str[100] = {};
	char str_res[100] = {};

	printf("\n################################# STACK DUMP ######################################################\n");
	printf("+-------------------------------------------------------------------------------------------------+\n");

	char* response	= NULL;
	char* resp_none = "";
	char* resp_ok	= "(ok)";
	char* resp_bad 	= "(BAD)";
	char* resp_poison = "(POISON?)";
	char* col		= reset_col;

	int len = 0, len_col = 0;
/**///	First line.
	sprintf(str, "|      %sStack ", yellow_col);				sprintf(str, "%s", str); 		strcat(str_res, str);	len += getStrLen(str);	len_col += yellow_l;
	sprintf(str, "\"%s\"%s:%s", s->name, reset_col, space_h);	sprintf(str, "%.*s", 15, str);	strcat(str_res, str);	len += getStrLen(str);	len_col += reset_l;
	sprintf(str, "[%p]%s", s, space_h); 						sprintf(str, "%.*s", 20, str);	strcat(str_res, str);	len += getStrLen(str);

	int state = StackOK(s);
	if (!state)
	{response = resp_ok; 	col = green_col;	len_col += (green_l + reset_l);}
	else
	{response = resp_bad; 	col = red_col;		len_col += (red_l + reset_l);}

	sprintf(str, "%s%s%s%s", col, response, reset_col, space_h);	sprintf(str, "%.*s", 10+len_col, str);	strcat(str_res, str);	len += getStrLen(str);

	printf("%s%.*s|\n", str_res, SPACE_LEN - (len - len_col) - 2, space);

	if (state == ST_NULL_PTR)
		goto end;

/**///	Stack's parameters.
	sprintf(str, "|        {");	printf("%s%.*s|\n", str, SPACE_LEN - getStrLen(str) - 2, space);

	//	Canary 1.
	len = 0;	memset(str_res, 0, 100);
	response = (state == ST_BAD_CANARY) ? resp_bad : resp_none;
	sprintf(str, "|        --> %scanary1  = 0x%X%s", blue_col, s->canary1, space_h);	sprintf(str, "%.*s", 51, str);	strcat(str_res, str);	len += getStrLen(str);
	sprintf(str, "%s%s%s", red_col, response, reset_col);								sprintf(str, "%.*s", 20, str);	strcat(str_res, str);	len += getStrLen(str);
	printf("%s%.*s|\n", str_res, SPACE_LEN - (len - blue_l - red_l - reset_l) - 2, space);

	//	Size.
	sprintf(str, "|            size     = %ld",	s->size);
	printf("%s%.*s|\n", str, SPACE_LEN - getStrLen(str) - 2, space);

	//	Capacity.
	response = (state == ST_INV_SIZE) ? resp_bad : resp_none;
	sprintf(str, "|            capacity = %ld %s%s%s",	s->capacity, red_col, response, reset_col);
	printf("%s%.*s|\n", str, SPACE_LEN - (getStrLen(str) - red_l - reset_l) - 2, space);

	//	Data.
	len = 0;	memset(str_res, 0, 100);
	response = (state == ST_NULL_DATA_PTR) ? resp_bad : resp_none;
	sprintf(str, "|            data     = [%p]%s", s->data, space_h);	sprintf(str, "%.*s", 40, str);	strcat(str_res, str);	len += getStrLen(str);
	sprintf(str, "%s%s%s", red_col, response, reset_col);				sprintf(str, "%.*s", 20, str);	strcat(str_res, str);	len += getStrLen(str);
	printf("%s%.*s|\n", str_res, SPACE_LEN - (len - red_l - reset_l) - 2, space);


	sprintf(str, "|               {");	printf("%s%.*s|\n", str, SPACE_LEN - getStrLen(str) - 2, space);
	for (int i = 0; i < s->capacity; i++)
	{
		char sign = (i < s->size) ? '*' : ' ';
		len = 0;	memset(str_res, 0, 100);
		response = (s->data[i] == POISON) ? resp_poison : resp_none;
		sprintf(str, "|                %c[%d]%s", sign, i, space_h);	sprintf(str, "%.*s", 25, str);	strcat(str_res, str);	len += getStrLen(str);
		sprintf(str, ": %10.3lf%s", s->data[i], space_h);				sprintf(str, "%.*s", 19, str);	strcat(str_res, str);	len += getStrLen(str);
		sprintf(str, "%s%s%s", yellow_col, response, reset_col);		sprintf(str, "%.*s", 30, str);	strcat(str_res, str);	len += getStrLen(str);
		printf("%s%.*s|\n", str_res, SPACE_LEN - (getStrLen(str_res) - yellow_l - reset_l) - 2, space);
	}
	sprintf(str, "|               }");	printf("%s%.*s|\n", str, SPACE_LEN - getStrLen(str) - 2, space);

	//	Canary 2.
	len = 0;	memset(str_res, 0, 100);
	response = (state == ST_BAD_CANARY) ? resp_bad : resp_none;
	sprintf(str, "|        --> %scanary2  = 0x%X%s", blue_col, s->canary2, space_h);	sprintf(str, "%.*s", 51, str);	strcat(str_res, str);	len += getStrLen(str);
	sprintf(str, "%s%s%s", red_col, response, reset_col);								sprintf(str, "%.*s", 20, str);	strcat(str_res, str);	len += getStrLen(str);
	printf("%s%.*s|\n", str_res, SPACE_LEN - (len - blue_l - red_l - reset_l) - 2, space);


	sprintf(str, "|        }");	printf("%s%.*s|\n", str, SPACE_LEN - getStrLen(str) - 2, space);
end:

	printf("+-------------------------------------------------------------------------------------------------+\n");
}

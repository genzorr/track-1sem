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


void StackDump(stack* stk)
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
	sprintf(str, "\"%s\"%s:%s", stk->name, reset_col, space_h);	sprintf(str, "%.*s", 15, str);	strcat(str_res, str);	len += getStrLen(str);	len_col += reset_l;
	sprintf(str, "[%p]%s", stk, space_h); 						sprintf(str, "%.*s", 20, str);	strcat(str_res, str);	len += getStrLen(str);

	int state = StackOK(stk);
	if (!state)
	{response = resp_ok; 	col = green_col;	len_col += (green_l + reset_l);}
	else
	{response = resp_bad; 	col = red_col;		len_col += (red_l + reset_l);}

	sprintf(str, "%s%s%s%s", col, response, reset_col, space_h);	sprintf(str, "%.*s", 10+len_col, str);	strcat(str_res, str);	len += getStrLen(str);

	printf("%s%.*s|\n", str_res, SPACE_LEN - (len - len_col) - 2, space);

	if (state & ST_NULL_PTR)
		goto end;

/**///	Stack's parameters.
	sprintf(str, "|        {");	printf("%s%.*s|\n", str, SPACE_LEN - getStrLen(str) - 2, space);

	//	Canary 1.
	len = 0;	memset(str_res, 0, 100);
	response = (state & ST_BAD_CANARY1) ? resp_bad : resp_none;

	sprintf(str, "|        --> %scanary1  = 0x%X%s", blue_col, stk->canary1, space_h);	sprintf(str, "%.*s", 51, str);	strcat(str_res, str);	len += getStrLen(str);
	sprintf(str, "%s%s%s", red_col, response, reset_col);								sprintf(str, "%.*s", 20, str);	strcat(str_res, str);	len += getStrLen(str);
	printf("%s%.*s|\n", str_res, SPACE_LEN - (len - blue_l - red_l - reset_l) - 2, space);


	//	Size.
	sprintf(str, "|            size     = %ld",	stk->size);
	printf("%s%.*s|\n", str, SPACE_LEN - getStrLen(str) - 2, space);


	//	Capacity.
	len = 0;	memset(str_res, 0, 100);
	response = (state & ST_INV_SIZE) ? resp_bad : resp_none;

	sprintf(str, "|            capacity = %ld%s", stk->capacity, space_h);	sprintf(str, "%.*s", 44, str);	strcat(str_res, str);	len += getStrLen(str);
	sprintf(str, "%s%s%s", red_col, response, reset_col);					sprintf(str, "%.*s", 20, str);	strcat(str_res, str);	len += getStrLen(str);
	printf("%s%.*s|\n", str_res, SPACE_LEN - (len - red_l - reset_l) - 2, space);


	//	Data.
	len = 0;	memset(str_res, 0, 100);
	response = (state & ST_NULL_DATA_PTR) ? resp_bad : resp_none;

	sprintf(str, "|            data     = [%p]%s", stk->data, space_h);	sprintf(str, "%.*s", 40, str);	strcat(str_res, str);	len += getStrLen(str);
	sprintf(str, "%s%s%s", red_col, response, reset_col);				sprintf(str, "%.*s", 20, str);	strcat(str_res, str);	len += getStrLen(str);
	printf("%s%.*s|\n", str_res, SPACE_LEN - (len - red_l - reset_l) - 2, space);

	sprintf(str, "|               {");	printf("%s%.*s|\n", str, SPACE_LEN - getStrLen(str) - 2, space);

	len = 0;	memset(str_res, 0, 100);
	response = (state & ST_BAD_CANARYDATA) ? resp_bad : resp_none;
	char value_s[20] = {};
	sprintf(value_s, $value, stk->data[0]);
	sprintf(str, "|               %scanary  = %s%s", blue_col, value_s, space_h);				sprintf(str, "%.*s", 51, str);	strcat(str_res, str);	len += getStrLen(str);
	sprintf(str, "%s%s%s", red_col, response, reset_col);									sprintf(str, "%.*s", 20, str);	strcat(str_res, str);	len += getStrLen(str);
	printf("%s%.*s|\n", str_res, SPACE_LEN - (len - blue_l - red_l - reset_l) - 2, space);

	for (int i = 0; i < stk->capacity; i++)
	{
		char sign = (i < stk->size) ? '*' : ' ';
		data_t value = *(stk->data+i+1);
		response = (value == POISON) ? resp_poison : resp_none;

		len = 0;	memset(str_res, 0, 100);
		sprintf(value_s, $value, value);
		sprintf(str, "|                %c[%d]%s", sign, i, space_h);	sprintf(str, "%.*s", 24, str);	strcat(str_res, str);	len += getStrLen(str);
		sprintf(str, ": %s%s", value_s, space_h);						sprintf(str, "%.*s", 20, str);	strcat(str_res, str);	len += getStrLen(str);
		sprintf(str, "%s%s%s", yellow_col, response, reset_col);		sprintf(str, "%.*s", 30, str);	strcat(str_res, str);	len += getStrLen(str);
		printf("%s%.*s|\n", str_res, SPACE_LEN - (getStrLen(str_res) - yellow_l - reset_l) - 2, space);
	}
	len = 0;	memset(str_res, 0, 100);
	response = (state & ST_BAD_CANARYDATA) ? resp_bad : resp_none;
	sprintf(value_s, $value, *(stk->data+stk->capacity+1));
	sprintf(str, "|               %scanary  = %s%s", blue_col, value_s, space_h);		sprintf(str, "%.*s", 51, str);	strcat(str_res, str);	len += getStrLen(str);
	sprintf(str, "%s%s%s", red_col, response, reset_col);								sprintf(str, "%.*s", 20, str);	strcat(str_res, str);	len += getStrLen(str);
	printf("%s%.*s|\n", str_res, SPACE_LEN - (len - blue_l - red_l - reset_l) - 2, space);

	sprintf(str, "|               }");	printf("%s%.*s|\n", str, SPACE_LEN - getStrLen(str) - 2, space);


	//	Canary 2.
	len = 0;	memset(str_res, 0, 100);
	response = (state & ST_BAD_CANARY2) ? resp_bad : resp_none;
	sprintf(str, "|        --> %scanary2  = 0x%X%s", blue_col, stk->canary2, space_h);	sprintf(str, "%.*s", 51, str);	strcat(str_res, str);	len += getStrLen(str);
	sprintf(str, "%s%s%s", red_col, response, reset_col);								sprintf(str, "%.*s", 20, str);	strcat(str_res, str);	len += getStrLen(str);
	printf("%s%.*s|\n", str_res, SPACE_LEN - (len - blue_l - red_l - reset_l) - 2, space);


	sprintf(str, "|        }");	printf("%s%.*s|\n", str, SPACE_LEN - getStrLen(str) - 2, space);
end:

	printf("+-------------------------------------------------------------------------------------------------+\n\n");
}

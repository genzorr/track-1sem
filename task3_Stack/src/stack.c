//--------------------------------------------------------------------------------------------
//! @file stack.c
//! Includes functions for working with stack.
//--------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "stack.h"

#define $_s( x )	printf("%s", #x);
#define $_s_ret(x)	(#x)

#define INIT_CAPACITY		16
#define	POISON				(-42)


stack* StackCtor()
{
	//	Allocate and check that memory was allocated.
	stack* s = (stack*)calloc(1, sizeof(*s));
	if (s == NULL)
		return NULL;

	//	Allocate data and fill fields.
	s->data 	= (data_t*)calloc(INIT_CAPACITY, sizeof(data_t));
	s->size 	= 0;
	s->capacity = INIT_CAPACITY;

	//	Check data.
	if (s->data == NULL)
	{
		free(s);
		s = NULL;
	}

	return s;
}


int StackDtor(stack* s)
{
	if (s == NULL)
		return ST_NULL_PTR;

	if (s->data == NULL)
	{
		free(s);
		return ST_NULL_DATA_PRT;
	}

	//	Fill stack with poison
	memset(s->data, POISON, s->size);
	s->size 	= POISON;
	s->capacity = POISON;

	free(s->data);
	s->data = NULL;
	free(s);
	s = NULL;

	return OK;
}


int StackOK(stack* s)
{
	if (s == NULL)
		return ST_NULL_PTR;

	if (s->data == NULL)
		return ST_NULL_DATA_PRT;

	if ((s->size < 0) || (s->size > s->capacity))
		return ST_INV_SIZE;

	return OK;
}


void StackDump(stack* s)
{
	char str[100] = {};

	printf("\n################################### STACK DUMP #######################################################\n");
	printf("+----------------------------------------------------------------------------------------------------+\n");

	char* response = NULL;
	char* resp_ok	= "ok";
	char* resp_err 	= "ERROR";

//	char* name = (char*)calloc(10, sizeof(*name));
////	name[0] = 's';	name[1] = '\0';
//	sprintf(name, "%s", $_s_ret(s));
	if (!StackOK(s))
		response = resp_ok;
	else
		response = resp_err;

//	printf("%s", response);
	printf("|\tStack ");
	sprintf(str, "%s           ", $_s_ret(s));		printf("%.*s", 10, str);
	sprintf(str, "[%p]              ", (void**)s);	printf("%.*s", 20, str);
	sprintf(str, "(%s)         ", response);		printf("%.*s", 10, str);
//	sprintf(str, "%s:\t[%p]\t(%s)                                                           ", name, (void**)s, response);
//	printf("%.*s", 100, str);
	printf("|\n");

//	free(name); name = NULL;

	return;

	printf("|");
	yellow;	printf("\tStack ");	$_s(s);	reset_color;
	printf(":\t[%p]", s);
	if (!StackOK(s))
		{message(green, "\t(ok)\t");}
	else
		{message(red, "\t(ERROR)\t");}
	printf("|\n");

	printf("+-------------------------------------------------------------------------------------------+\n");
}


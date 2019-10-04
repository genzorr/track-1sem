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
	printf("\n########## STACK DUMP ####################################\n");
	printf("+--------------------------------------------------------+\n");

	printf("|");
	yellow;	printf("\tStack ");	$_s(s);	reset_color;
	printf(":\t[%p]", s);
	if (!StackOK(s))
		{message(green, "\t(ok)\t");}
	else
		{message(red, "\t(ERROR)\t");}
	printf("|\n");

	printf("+--------------------------------------------------------+\n");
}


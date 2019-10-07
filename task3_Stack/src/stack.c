//--------------------------------------------------------------------------------------------
//! @file stack.c
//! Includes functions for working with stack.
//--------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "stack.h"


int StackCtor(stack* s)
{
	if (MY_assert(s))
		return ASSERT_FAIL;

	//	Allocate data and fill fields.
	s->data 	= (data_t*)calloc(INIT_CAPACITY, sizeof(data_t));
	s->size 	= 0;
	s->capacity = INIT_CAPACITY;

	s->canary1	= CANARY1;
	s->canary2	= CANARY2;

	//	Check data.
	if (s->data == NULL)
		return ST_NULL_DATA_PTR;

	return OK;
}


int StackDtor(stack* s)
{
	if (s == NULL)
		return ST_NULL_PTR;

	if (s->data == NULL)
		return ST_NULL_DATA_PTR;

	//	Fill stack with poison
	memset(s->data, POISON, s->size);
	s->size 	= POISON;
	s->capacity = POISON;

	free(s->data);
	s->data = NULL;

	return OK;
}


int StackOK(stack* s)
{
	if (s == NULL)
		return ST_NULL_PTR;

	if (s->data == NULL)
		return ST_NULL_DATA_PTR;

	if ((s->size < 0) || (s->size > s->capacity))
		return ST_INV_SIZE;

	if ((s->canary1 != CANARY1) || (s->canary2 != CANARY2))
		return ST_BAD_CANARY;

	return OK;
}


//--------------------------------------------------------------------------------------------
//! @file stack.c
//! Includes functions for working with stack.
//--------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "stack.h"


int StackCtor(stack* stk)
{
	if (MY_assert(stk))
		return ASSERT_FAIL;

	//	Allocate data memory and fill fields.
	stk->data 	= (data_t*)calloc(INIT_CAPACITY+2, sizeof(data_t));
	stk->size 	= 0;
	stk->capacity = INIT_CAPACITY;

	stk->canary1	= CANARY1;
	stk->canary2	= CANARY2;

	//	Check data.
	if (stk->data == NULL)
		return ST_NULL_DATA_PTR;

	stk->data[0] = CANARYDATA;
	stk->data[INIT_CAPACITY+1] = CANARYDATA;

	return OK;
}


int StackDtor(stack* stk)
{
	if (stk == NULL)
		return ST_NULL_PTR;

	if (stk->data == NULL)
		return ST_NULL_DATA_PTR;

	//	Fill stack with poison.
	memset(&(stk->data[1]), POISON, stk->size);
	stk->size 	= POISON;
	stk->capacity = POISON;

	free(stk->data);
	stk->data = NULL;

	return OK;
}


int StackOK(stack* stk)
{
	if (stk == NULL)
		return ST_NULL_PTR;

	int error = 0;

	if (stk->data == NULL)
		error |= ST_NULL_DATA_PTR;

	if ((stk->size < 0) || (stk->size > stk->capacity))
		error |= ST_INV_SIZE;

	if (stk->canary1 != CANARY1)
		error |= ST_BAD_CANARY1;

	if (stk->canary2 != CANARY2)
		error |= ST_BAD_CANARY2;

	if ((stk->data[0] != CANARYDATA) || (stk->data[stk->capacity+1] != CANARYDATA))
		error |= ST_BAD_CANARYDATA;

	return error;
}


int StackIncrease(stack* stk)
{
	ASSERT_OK;

	size_t size = INIT_CAPACITY;
	if (stk->size == stk->capacity)
		size = stk->capacity * 2;

	data_t* copy = realloc(stk->data, (size+2)*sizeof(data_t));

	if (copy == NULL)
	{
		messagen(red, "# Can't realloc new memory for data");
		return ALLOC_FAIL;
	}

	stk->data = copy;
	stk->data[stk->capacity+1] = 0;

	stk->capacity = size;
	stk->data[stk->capacity+1] = CANARYDATA;

	ASSERT_OK;
	return OK;
}


int StackPush(stack* stk, data_t value)
{
	ASSERT_OK;

	if (stk->size == stk->capacity)
		if (StackIncrease(stk) == ALLOC_FAIL)
		{
			messagen(yellow, "# Can't push because of stack overflow");
			return	ST_OVERFLOW;
		}

	stk->data[(stk->size++) + 1] = value;

	ASSERT_OK;
	return OK;
}


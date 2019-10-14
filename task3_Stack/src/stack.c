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
	stk->error	= 0;

	stk->canary1	= CANARY1;
	stk->canary2	= CANARY2;

	//	Check data.
	if (stk->data == NULL)
	{
		stk->error = ST_NULL_DATA_PTR;
		return ST_NULL_DATA_PTR;
	}

	stk->data[0] = CANARYDATA;
	stk->data[INIT_CAPACITY+1] = CANARYDATA;

	return OK;
}


int StackDtor(stack* stk)
{
	if (stk == NULL)
		return ST_NULL_PTR;

	if (stk->data == NULL)
	{
		stk->error = ST_NULL_DATA_PTR;
		return ST_NULL_DATA_PTR;
	}

	//	Fill stack with poison.
	memset(stk->data, POISON, stk->capacity + 2);
	stk->size 	= POISON;
	stk->capacity = POISON;
	stk->error	= POISON;

	//	here.

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

	stk->error = error;

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
	stk->data[stk->capacity+1] = POISON;

	stk->capacity = size;
	stk->data[stk->capacity+1] = CANARYDATA;

	ASSERT_OK;
	return OK;
}


int StackDecrease(stack* stk)
{
	ASSERT_OK;

	if ((stk->size < stk->capacity / 4) && (stk->capacity > INIT_CAPACITY))
	{
		size_t size = stk->capacity / 4;
		size = (size < INIT_CAPACITY) ? INIT_CAPACITY : size;

		stk->data[stk->capacity+1] = POISON;

		data_t* copy = realloc(stk->data, (size+2)*sizeof(data_t));

		if (copy == NULL)
		{
			messagen(red, "# Can't realloc new memory for data");
			return ALLOC_FAIL;
		}

		stk->data = copy;
		stk->capacity = size;
		stk->data[stk->capacity+1] = CANARYDATA;

	}

	ASSERT_OK;
	return OK;
}


int StackPush(stack* stk, data_t value)
{
	ASSERT_OK;

	if (stk->size == stk->capacity)
	{
		if (StackIncrease(stk) == ALLOC_FAIL)
		{
			messagen(yellow, "# Can't push element: allocation fail");
			stk->error |= ST_OVERFLOW;
			return	ST_OVERFLOW;
		}
		else
			messagen(yellow, "# Stack's data memory was reallocated");
	}

	stk->data[(stk->size++) + 1] = value;

	ASSERT_OK;
	return OK;
}


data_t StackPop(stack* stk)
{
	ASSERT_OK;

	if (stk->size == 0)
	{
		messagen(yellow, "# Can't pop element: stack is empty");
		stk->error = ST_UNDERFLOW;
		return ST_UNDERFLOW;
	}

	if (stk->size < (stk->capacity / 4))
	{
		if (StackDecrease(stk) == ALLOC_FAIL)
		{
			messagen(yellow, "# Can't push element: allocation fail");
			stk->error |= ST_ALLOC_FAIL;
			return POISON;
		}
		else
			messagen(yellow, "# Stack's data memory was reallocated");
	}

	data_t value = stk->data[(--(stk->size)) + 1];
	stk->data[(stk->size) + 1] = POISON;

	ASSERT_OK;
	return value;
}


int StackClear(stack* stk)
{
	ASSERT_OK;

	StackDtor(stk);
	StackCtor(stk);

	ASSERT_OK;
	return OK;
}

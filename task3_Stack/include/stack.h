//--------------------------------------------------------------------------------------------
//! @file stack.h
//! Includes functions prototypes.
//--------------------------------------------------------------------------------------------

#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

#include <stdint.h>
#include <assert.h>

#define INIT_CAPACITY		8
#define	POISON				(-42)

#define CANARY1		0xDEADBEEF
#define CANARY2		0x0EDAF00D
#define CANARYDATA	(POISON*POISON)

#define $value		"%10.3lf"
typedef double data_t;
//#define $value			"%5d"
//typedef int data_t;


typedef struct Stack
{
	const char name[10];

	int32_t	canary1;

	data_t* data;
	size_t	size;
	size_t	capacity;

	size_t	error;

	int32_t canary2;

	data_t hash;
} stack;


enum stack_errors
{
	ST_NULL_PTR			= (1 << 0),
	ST_NULL_DATA_PTR	= (1 << 1),
	ST_INV_SIZE			= (1 << 2),
	ST_BAD_CANARY1		= (1 << 3),
	ST_BAD_CANARY2		= (1 << 4),
	ST_BAD_CANARYDATA	= (1 << 5),
	ST_OVERFLOW			= (1 << 6),
	ST_UNDERFLOW		= (1 << 7),
	ST_ALLOC_FAIL		= (1 << 8),
	ST_BAD_HASH			= (1 << 9)
};


int StackCtor();
int StackDtor(stack* s);
int StackOK(stack* s);
void StackDump(stack* s);

int StackPush(stack* stk, data_t value);
data_t StackPop(stack* stk);

int StackIncrease(stack* stk);
int StackDecrease(stack* stk);

int StackClear(stack* stk);

data_t calc_hash(stack* stk);



#define ASSERT_OK			\
{							\
	if (StackOK(stk))		\
	{						\
		StackDump(stk);		\
		assert(!"OK");		\
	}						\
}

#endif /* INCLUDE_STACK_H_ */

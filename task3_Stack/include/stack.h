//--------------------------------------------------------------------------------------------
//! @file stack.h
//! Includes functions prototypes.
//--------------------------------------------------------------------------------------------

#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

#include <stdint.h>

#define INIT_CAPACITY		16
#define	POISON				(-42)

#define CANARY1		0xDEADBEEF
#define CANARY2		0x0EDAF00D
#define CANARYDATA	(POISON*POISON)


typedef double data_t;

typedef struct Stack
{
	const char name[10];

	int32_t	canary1;

	data_t* data;
	size_t	size;
	size_t	capacity;

	int32_t canary2;
} stack;


enum stack_errors
{
	ST_NULL_PTR			= (1 << 0),
	ST_NULL_DATA_PTR	= (1 << 1),
	ST_INV_SIZE			= (1 << 2),
	ST_BAD_CANARY1		= (1 << 3),
	ST_BAD_CANARY2		= (1 << 4),
	ST_BAD_CANARYDATA	= (1 << 5)
};


int StackCtor();
int StackDtor(stack* s);
int StackOK(stack* s);
void StackDump(stack* s);

#endif /* INCLUDE_STACK_H_ */

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
	ST_NULL_PTR			= -11,
	ST_NULL_DATA_PTR	= -12,
	ST_INV_SIZE			= -13,
	ST_BAD_CANARY		= -14
};


int StackCtor();
int StackDtor(stack* s);
int StackOK(stack* s);
void StackDump(stack* s);

#endif /* INCLUDE_STACK_H_ */

//--------------------------------------------------------------------------------------------
//! @file stack.h
//! Includes functions prototypes.
//--------------------------------------------------------------------------------------------

#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

typedef double data_t;

typedef struct Stack
{
	data_t* data;
	size_t	size;
	size_t	capacity;
} stack;


enum stack_errors
{
	ST_NULL_PTR			= -11,
	ST_NULL_DATA_PRT	= -12,
	ST_INV_SIZE			= -13
};


stack* StackCtor();
int StackDtor(stack* s);
int StackOK(stack* s);
void StackDump(stack* s);

#endif /* INCLUDE_STACK_H_ */

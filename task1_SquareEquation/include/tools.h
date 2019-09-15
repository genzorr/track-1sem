//--------------------------------------------------------------------------------------------
//! @author korr237i
//! @file	tools.h
//! This file contains special tools like macros, structures etc.
//--------------------------------------------------------------------------------------------

#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdlib.h>
#include <stdio.h>

//	Note: type and special should be strings like "d", "s" etc.
#define $( x , type )	printf("%"type, (x));
#define $n( x , type )	printf("%"type"\n", (x));

#define $$( x , type , special )	printf(special#x" = %"type, (x));
#define $$n( x , type , special )	printf(special#x" = %"type"\n", (x));

#define my_assert( check )					\
({											\
	int error = 0;							\
	if (!(check))							\
	{										\
		printf("!## ASSERTION FAILED: function %s()\tFILE %s\tLINE %d\n", __PRETTY_FUNCTION__, __FILE__, __LINE__);\
		printf("!## expression: %s\n", #check);\
		error = -1;							\
	}										\
	error;									\
})

enum
{
	ASSERT_FAIL = -1,
	INPUT_FAIL 	= -2,
	TESTS_FAIL  = -3,
	FUN_ERROR	= -10
} errors_e;

int runUnitTests(int tests_num, int (*tester)(int));

#endif /* TOOLS_H_ */

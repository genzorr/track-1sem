//--------------------------------------------------------------------------------------------
//! @author korr237i
//! @file	tests_lib.c
//!
//! This file contains macros and functions to provide unit-testing.
//!	Run runUnitTests function with custom tester function.
//--------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "tools.h"

//--------------------------------------------------------------------------------------------
//! @def UNITTEST( what, op, ref, res_type )
//!	Performs comparison using (op) between (what) and (ref).
//!
//! @retval	0 if ((what) op (ref)), -1 else.
//--------------------------------------------------------------------------------------------
#define UNITTEST( what, op, ref, res_type )                                                   \
({                                                                                            \
	int error = 0;                                                                            \
	auto result##__LINE__ = (what);                                                           \
	if (result op (ref));                                                                     \
    else                                                                                      \
	{                                                                                         \
    	red;																				  \
        printf(#what" is %"#res_type" but should be %"#res_type"\n", result##__LINE__, (ref)) \
		error = -1;                                                                           \
		reset_color;                                                                          \
	}                                                                                         \
	error;                                                                                    \
})


//--------------------------------------------------------------------------------------------
//! @fn runUnitTests(int tests_num, int (*tester)(int))
//! Runs unit tests tester function for test_num times.
//!
//! @param[in]  tests_num	Number of tests to be runned.
//! @param[in]  tester		Pointer to tester function. It sould run tests and create response by itself.
//!
//! @return	 Error if one of tests failed.
//! @retval  0 if all tests passed, TESTS_FAIL (-3) else.
//--------------------------------------------------------------------------------------------
int runUnitTests(int tests_num, int (*tester)(int))
{
	int error = OK;
	char* passed = (char*)calloc(tests_num+1,   sizeof(*passed));
	char* total  = (char*)calloc(tests_num+1,   sizeof(*total));

	for (int i = 0; i < tests_num; i++)
	{
		passed[i] = '#';
		total[i]  = '-';
	}

	yellow; printf("# Unit testing started\n"); reset_color;
	yellow; printf("-------------------------------------------------\n"); reset_color;
	for (int i = 1; i < tests_num + 1; i++)
	{
		if(tester(i))
		{
			red; printf("#!! UNITTEST #%d failed\n", i); reset_color;
			error = TESTS_FAIL;
			break;
		}
		green; printf("\r[%.*s|%.*s]", i, passed, tests_num - i, total);
	}

	reset_color;
	yellow; printf("\n-------------------------------------------------\n"); reset_color;
	if (!error)
	{ green; printf("# Unit testing ended successfully\n"); reset_color;}

	free(passed);
	free(total);

	return error;
}

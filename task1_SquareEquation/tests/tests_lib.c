//--------------------------------------------------------------------------------------------
//! @author korr237i
//! @file	tests_lib.c
//! This is a file with macros and functions to provide unit-testing.
//!	@note	To use it, create tests.c file with arrays of input and output data.
//--------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#define UNITTEST( what, op, ref, res_type )                                                   \
({                                                                                            \
	int error = 0;                                                                            \
	auto result##__LINE__ = (what);                                                           \
	if (result op (ref));                                                                     \
    else                                                                                      \
	{                                                                                         \
        printf(#what" is %"#res_type" but should be %"#res_type"\n", result##__LINE__, (ref)) \
		error = -1;                                                                           \
	}                                                                                         \
	error;                                                                                    \
})


//	TODO: pointer to function
int runUnitTests(int tests_num, int (*tester)(int))
{
	int error = 0;
	char* passed = (char*)calloc(tests_num+1,   sizeof(*passed));
	char* total  = (char*)calloc(tests_num+1,   sizeof(*total));
	char* back   = (char*)calloc(tests_num*2+2, sizeof(*back));

	for (int i = 0; i < tests_num; i++)
	{
		passed[i] = '#';
		total[i]  = '-';
	}
	for (int i = 0; i < tests_num*2+2; i++)
		back[i] = '\b';

	printf("# Unit testing started\n");
	printf("-------------------------------------------------\n");
	for (int i = 1; i < tests_num + 1; i++)
	{
		if(tester(i))
		{
			printf("#!! UNITTEST #%d failed\n", i);
			error = -3;
			break;
		}
		printf("\r[%.*s|%.*s]", i, passed, tests_num - i, total);
//		fflush(stdout);
	}
	printf("\n-------------------------------------------------\n");
	if (!error)
		printf("# Unit testing ended successfully\n");

	free(passed);
	free(total);

	return error;
}

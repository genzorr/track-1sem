//--------------------------------------------------------------------------------------------
//! @author korr237i
//! @file	tests.h
//! This file contains data arrays and tester for Square Equation solver.
//--------------------------------------------------------------------------------------------

#ifndef TESTS_H_
#define TESTS_H_

#include "equation.h"

//--------------------------------------------------------------------------------------------
//! @def TESTS_NUMBER
//! Number of created unit tests.
//--------------------------------------------------------------------------------------------
#define TESTS_NUMBER	2


//--------------------------------------------------------------------------------------------
//! @var coeff_data
//! 2d array which contains a, b, c coefficients of square equation.
//--------------------------------------------------------------------------------------------
double coeff_data[TESTS_NUMBER][3] =
{
		{0, 0, 0},
		{1, 2, 1}
};


//--------------------------------------------------------------------------------------------
//! @var res_data
//! Array which contains function results.
//--------------------------------------------------------------------------------------------
int res_data[TESTS_NUMBER] =
{
		INF_ROOTS,
		ONE_ROOT
};


//--------------------------------------------------------------------------------------------
//! @var roots_data
//! Array which contains roots of solved equation.
//--------------------------------------------------------------------------------------------
double roots_data[TESTS_NUMBER][2] =
{
		{0, 0},
		{-1, -1}
};

//--------------------------------------------------------------------------------------------
//! @fn runUnitTests(int cnt)
//! Runs unittest using coeff_data, res_data, roots_data.
//!
//! @param[in]  cnt	Number of current test which is runned.
//!
//! @return	 Error if test failed.
//! @retval  0 if test passed, TESTS_FAIL (-3) else.
//--------------------------------------------------------------------------------------------
int unittest_SolveSquare(int cnt)
{
	double x1 = 0, x2 = 0;
	double a = coeff_data[cnt-1][0], b = coeff_data[cnt-1][1], c = coeff_data[cnt-1][2];
	int result = SolveSquare(a, b, c, &x1, &x2);

	if ((result != res_data[cnt-1]) || (x1 != roots_data[cnt-1][0]) || (x2 != roots_data[cnt-1][1]))
	{
		red;
		printf("#!! Unit test #%d FAILED\n", cnt);
		printf("#!!\tSolveSquare result: %d, expected: %d\n", result, res_data[cnt-1]);
		printf("#!!\ta = %.2lf\tb = %.2lf\tc = %.2lf\n", a, b, c);
		printf("#!!\tx1 = %.2lf, expected: %.2lf\n", x1, roots_data[cnt-1][0]);
		printf("#!!\tx2 = %.2lf, expected: %.2lf\n", x2, roots_data[cnt-1][1]);
		reset_color;
		return TESTS_FAIL;
	}

	return OK;
}


#endif /* TESTS_H_ */

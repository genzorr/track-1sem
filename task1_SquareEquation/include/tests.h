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
#define TESTS_NUMBER	sizeof(test_data) / (sizeof(double) * 6)


//--------------------------------------------------------------------------------------------
//! @def TEST
//! Macro substitution for running unit testing.
//--------------------------------------------------------------------------------------------
#ifdef DEBUG
#define TEST	(runUnitTests(TESTS_NUMBER, unittest_SolveSquare))
#else
#define TEST	0
#endif


//--------------------------------------------------------------------------------------------
//! @def TESTS_EPS
//! Epsilon value used to compare doubles in tests.
//--------------------------------------------------------------------------------------------
#define TESTS_EPS	0.001


//--------------------------------------------------------------------------------------------
//! @var test_data
//! 2d array which contains a, b, c coefficients of square equation, roots and results.
//--------------------------------------------------------------------------------------------
double test_data[][6] =
{
        {INF_ROOTS, 0,  0,  0,  NAN,    NAN},
        {ONE_ROOT,  1,  0,  0,  0,      0},
        {ONE_ROOT,  0,  1,  0,  0,      0},
        {NO_ROOTS,  0,  0,  1,  NAN,    NAN},
        {ONE_ROOT,  1,  2,  1,  -1,     -1},
        {NO_ROOTS,  1,  2,  2,  NAN,    NAN},
        {TWO_ROOTS, 1,  2,  -2, 0.732,  -2.732}
};


//--------------------------------------------------------------------------------------------
//! @fn unittest_SolveSquare(int cnt)
//! Runs unittest using coeff_data, res_data, roots_data.
//!
//! @param[in]  cnt	Number of current test which is runned.
//!
//! @return	 Error if test failed.
//! @retval  0 if test passed, TESTS_FAIL (-3) else.
//--------------------------------------------------------------------------------------------
int unittest_SolveSquare(int cnt)
{
	double x1 = NAN, x2 = NAN;
	double a = test_data[cnt-1][1], b = test_data[cnt-1][2], c = test_data[cnt-1][3];
	int result = SolveSquare(a, b, c, &x1, &x2);

	int _cmp1_res = (result != (int)test_data[cnt-1][0]);
	int _cmp2_res = !isnan(test_data[cnt-1][4]) ? isnan(x1) : isValue(x1, test_data[cnt-1][4], TESTS_EPS);
	int _cmp3_res = !isnan(test_data[cnt-1][5]) ? isnan(x2) : isValue(x2, test_data[cnt-1][5], TESTS_EPS);

	if (_cmp1_res || _cmp2_res || _cmp3_res)
	{
		red;
		printf("\n#!! Unit test #%d FAILED, invalid ", cnt);
		if (_cmp1_res)
			printf("result ");
		if (_cmp2_res)
			printf("root 1 ");
		if (_cmp3_res)
			printf("root 2 ");
		printf("\n");

		printf("#!!\tSolveSquare result: %d, expected: %d\n", result, (int)test_data[cnt-1][0]);
		printf("#!!\ta = %.3lf\tb = %.3lf\tc = %.3lf\n", a, b, c);
		printf("#!!\tx1 = %.3lf, expected: %.3lf\n", x1, test_data[cnt-1][4]);
		printf("#!!\tx2 = %.3lf, expected: %.3lf\n", x2, test_data[cnt-1][5]);
		reset_color;
		return TESTS_FAIL;
	}

	return OK;
}


#endif /* TESTS_H_ */

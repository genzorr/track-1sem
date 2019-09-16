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
        {TWO_ROOTS, 1,  2,  -2, 0.732,  -2.732},
        {INF_ROOTS, 0,  0,  0,  NAN,    NAN},
        {INF_ROOTS, 0,  0,  0,  NAN,    NAN},
        {INF_ROOTS, 0,  0,  0,  NAN,    NAN},
        {INF_ROOTS, 0,  0,  0,  NAN,    NAN},
        {INF_ROOTS, 0,  0,  0,  NAN,    NAN},
        {INF_ROOTS, 0,  0,  0,  NAN,    NAN},
        {INF_ROOTS, 0,  0,  0,  NAN,    NAN},
        {INF_ROOTS, 0,  0,  0,  NAN,    NAN}
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
	double x1 = NAN, x2 = NAN;
	double a = test_data[cnt-1][1], b = test_data[cnt-1][2], c = test_data[cnt-1][3];
	int result = SolveSquare(a, b, c, &x1, &x2);

	int _cmp1_value = (result != (int)test_data[cnt-1][0]);

	int _cmp_value = 0;
	_cmp_value = isnan(x1);
	int _cmp2_value = !isnan(test_data[cnt-1][4]) ? _cmp_value : isValue(x1, test_data[cnt-1][4], TESTS_EPS);
	_cmp_value = isnan(x2);
	int _cmp3_value = !isnan(test_data[cnt-1][5]) ? _cmp_value : isValue(x2, test_data[cnt-1][5], TESTS_EPS);

	if (_cmp1_value || _cmp2_value || _cmp3_value)
	{
		red;
		printf("\n#!! Unit test #%d FAILED, invalid ", cnt);
		if (_cmp1_value)
			printf("result\n");
		if (_cmp2_value)
			printf("root 1\n");
		if (_cmp3_value)
			printf("root 2\n");

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

//--------------------------------------------------------------------------------------------
//! @author korr237i
//! @file	main.c
//! Main file of the project.
//!
//! This file contains functions for solving square and linear equations and main() function.
//--------------------------------------------------------------------------------------------

#include <stdio.h>
#include <math.h>

#include "tools.h"
#include "tests.h"
#include "equation.h"


//--------------------------------------------------------------------------------------------
//! @fn main
//! Main function of project.
//--------------------------------------------------------------------------------------------
int main()
{
	message(green, "# Square Solver (c) korr237i");

	if (TEST) return ASSERT_FAIL;

    message(green, "# Enter 3 coefficients of square equation: a, b, c");

    //	Scan square coefficients
	double a = NAN, b = NAN, c = NAN;
	int entered = scanf("%lf%lf%lf", &a, &b, &c);

	//	Check if 3 coefficients were scanned
	if (entered != 3)
	{
		message(red, "# Can't scan 3 values. Try again");
	    return INPUT_FAIL;
	}

	if (MY_assert(isfinite(a))|| MY_assert(isfinite(b)) || MY_assert(isfinite(c)))
	{
		message(red, "# Error while scanning coefficients");
		return ASSERT_FAIL;
	}

	//	Run solver
	double x1 = NAN, x2 = NAN;
	int response = SolveSquare(a, b, c, &x1, &x2);

	//	Print response of solver
	printResponse_SolveSquare(response, x1, x2);

	return OK;
}

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
	green; printf("# Square Solver (c) korr237i\n"); reset_color;

#ifdef DEBUG
    if (runUnitTests(TESTS_NUMBER, unittest_SolveSquare)) return TESTS_FAIL;
#endif

    green; printf("# Enter 3 coefficients of square equation: a, b, c\n"); reset_color;

	double a = NAN, b = NAN, c = NAN;		// Real coefficients of equation

	int entered = scanf("%lf%lf%lf", &a, &b, &c);
	if(my_assert(isfinite(a) && isfinite(b) && isfinite(c))) return ASSERT_FAIL;

	if (entered != 3)    {red; printf("# Can't scan 3 values. Try again\n"); reset_color; return INPUT_FAIL;}

	double x1 = NAN, x2 = NAN;			// Roots of equation
	int response = FUN_ERROR;			// Response of solver
	response = SolveSquare(a, b, c, &x1, &x2);

	//	TODO: move response to function
	switch (response)
	{
		case NO_ROOTS:
			blue; printf("# Equation has no real roots\n"); reset_color;
			break;
		case ONE_ROOT:
			blue; printf("# Equation has one real root:\t\tx = %.3lf\n", x1); reset_color;
			break;
		case TWO_ROOTS:
			blue; printf("# Equation has two real roots:\t\tx1 = %.3lf\tx2 = %.3lf\n", x1, x2); reset_color;
			break;
		case INF_ROOTS:
			blue; printf("# Equation has endless quantity of real roots\n"); reset_color;
			break;
		default:
			blue; printf("# Error. Something went wrong\n"); reset_color;
			break;
	}

	return OK;
}

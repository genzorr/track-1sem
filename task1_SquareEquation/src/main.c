//--------------------------------------------------------------------------------------------
//! @author korr237i
//! @file	main.c
//! Main file of the project.
//!
//! This file contains functions for solving square and linear equations and main() function.
//--------------------------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <errno.h>

#include "tools.h"
#include "tests.h"


//----------------------------
//! @def CMP_EPS
//! Doubles compare accuracy.
//----------------------------
#define CMP_EPS	10E-9

//----------------------------
//! @def NO_ROOTS
//! Means equation has no real roots.
//----------------------------
#define NO_ROOTS  	0

//----------------------------
//! @def ONE_ROOT
//! Means equation has one real root.
//----------------------------
#define ONE_ROOT  	1

//----------------------------
//! @def TWO_ROOTS
//! Means equation has two real roots.
//----------------------------
#define TWO_ROOTS 	2

//----------------------------
//! @def INFINITY_ROOTS
//! Means equation has endless quantity of real roots.
//----------------------------
#define INF_ROOTS	3


int isValue(double x, double a);
int SolveLinear(double a, double b, double * x);
int SolveSquare(double a, double b, double c, double * x1, double * x2);


//---------------------------------------------------------------------------------
//! @fn main
//! Main function of project.
//---------------------------------------------------------------------------------

int main()
{
#ifdef DEBUG
    if (runUnitTests(TESTS_NUMBER, unittest_SolveSquare)) return TESTS_FAIL;
#endif

	printf("# Enter 3 coefficients of square equation: a, b, c\n");

	double a = NAN, b = NAN, c = NAN;		// Real coefficients of equation

	int entered = scanf("%lf%lf%lf", &a, &b, &c);
	if(my_assert(isfinite(a) && isfinite(b) && isfinite(c))) return ASSERT_FAIL;

	if (entered != 3)    {printf("# Can't scan 3 values. Try again"); return INPUT_FAIL;}

	double x1 = NAN, x2 = NAN;			// Roots of equation
	int response = FUN_ERROR;			// Response of solver
	response = SolveSquare(a, b, c, &x1, &x2);

	//	TODO: move response to function
	switch (response)
	{
		case NO_ROOTS:
			printf("# Equation has no real roots");
			break;
		case ONE_ROOT:
			printf("# Equation has one real root:\tx = %.2lf", x1);
			break;
		case TWO_ROOTS:
			printf("# Equation has two real roots:\tx1 = %.2lf\tx2 = %.2lf", x1, x2);
			break;
		case INF_ROOTS:
			printf("# Equation has endless quantity of real roots");
			break;
		default:
			printf("# Error. Something went wrong");
			break;
	}

	return 0;
}


//------------------------------------------------------------------
//! @fn isValue(double x, double a)
//! Checks x for match with a within the accuracy DBL_CMPR_ACCUR.
//!
//! @param[in]  x   Compared value.
//! @param[in]  a   The value with which the comparison takes place.
//!
//! @return	 Output of logical expression x == a (here: |x - a| < DBL_CMPR_ACCUR).
//! @retval  1 if x == a, 0 else
//------------------------------------------------------------------
int isValue(double x, double a)
{
	return (fabs(x - a) < CMP_EPS) ? 1 : 0;
}


//----------------------------------------------------------------------
//! @fn	solve_linearEquation(double a, double b, double * x)
//! Solves linear equation of the form ax + b = 0.
//!
//! @param[in]  a  Leading coefficient.
//! @param[in]  b  Free term.
//! @param[out] x  Root's pointer.
//!
//! @return Number of roots.
//----------------------------------------------------------------------
int SolveLinear(double a, double b, double * x)
{
	if(my_assert(isfinite(a) && isfinite(b))) return ASSERT_FAIL;       // Check for non-NaN
	if(my_assert(x != NULL)) return ASSERT_FAIL;                        // Check for non-NULL pointer

	if (isValue(a, 0.0))
	{
		if (isValue(b, 0.0))
			return INF_ROOTS;
		else
			return NO_ROOTS;
	}
	else
	{
		*x = - b / a;
		return ONE_ROOT;
	}
}


//-------------------------------------------------------------------------------------------------------------
//! @fn solve_squareEquation(double a, double b, double c, double * x1, double *x2)
//! Solves square equation of the form ax^2 + bx + c = 0 using function solve_linearEquation.
//!
//! @param[in]  a   Leading coefficient.
//! @param[in]  b   Second	coefficient.
//! @param[in]  c   Free term.
//! @param[out] x1  First root's pointer.
//! @param[out] x2  Second root's pointer.
//!
//! @return Number of roots.
//!         Returns INFINITY_ROOTS if equation has endless quantity of real roots.
//-------------------------------------------------------------------------------------------------------------
int SolveSquare(double a, double b, double c, double * x1, double *x2)
{
	if(my_assert(isfinite(a) && isfinite(b) && isfinite(c)))  return ASSERT_FAIL;		// Check for non-NaN
	if(my_assert((x1 != NULL) && (x2 != NULL) && (x1 != x2))) return ASSERT_FAIL;		// Check for non-NULL pointers and for mismatch of pointers

	if (isValue(a, 0.0))
		return SolveLinear(b, c, x1);
	else
	{
		double discr2 = b*b - 4*a*c;		// Discriminant in square
		if (isValue(discr2, 0.0))
		{
			*x1 = *x2 = -b / (2*a);
			return ONE_ROOT;
		}
		else if	(discr2 < 0)
			return NO_ROOTS;
		else
		{
			double discr = sqrt(discr2);
			*x1 = (-b + discr) / (2*a);
			*x2 = (-b - discr) / (2*a);
			return TWO_ROOTS;
		}
	}
}

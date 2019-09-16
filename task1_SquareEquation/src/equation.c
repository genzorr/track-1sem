//--------------------------------------------------------------------------------------------
//! @author korr237i
//! @file	equation.c
//! Contains functions to solve linear and square equation.
//--------------------------------------------------------------------------------------------
#include <stdlib.h>
#include <math.h>

#include "tools.h"
#include "equation.h"


int isValue(double x, double a, double eps);
int SolveLinear(double a, double b, double * x);
int SolveSquare(double a, double b, double c, double * x1, double * x2);

//--------------------------------------------------------------------------------------------
//! @fn isValue(double x, double a)
//! Checks x for match with a within the accuracy DBL_CMPR_ACCUR.
//!
//! @param[in]  x   Compared value.
//! @param[in]  a   The value with which the comparison takes place.
//! @param[in]	eps	Comparison epsilon.
//!
//! @return	 Output of logical expression x == a (here: |x - a| < DBL_CMPR_ACCUR).
//! @retval  1 if x == a, 0 else
//--------------------------------------------------------------------------------------------
int isValue(double x, double a, double eps)
{
	return (fabs(x - a) < eps) ? 1 : 0;
}


//--------------------------------------------------------------------------------------------
//! @fn	SolveLinear(double a, double b, double * x)
//! Solves linear equation of the form ax + b = 0.
//!
//! @param[in]  a  Leading coefficient.
//! @param[in]  b  Free term.
//! @param[out] x  Root's pointer.
//!
//! @return Number of roots.
//--------------------------------------------------------------------------------------------
int SolveLinear(double a, double b, double * x)
{
	if(my_assert(isfinite(a) && isfinite(b))) return ASSERT_FAIL;       // Check for non-NaN
	if(my_assert(x != NULL)) return ASSERT_FAIL;                        // Check for non-NULL pointer

	if (isValue(a, 0.0, CMP_EPS))
	{
		if (isValue(b, 0.0, CMP_EPS))
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


//--------------------------------------------------------------------------------------------
//! @fn SolveSquare(double a, double b, double c, double * x1, double *x2)
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
//--------------------------------------------------------------------------------------------
int SolveSquare(double a, double b, double c, double * x1, double *x2)
{
	if(my_assert(isfinite(a) && isfinite(b) && isfinite(c)))  return ASSERT_FAIL;		// Check for non-NaN
	if(my_assert((x1 != NULL) && (x2 != NULL) && (x1 != x2))) return ASSERT_FAIL;		// Check for non-NULL pointers and for mismatch of pointers

	if (isValue(a, 0.0, CMP_EPS))
	{
		*x1 = 0;
		return SolveLinear(b, c, x2);
	}
	else
	{
		double discr2 = b*b - 4*a*c;		// Discriminant in square
		if (isValue(discr2, 0.0, CMP_EPS))
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

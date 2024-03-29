//--------------------------------------------------------------------------------------------
//! @author korr237i
//! @file	equation.h
//! Describes functions from equation.c and macros.
//--------------------------------------------------------------------------------------------

#ifndef EQUATION_H_
#define EQUATION_H_


//--------------------------------------------------------------------------------------------
//! @def CMP_EPS
//! Doubles compare accuracy.
//--------------------------------------------------------------------------------------------
#define CMP_EPS	10E-9

//--------------------------------------------------------------------------------------------
//! @def NO_ROOTS
//! Means equation has no real roots.
//--------------------------------------------------------------------------------------------
#define NO_ROOTS  	0

//--------------------------------------------------------------------------------------------
//! @def ONE_ROOT
//! Means equation has one real root.
//--------------------------------------------------------------------------------------------
#define ONE_ROOT  	1

//--------------------------------------------------------------------------------------------
//! @def TWO_ROOTS
//! Means equation has two real roots.
//--------------------------------------------------------------------------------------------
#define TWO_ROOTS 	2

//--------------------------------------------------------------------------------------------
//! @def INF_ROOTS
//! Means equation has endless quantity of real roots.
//--------------------------------------------------------------------------------------------
#define INF_ROOTS	3


int isValue(double x, double a, double eps);
int SolveLinear(double a, double b, double * x);
int SolveSquare(double a, double b, double c, double * x1, double * x2);
void printResponse_SolveSquare(int response, double x1, double x2);


#endif /* EQUATION_H_ */

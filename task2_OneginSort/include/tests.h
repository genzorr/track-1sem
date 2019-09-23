//--------------------------------------------------------------------------------------------
//! @author korr237i
//! @file	tests.h
//! This file contains data arrays and tester for Square Equation solver.
//--------------------------------------------------------------------------------------------

#ifndef TESTS_H_
#define TESTS_H_

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




#endif /* TESTS_H_ */

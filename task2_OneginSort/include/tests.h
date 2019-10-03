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
#define TESTS_NUMBER	1


//--------------------------------------------------------------------------------------------
//! @def TEST
//! Macro substitution for running unit testing.
//--------------------------------------------------------------------------------------------
#ifdef DEBUG
#define TEST	(runUnitTests(TESTS_NUMBER, unittest_Onegin))
#else
#define TEST	0
#endif


char** testData = {
		{"a\n\0b\n\0\n", "a\n\0b\n\0"}
};


//--------------------------------------------------------------------------------------------
//! @fn unittest_Onegin(int cnt)
//! Runs unittests from given in testData.
//! @param[in]  cnt	Number of current test which is runned.
//!
//! @return	 Error if test failed.
//! @retval  0 if test passed, TESTS_FAIL (-3) else.
//--------------------------------------------------------------------------------------------
int unittest_Onegin(int cnt)
{

	return OK;
}



#endif /* TESTS_H_ */

//--------------------------------------------------------------------------------------------
//! @file text.h
//! Includes functions prototypes.
//--------------------------------------------------------------------------------------------

#ifndef TEXT_H_
#define TEXT_H_


enum errors
{
	CANT_OPEN_FILE   = -100,
	INV_LINES_NUMBER = -101
};


int get_fileSize(const char* filepath, int* size);
int get_linesNumber(char* str, int* nLines);

char* read_plaintext(const char* filepath, int* filesize, int* nlines, int* response);
char** create_pointersToLinesArray(char* plaintext, int nlines, int* response);
int text_fillArray_removeNewLines(char* plaintext, char** text);


//--------------------------------------------------------------------------------------------
//! @fn str_ForwardCmp(char* a, char* b)
//! Compares two strings from their beginnings.
//!
//! @param[in]  a  First string.
//! @param[in]  b  Second string.
//!
//! @return  (a > b)
//! @retval   0  a == b
//! @retval   1  a >  b
//! @retval  -1  a <  b
//--------------------------------------------------------------------------------------------
int str_ForwardCmp(char* a, char* b);


//--------------------------------------------------------------------------------------------
//! @fn str_ReverseCmp(char* a, char* b)
//! Compares two strings from their engings.
//!
//! @param[in]  a  First string.
//! @param[in]  b  Second string.
//!
//! @return  (a > b)
//! @retval   0  a == b
//! @retval   1  a >  b
//! @retval  -1  a <  b
//--------------------------------------------------------------------------------------------
int str_ReverseCmp(char* a, char* b);


//--------------------------------------------------------------------------------------------
//! @fn text_forwardSort(char** text, int nlines)
//! Sorts text lines from their beginnings.
//!
//! @param[in]  text    Pointers-to-lines array.
//! @param[in]  nlines  Number of lines in text.
//--------------------------------------------------------------------------------------------
int text_forwardSort(char** text, int nlines);


//--------------------------------------------------------------------------------------------
//! @fn text_reverseSort(char** text, int nlines)
//! Sorts text lines from their engings.
//!
//! @param[in]  text    Pointers-to-lines array.
//! @param[in]  nlines  Number of lines in text.
//--------------------------------------------------------------------------------------------
int text_reverseSort(char** text, int nlines);


//--------------------------------------------------------------------------------------------
//! @fn plaintext_writeToFile(const char* filepath, char* plaintext, int nlines)
//! Sorts text lines from their engings.
//!
//! @param[in]  filepath   Path where the file is.
//! @param[in]  plaintext  Text array.
//! @param[in]  nlines     Number of lines in text.
//!
//! @return  Response of reading file
//--------------------------------------------------------------------------------------------
int plaintext_writeToFile(const char* filepath, char* plaintext, int nlines);


//--------------------------------------------------------------------------------------------
//! @fn text_writeToFile(const char* filepath, char** text, int nlines)
//! Sorts text lines from their engings.
//!
//! @param[in]  filepath  Path where the file is.
//! @param[in]  text      Pointers-to-lines of text array.
//! @param[in]  nlines    Number of lines in text.
//!
//! @return  Response of reading file
//--------------------------------------------------------------------------------------------
int text_writeToFile(const char* filepath, char** text, int nlines);


#endif /* TEXT_H_ */

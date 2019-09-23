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


//--------------------------------------------------------------------------------------------
//! @fn get_fileSize(const char* filepath)
//! Gets size of file using stat function.
//!
//! @param[in]  filepath   Path of file.
//!
//! @return	 Size of file in bytes.
//--------------------------------------------------------------------------------------------
int get_fileSize(const char* filepath, int* size);


//--------------------------------------------------------------------------------------------
//! @fn text_countLinesNumber(char* str)
//! Counts the number of lines in text (string).
//!
//! @param[in]  str   Text array.
//!
//! @return	 Number of lines in this file.
//--------------------------------------------------------------------------------------------
int get_linesNumber(char* str, int* nLines);


//--------------------------------------------------------------------------------------------
//! @fn str_skipSpaces(char* str)
//! Skippes spaces in char array.
//!
//! @param[out]  str   String (array).
//!
//! @return	 Number of skipped spaces.
//--------------------------------------------------------------------------------------------
int str_countSpaces(char* str, int* spacesCount);


//--------------------------------------------------------------------------------------------
//! @fn rawtext_removeGarbage(char* rawtext, int textsize, int* nlines)
//! Removes puncts and excess spaces in at the beginning of lines.
//!
//! @param[out]  rawtext   Text array.
//! @param[in]   textsize  Size of text.
//! @param[out]  nlines    Number of lines in text.
//!
//! @return	 Number of symbols in new file.
//--------------------------------------------------------------------------------------------
int rawtext_removeGarbage(char* rawtext, int textsize, int* nlines);


//--------------------------------------------------------------------------------------------
//! @fn file_check(FILE* f)
//! Checks fhe file to equal to NULL.
//!
//!	@param[in]  f  File.
//!
//! @return	 0 if (f != NULL).
//--------------------------------------------------------------------------------------------
int file_check(FILE* f);


//--------------------------------------------------------------------------------------------
//! @fn read_plaintextFromFile(const char* filepath, int* filesize, int* nlines, int* response)
//! Reads text from file (raw text) and removes garbage (plaintext).
//!
//! @param[in]  filepath  Path of file where is the text.
//! @param[in]  filesize  Size of file.
//! @param[out] nlines    Number of lines in text.
//! @param[out] response  Response of reading.
//!
//! @return	 Pointer to dynamic buffer created for keeping text.
//--------------------------------------------------------------------------------------------
char* read_plaintext(const char* filepath, int* filesize, int* nlines, int* response);


//--------------------------------------------------------------------------------------------
//! @fn create_pointersToLinesArray(char* plaintext, int nlines, int* response)
//! Creates dynamic array of pointers that indicate lines in plaintext.
//!
//! @param[out]  plaintext  Text array.
//! @param[in]      nlines     Number of lines in text.
//! @param[out]     response   Response creating.
//!
//! @return  Pointer to created array.
//--------------------------------------------------------------------------------------------
char** create_pointersToLinesArray(char* plaintext, int nlines, int* response);


//--------------------------------------------------------------------------------------------
//! @fn text_fillArray_removeNewLines(char* plaintext, char** text)
//! Fills the pointers-to-lines array and removes \n.
//!
//! @param[out] plaintext  Text array.
//! @param[out]	text       Array of pointers-to-lines.
//--------------------------------------------------------------------------------------------
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

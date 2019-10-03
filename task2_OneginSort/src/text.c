//--------------------------------------------------------------------------------------------
//! @file text.c
//! Includes functions for working with text.
//--------------------------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>

#include "tools.h"
#include "text.h"


int get_fileSize(const char* filepath, int* size);
int get_linesNumber(char* str, int* nLines);

char* read_plaintext(const char* filepath, int* filesize, int* nlines, int* response);
char** create_pointersToLinesArray(char* plaintext, int nlines, int* response);
int text_fillArray_removeNewLines(char* plaintext, char** text);

int str_ForwardCmp(char* a, char* b);
int str_ReverseCmp(char* a, char* b);

int textSort(char** text, int nlines, int mode);

int plaintext_writeToFile(const char* filepath, char* plaintext, int nlines);
int text_writeToFile(const char* filepath, char** text, int nlines);


//--------------------------------------------------------------------------------------------
//! @fn get_fileSize(const char* filepath, int* size)
//! Gets size of file using stat function without file opening.
//!
//! @param[in]  filepath	Path to file.
//! @param[out]	size		Size of file.
//!
//! @return	 Error code if assert occurred.
//--------------------------------------------------------------------------------------------
int get_fileSize(const char* filepath, int* size)
{
	if (MY_assert(filepath) || MY_assert(size))
		return ASSERT_FAIL;

	struct stat st = {};
	stat(filepath, &st);
	*size = st.st_size;

	return OK;
}


//--------------------------------------------------------------------------------------------
//! @fn text_countLinesNumber(char* str, int* nLines)
//! Counts the number of lines in text represented as string.
//!
//! @param[in]  str		Text array.
//!	@param[out]	nLines	Number of lines in text including empty lines.
//!
//! @return	 Error code if assert occurred.
//--------------------------------------------------------------------------------------------
int get_linesNumber(char* str, int* nLines)
{
	if (MY_assert(str) || MY_assert(nLines))
		return ASSERT_FAIL;

	int nChar = 0;
	char* ch = str;

	for (ch = strchr(str, '\n'); ch; ch = strchr(ch + 1, '\n'))
		nChar++;

	*nLines = (str[-1] == '\n') ? nChar : (nChar+1);

	return OK;
}


//--------------------------------------------------------------------------------------------
//! @fn read_plaintextFromFile(const char* filepath, int* filesize, int* nLines, int* response)
//! Reads text from file, allocates memory for it.
//!	If you use this function you MUST free buffer after the end of it's usage.
//!
//! @param[in]  filepath  Path to file.
//! @param[in]  filesize  Size of file.
//! @param[in]	nlines    Number of lines in text.
//! @param[out] response  Response of reading.
//!
//! @return	 Pointer to allocated dynamic buffer.
//--------------------------------------------------------------------------------------------
char* read_plaintext(const char* filepath, int* filesize, int* nLines, int* response)
{
	if (MY_assert(filepath) || MY_assert(filesize))	return NULL;
	if (MY_assert(nLines)	|| MY_assert(response))	return NULL;

	int error = 0;

	//	Get size of file to be read.
	error = get_fileSize(filepath, filesize);
	if ((*response == ASSERT_FAIL) || error)
	{
		message(red, "# Can't find file in file system");
		return NULL;
	}

	//	Open file for reading.
	FILE* file = fopen(filepath, "r");
	if (MY_assert(file != NULL))
	{
		message(red, "# Error opening file");
		return NULL;
	}

	//	Allocate buffer for text.
	char* raw_text = (char*)calloc(*filesize+1, sizeof(*raw_text));
	if (MY_assert(raw_text))
	{
		*response = ALLOC_FAIL;
		message(red, "# Can't allocate memory");
		return NULL;
	}

	//	Read file to allocated buffer.
	int readed_size = fread(raw_text, sizeof(*raw_text), *filesize, file);
	if (readed_size < *filesize)
	{
		red; printf("# Only %d bytes from %d were read\n", readed_size, *filesize); reset_color;
	}

	//	Close file.
	error = fclose(file);
	if (error)
	{
		*response = SYS_ERROR;
		message(red, "# Error occurred while file closing");
		return NULL;
	}

	//	Get number of lines in read text.
	error = get_linesNumber(raw_text, nLines);
	if (error)
	{
		*response = FUN_ERROR;
		return NULL;
	}

	return raw_text;
}


//--------------------------------------------------------------------------------------------
//! @fn create_pointersToLinesArray(char* plaintext, int nlines, int* response)
//! Allocates array of pointers to strings. Every element in that array points at the beginning of string in text.
//!	If you use this function you MUST free buffer after the end of it's usage.
//!
//! @param[in]	plaintext  Pointer to plaintext array.
//! @param[in]	nLines     Number of lines in text.
//! @param[out]	response   Result of working.
//!
//! @return  Pointer to created lines pointers array.
//--------------------------------------------------------------------------------------------
char** create_pointersToLinesArray(char* plaintext, int nLines, int* response)
{
	if (MY_assert(plaintext) || MY_assert(response))
	{
		*response = ASSERT_FAIL;
		return NULL;
	}

	int error = 0;

	//	Check if file has no lines.
	*response = 0;
	if (nLines <= 0)
	{
		*response = INV_LINES_NUMBER;
		message(red, "# Invalid lines number");
		return NULL;
	}

	//	Allocate buffer.
	char** text = (char**)calloc(nLines+1, sizeof(*text));
	if (MY_assert(text))
	{
		*response = ASSERT_FAIL;
		message(red, "# Can't allocate memory");
		return NULL;
	}

	//	Fill in pointers array and change \n symbols to \0 in each line.
	//	I use element number nLines as indication of array's end.
	text[0] = plaintext;
	text[nLines] = NULL;
	error = text_fillArray_removeNewLines(plaintext, text);
	if (error)
	{
		*response = FUN_ERROR;
		return NULL;
	}

	return text;
}


//--------------------------------------------------------------------------------------------
//! @fn text_fillArray_removeNewLines(char* plaintext, char** text)
//! Fills the pointers-to-lines array and changes \n to \0 in each file.
//!
//! @param[in]	plaintext  Text array.
//! @param[in]	text       Array of pointers-to-lines.
//!
//!	@return		Error code if assert occurred.
//--------------------------------------------------------------------------------------------
int text_fillArray_removeNewLines(char* plaintext, char** text)
{
	if (MY_assert(plaintext) || MY_assert(text))
		return ASSERT_FAIL;

	//	Start from 1 element, 0 element is already pointer to plaintext.
	int lines_counter = 1;
	for (char* ch = strchr(plaintext, '\n'); ch; ch = strchr(ch + 1, '\n'))
	{
		*ch = '\0';
		text[lines_counter++] = ch+1;
	}

	return OK;
}


//--------------------------------------------------------------------------------------------
//! @fn str_ForwardCmp(char* a, char* b)
//! Compares two strings from their beginnings.
//!
//! @param[in]  a  First string.
//! @param[in]  b  Second string.
//!
//! @return  (a > b)
//! @retval   0  a == b
//! @retval   1  a > b
//! @retval  -1  a < b
//--------------------------------------------------------------------------------------------
int str_ForwardCmp(char* a, char* b)
{
	assert(a);
	assert(b);

	int cha = 0, chb = 0;
	int cmpretval = 0;

	if (a[0] == '\0')
		return 1;
	if (b[0] == '\0')
		return -1;

	for (int i = 0, k = 0; (((cha = tolower(a[i])) != '\0') && ((chb = tolower(b[k])) != '\0')); )
	{
		if (!isalpha(cha))
		{
			i++;
			continue;
		}
		if (!isalpha(chb))
		{
			k++;
			continue;
		}

		if (cha == chb)
		{
			cmpretval = 0;
			i++;
			k++;
		}
		else if (cha > chb)
		{
			cmpretval = 1;
			break;
		}
		else if (cha < chb)
		{
			cmpretval = -1;
			break;
		}
	}

	if ((cha == '\0') && (chb != '\0'))
		return -1;
	else if ((chb == '\0') && (cha != '\0'))
		return 1;

	return cmpretval;
}


//--------------------------------------------------------------------------------------------
//! @fn str_ReverseCmp(char* a, char* b)
//! Compares two strings from their endings.
//!
//! @param[in]  a  First string.
//! @param[in]  b  Second string.
//!
//! @return  (a > b)
//! @retval   0  a == b
//! @retval   1  a >  b
//! @retval  -1  a <  b
//--------------------------------------------------------------------------------------------
int str_ReverseCmp(char* a, char* b)
{
	assert(a);
	assert(b);

	int cha = 0, chb = 0;
	int cmpretval = 0;

	int asize = (int)(strchr(a, '\0') - a);
	int bsize = (int)(strchr(b, '\0') - b);

	if (asize == 1)
		return 1;
	if (bsize == -1)
		return -1;

	int i = 0, k = 0;
	for (i = asize-1, k = bsize-1; (i>=0) && (k>=0); )
	{
		cha = tolower(a[i]);
		chb = tolower(b[k]);

		if (!isalpha(cha))
		{
			i--;
			continue;
		}
		if (!isalpha(chb))
		{
			k--;
			continue;
		}

		if (cha == chb)
		{
			cmpretval = 0;
			i--;
			k--;
		}
		else if (cha > chb)
		{
			cmpretval = 1;
			break;
		}
		if (cha < chb)
		{
			cmpretval = -1;
			break;
		}
	}

	if ((i == -1) && (k >= 0))
		return -1;
	else if ((i >= 0) && (k == -1))
		return 1;

	return cmpretval;
}


//--------------------------------------------------------------------------------------------
//! @fn str_ForwardCmpFunc(const void* a, const void* b)
//! A comparator function to use qsort for sorting char** array.
//!
//! @param[in]  a  First string.
//! @param[in]  b  Second string.
//!
//! @retval   Retval of str_ForwardCmp.
//--------------------------------------------------------------------------------------------
static int str_ForwardCmpFunc(const void* a, const void* b)
{
	return str_ForwardCmp(*(char**)a, *(char**)b);
}


//--------------------------------------------------------------------------------------------
//! @fn str_ReverseCmpFunc(const void* a, const void* b)
//! A comparator function to use qsort for sorting char** array.
//!
//! @param[in]  a  First string.
//! @param[in]  b  Second string.
//!
//! @retval   Retval of str_ReverseCmp.
//--------------------------------------------------------------------------------------------
static int str_ReverseCmpFunc(const void* a, const void* b)
{
	return str_ReverseCmp(*(char**)a, *(char**)b);
}


//--------------------------------------------------------------------------------------------
//! @fn textSort(char** text, int nlines, int mode)
//! Sorts text by lines by specified mode. It may be 1 for forward sort or -1 for reverse sort.
//!
//! @param[in]  text    Pointers-to-lines array.
//! @param[in]  nLines  Number of lines in text.
//!	@param[in]	mode	Means forward or reverse sort it will be.
//!
//! @return		Error if assert or other error occurred.
//--------------------------------------------------------------------------------------------
int textSort(char** text, int nLines, int mode)
{
	if (MY_assert(text))
		return ASSERT_FAIL;

	if (nLines <= 0)
		return INV_LINES_NUMBER;

	if ((mode != 1) && (mode != -1))
		return FUN_ERROR;

	if (mode == 1)
		qsort(text, nLines, sizeof(text[0]), str_ForwardCmpFunc);
	else
		qsort(text, nLines, sizeof(text[0]), str_ReverseCmpFunc);

    return OK;
}


//--------------------------------------------------------------------------------------------
//! @fn plaintext_writeToFile(const char* filepath, char* plaintext, int nLines)
//! Writes raw text to file.
//!
//! @param[in]  filepath   Path where the file is.
//! @param[in]  plaintext  Text array.
//! @param[in]  nLines     Number of lines in text.
//!
//! @return  Error code if error occurred.
//--------------------------------------------------------------------------------------------
int plaintext_writeToFile(const char* filepath, char* plaintext, int nLines)
{
	if (MY_assert(filepath) || MY_assert(plaintext))
		return ASSERT_FAIL;

	FILE* f = fopen(filepath, "a");
	if (MY_assert(f))
		return CANT_OPEN_FILE;

	fprintf(f, "\n\n\n\n################################################\n"\
				"################################################\n"\
				"################################################\n\n\n\n\n");

	int cnt = 0;
	fprintf(f, "%s\n", plaintext);

	for (char* ch = strchr(plaintext, '\0'); ch; ch = strchr(ch + 1, '\0')) {
		if (cnt >= nLines)
			break;

		fprintf(f, "%s\n", ch+1);
		cnt++;
	}

	int error = fclose(f);
	if (error)
	{
		message(red, "# Error occurred while file closing");
		return FUN_ERROR;
	}

	return OK;
}


//--------------------------------------------------------------------------------------------
//! @fn text_writeToFile(const char* filepath, char** text, int nLines)
//! Writes sorted text to file.
//!
//! @param[in]  filepath  Path where the file is.
//! @param[in]  text      Pointers-to-lines of text array.
//! @param[in]  nLines    Number of lines in text.
//!
//! @return  Response of reading file
//--------------------------------------------------------------------------------------------
int text_writeToFile(const char* filepath, char** text, int nLines)
{
	if (MY_assert(filepath) || MY_assert(text))
		return ASSERT_FAIL;

	FILE* f = fopen(filepath, "a");
	if (MY_assert(f))
			return CANT_OPEN_FILE;

	fprintf(f, "################################################\n"\
				"################################################\n"\
				"################################################\n");

	for (int i = 0; i < nLines; i++)
		fprintf(f, "%s\n", text[i]);

	int error = fclose(f);
	if (error)
	{
		message(red, "# Error occurred while file closing");
		return FUN_ERROR;
	}

	return OK;
}

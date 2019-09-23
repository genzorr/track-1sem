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
int str_countSpaces(char* str, int* spacesCount);

int rawtext_removeGarbage(char* rawtext, int textsize, int* nLines);

char* read_plaintext(const char* filepath, int* filesize, int* nlines, int* response);
char** create_pointersToLinesArray(char* plaintext, int nlines, int* response);
int text_fillArray_removeNewLines(char* plaintext, char** text);

int str_ForwardCmp(char* a, char* b);
int str_ReverseCmp(char* a, char* b);

int text_forwardSort(char** text, int nlines);
int text_reverseSort(char** text, int nlines);

int plaintext_writeToFile(const char* filepath, char* plaintext, int nlines);
int text_writeToFile(const char* filepath, char** text, int nlines);


int get_fileSize(const char* filepath, int* size)
{
	if (MY_assert(filepath) || MY_assert(size))
		return ASSERT_FAIL;

	struct stat st = {};
	stat(filepath, &st);
	*size = st.st_size;

	return OK;
}


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


int str_countSpaces(char* str, int* spacesCount)
{
	if (MY_assert(str) || MY_assert(spacesCount))
		return ASSERT_FAIL;

	int spaces_cnt = 0;
	for (spaces_cnt = 0; isspace(str[spaces_cnt]); spaces_cnt++);

	*spacesCount = spaces_cnt;

	return OK;
}


//int rawtext_removeGarbage(char* rawtext, int textsize, int* nLines)
//{
//	if (MY_assert(rawtext) || MY_assert(nLines)) return ASSERT_FAIL;
//
//	int newtext_startpos = str_countSpaces(rawtext);
//
//	int ch = 0, cnt = 0, new_cnt = 0;
//	for (cnt = newtext_startpos; ((ch = rawtext[cnt]) != '\0'); cnt++) {
//
//		// ����� � ����� ���, ����� ������ ����������
//		if (!ispunct(ch))
//			rawtext[new_cnt++] = ch;
//
//		// ���������� ���������� ������� ����� ������� �������������� \n
//		int skipped = 0;
//		if (ch == '\n') {
//			*nLines += 1;
//			skipped = str_countSpaces(&rawtext[cnt]);
//
//			if ((cnt+skipped) < textsize)
//				cnt += skipped-1;
//			else
//				break;
//		}
//	}
//	rawtext[new_cnt] = '\0';
//
//	for (int i = new_cnt+1; i < textsize; i++)
//		rawtext[i] = '\0';
//
//	return new_cnt;
//}


char* read_plaintext(const char* filepath, int* filesize, int* nLines, int* response)
{
	if (MY_assert(filepath) || MY_assert(filesize))	return NULL;
	if (MY_assert(nLines)	|| MY_assert(response))	return NULL;

	int error = 0;

	error = get_fileSize(filepath, filesize);
	if ((*response == ASSERT_FAIL) || error)
	{
		message(red, "# Can't find file in filesystem");
		return NULL;
	}

	FILE* file = fopen(filepath, "r");
	if (MY_assert(file != NULL))
	{
		message(red, "# Error opening file");
		return NULL;
	}

	char* raw_text = (char*)calloc(*filesize+1, sizeof(*raw_text));
	if (MY_assert(raw_text))
	{
		*response = ALLOC_FAIL;
		message(red, "# Can't allocate memory");
		return NULL;
	}

	int readed_size = fread(raw_text, sizeof(*raw_text), *filesize, file);
	if (readed_size < *filesize)
	{
		red; printf("# Only %d bytes from %d were read\n", readed_size, *filesize); reset_color;
	}

	error = fclose(file);
	if (error)
	{
		message(red, "# Error occured while file closing");
		return NULL;
	}

	error = get_linesNumber(raw_text, nLines);
	if (error)
		return NULL;

//	rawtext_removeGarbage(raw_text, *filesize, nlines);

	return raw_text;
}


char** create_pointersToLinesArray(char* plaintext, int nlines, int* response)
{
	if (MY_assert(plaintext) || MY_assert(response))
	{
		*response = ASSERT_FAIL;
		return NULL;
	}

	*response = 0;
	if (nlines <= 0)
	{
		*response = INV_LINES_NUMBER;
		message(red, "# Invalid lines number");
		return NULL;
	}

	char** text = (char**)calloc(nlines+1, sizeof(*text));
	if (MY_assert(text))
	{
		*response = ASSERT_FAIL;
		message(red, "# Can't allocate memory");
		return NULL;
	}

	text[0] = plaintext;
	text[nlines] = NULL;
	if (text_fillArray_removeNewLines(plaintext, text))
		return NULL;

	return text;
}


int text_fillArray_removeNewLines(char* plaintext, char** text)
{
	if (MY_assert(plaintext) || MY_assert(text))
		return ASSERT_FAIL;

	int lines_counter = 1;
	for (char* ch = strchr(plaintext, '\n'); ch; ch = strchr(ch + 1, '\n')) {
		*ch = '\0';
		text[lines_counter++] = ch+1;
	}

	return OK;
}


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


static int str_ForwardCmpFunc(const void* a, const void* b)
{
	return str_ForwardCmp(*(char**)a, *(char**)b);
}

static int str_ReverseCmpFunc(const void* a, const void* b)
{
	return str_ReverseCmp(*(char**)a, *(char**)b);
}


int text_forwardSort(char** text, int nlines)
{
	if (MY_assert(text))
		return ASSERT_FAIL;

	if (nlines <= 0)
		return INV_LINES_NUMBER;

    qsort(text, nlines, sizeof(text[0]), str_ForwardCmpFunc);

    return OK;
}


int text_reverseSort(char** text, int nlines)
{
	if (MY_assert(text))
		return ASSERT_FAIL;

	if (nlines <= 0)
		return INV_LINES_NUMBER;

	qsort(text, nlines, sizeof(text[0]), str_ReverseCmpFunc);

	return OK;
}


int plaintext_writeToFile(const char* filepath, char* plaintext, int nlines)
{
	if (MY_assert(filepath) || MY_assert(plaintext))
		return ASSERT_FAIL;

	FILE* f = fopen(filepath, "w");
	if (MY_assert(f))
		return CANT_OPEN_FILE;

	int cnt = 0;
	fprintf(f, "%s\n", plaintext);

	for (char* ch = strchr(plaintext, '\0'); ch; ch = strchr(ch + 1, '\0')) {
		if (cnt >= nlines) break;

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


int text_writeToFile(const char* filepath, char** text, int nlines)
{
	if (MY_assert(filepath) || MY_assert(text))
		return ASSERT_FAIL;

	FILE* f = fopen(filepath, "a");
	if (MY_assert(f))
			return CANT_OPEN_FILE;

	fprintf(f, "################################################\n"\
				"################################################\n"\
				"################################################\n");

	for (int i = 0; i < nlines; i++)
		fprintf(f, "%s\n", text[i]);

	int error = fclose(f);
	if (error)
	{
		message(red, "# Error occurred while file closing");
		return FUN_ERROR;
	}

	return OK;
}

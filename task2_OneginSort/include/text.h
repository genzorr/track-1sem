//--------------------------------------------------------------------------------------------
//! @file text.h
//! Includes functions prototypes.
//--------------------------------------------------------------------------------------------

#ifndef TEXT_H_
#define TEXT_H_

#define	FORWARD	1
#define REVERSE	-1

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

int str_ForwardCmp(char* a, char* b);
int str_ReverseCmp(char* a, char* b);

int textSort(char** text, int nlines, int mode);

int plaintext_writeToFile(const char* filepath, char* plaintext, int nlines);
int text_writeToFile(const char* filepath, char** text, int nlines);


#endif /* TEXT_H_ */

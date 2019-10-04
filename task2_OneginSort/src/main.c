//--------------------------------------------------------------------------------------------
//! @file main.c
//!       Main file of the project.
//--------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "tools.h"
#include "tests.h"
#include "text.h"


const char* in_filepath		= "/home/michael/track/track-1sem/task2_OneginSort/text/text_in.txt";
const char* out_filepath	= "/home/michael/track/track-1sem/task2_OneginSort/text/text_out.txt";


//--------------------------------------------------------------------------------------------
//! @fn main()
//! Main function of the project.
//--------------------------------------------------------------------------------------------
int main()
{
	message(green, "### Text sorter\n");
	if (TEST)
		return ASSERT_FAIL;

	int filesize = 0, nLines = 0, response = 0;
	char* plaintext = read_plaintext(in_filepath, &filesize, &nLines, &response);
	if (response)
		return CANT_OPEN_FILE;

	$$n(in_filepath, "s", "# File: ");
	$$n(filesize, "d", "# File size: ");
	$$n(nLines, "d", "# Lines number: ");

	char** text = create_pointersToLinesArray(plaintext, nLines, &response);
	if (response)
		return response;

	char** text_zeroptr = &text[0];

	//	Open file for the first time with "w" option to clean it.
	FILE* f = fopen(out_filepath, "w");
	if (MY_assert(f))
		return CANT_OPEN_FILE;
	fclose(f);

	response = textSort(text, nLines, FORWARD);
	if (response)
		return response;

	response = text_writeToFile(out_filepath, text, nLines);
	if (response)
		return response;

	response = textSort(text, nLines, REVERSE);
	if (response)
		return response;

	response = text_writeToFile(out_filepath, text, nLines);
	if (response)
		return response;

	response = plaintext_writeToFile(out_filepath, plaintext, nLines);
	if (response != OK)
		return CANT_OPEN_FILE;

	free(plaintext);
	free(text_zeroptr);

	return 0;
}

//============================================================================
//  Assignment: 2 
//  Milestone : 4
//  Student Name  : Seonhye Hyeon
//  Student ID    : 125635193
//  Student Email : shyeon@myseneca.ca
//  Course Section: IPC144ZAA
// ============================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "commonHelpers.h"
#include "accountTicketingUI.h"



int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}

// Empty the standard input buffer
void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}

//Function: getInteger
int getInteger(void)
{
	char newLine = 'x';
	int val;

	while (newLine != '\n')
	{
		scanf("%d%c", &val, &newLine);

		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
	}
	return val;
}


//function: getPositiveInteger
int getPositiveInteger(void)
{
	int val = getInteger();

	while (val <= 0)
	{
		printf("ERROR: Value must be a positive integer greater than zero: ");
		val = getInteger();
	}

	return val;
}
//a2ms2
int getPositiveIntegerZero(void)
{
	int val = getInteger();

	while (val < 0)
	{
		printf("ERROR: Value must be positive or zero: ");
		val = getInteger();
	}
	return val;
}

// Function: getDouble
double getDouble(void)
{
	char newLine = 'x';
	double val;

	while (newLine != '\n')
	{
		scanf("%lf%c", &val, &newLine);

		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
	}
	return val;
}

// Function: getPositiveDouble
double getPositiveDouble(void)
{
	double val = getDouble();

	while (val <= 0)
	{
		printf("ERROR: Value must be a positive double floating-point number: ");
		val = getDouble();
	}

	return val;
}

// Function: getIntFromRange
int getIntFromRange(int lower_bound, int upper_bound)
{
	int val = getInteger();
	while (val < lower_bound || val > upper_bound)
	{
		printf("ERROR: Value must be between %d and %d inclusive: ", lower_bound, upper_bound);
		val = getInteger();
	}
	return val;
}


// Function: getCharOption
char getCharOption(char validOption[])
{
	char ch;
	char newline = 'x';
	int isValid = 0;
	do
	{
		isValid = 0;
		scanf("%c%c", &ch, &newline);
		if (newline != '\n')
		{
			clearStandardInputBuffer();
		}
		else
		{
			if (strchr(validOption, ch))
			{
				isValid = 1;
			}

		}
		if (isValid == 0)
		{
			printf("ERROR: Character must be one of [%s]: ", validOption);
		}

	} while (newline != '\n' || isValid == 0);

	return ch;
}


// Function: getCString
void getCString(char* cstring, int min_length, int max_length)
{
	char newLine = 'x';
	char word[300];
	int length = 0;
	char* p = word;
	int isValid = 0;
	do
	{
		isValid = 0;
		length = 0;
		scanf("%299[^\n]%c", word, &newLine);
		for (p = word; *p; p++)
		{
			length++;
		}
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
		}
		else if (length >= min_length && length <= max_length)
		{
			isValid = 1;
			p = word;
			while (*p)
			{
				*cstring++ = *p++;
			}
			*cstring = 0;
		}
		else
		{
			if (min_length == max_length)
			{
				printf("ERROR: String length must be exactly %d chars: ", min_length);
			}
			else if (length > max_length)
			{
				printf("ERROR: String length must be no more than %d chars: ", max_length);
			}
			else if (length < min_length)
			{
				printf("ERROR: String length must be between %d and %d chars: ", min_length, max_length);
			}
		}

	} while (newLine != '\n' || isValid == 0);
}
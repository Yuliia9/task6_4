/*
*@file		functions.cpp
*@brief		implements functions used in file task3_7.cpp
			uses developed dll and lib library for working with C string
*/

#include "stdafx.h"
#include "task3_7.h"
#include <stdlib.h>



typedef int(*STRLEN_PRINT) (const char*);
typedef char* (*STRPBRK_CAT) (char*, const char*);
typedef char* (*STRNCPY) (char*, const char*, size_t);



#ifdef USE_STRING_H
#include <string.h>
#define STREND '\0'
STRLEN_PRINT mystrlen = (STRLEN_PRINT)strlen;
STRLEN_PRINT myprintf = puts;
STRPBRK_CAT mystrpbrk = (STRPBRK_CAT)strpbrk;
STRPBRK_CAT mystrcat = (STRPBRK_CAT)strcat;
STRNCPY mystrncpy = (STRNCPY) strncpy;

#elif defined (USE_MY_LIB)
#include "my_string.h"
STRLEN_PRINT mystrlen = (STRLEN_PRINT)my_strlen;
STRLEN_PRINT myprintf = (STRLEN_PRINT)my_strprintf;
STRPBRK_CAT mystrpbrk = (STRPBRK_CAT) my_strpbrk;
STRPBRK_CAT mystrcat = (STRPBRK_CAT)my_strcat;
STRNCPY mystrncpy = (STRNCPY)my_strncpy_s;


#elif defined (USE_MY_DLL) 
#include <windows.h> 
HINSTANCE stringdll = LoadLibrary(TEXT("stringdll.dll"));
char* end = (char*)GetProcAddress(stringdll, LPCSTR("STREND"));
const char STREND = *end;
STRLEN_PRINT mystrlen = (STRLEN_PRINT)GetProcAddress(stringdll, LPCSTR("my_strlen"));
STRLEN_PRINT myprintf = (STRLEN_PRINT)GetProcAddress(stringdll, LPCSTR("my_strprintf"));
STRPBRK_CAT mystrpbrk = (STRPBRK_CAT)GetProcAddress(stringdll, LPCSTR("my_strpbrk"));
STRPBRK_CAT mystrcat = (STRPBRK_CAT)GetProcAddress(stringdll, LPCSTR("my_strcat"));
STRNCPY mystrncpy = (STRNCPY)GetProcAddress(stringdll, LPCSTR("my_strncpy_s"));

unsigned int Check_Loading_Library(void)
{
	if (stringdll == NULL)
	{
		return FAIL;
	}
	else if (end == NULL || mystrlen == NULL || myprintf == NULL || mystrpbrk == NULL || mystrcat == NULL || mystrncpy == NULL)
	{
		return FAIL;
	}
}
#endif

void Interface(void)
{
	puts("------------------------------------------------------------------");
	puts("Hi! Welcome to the brilliant word censor.");
	puts("Enter sentences and program will delete for you 2 and 5 word. ");
	puts("Program made by Yuliia Lyubchik.");
	puts("------------------------------------------------------------------\n");
}

unsigned char Input(char** riadok)
{
	int count;
	do
	{
		char temp;
		count = 0;
		printf("Please enter sentence: ");
		do
		{
			scanf("%c", &temp);
			++count;
			*riadok = (char*)realloc(*riadok, count * sizeof(char));
			if (*riadok != NULL)
			{
				*(*riadok + count - 1) = temp;
			}
			else
			{
				free(riadok);
				puts("Error (re)allocating memory. \n");
				return FAIL;
			}

		} 
		while (temp != '\n' && temp != EOF);
		fflush(stdin);
		*(*riadok + count - 1) = STREND;
	} 
	while (riadok == NULL || mystrlen(*riadok) == 0);

	return SUCCESS;
}

char* Delete_bad_word(char* censorship, unsigned int number)
{
	if (censorship == NULL)
	{
		return NULL;
	}
	char* temp;
	char* copy;
	int len = mystrlen(censorship);
	temp = (char*)malloc(len * sizeof(char));

	if (temp == NULL)
	{
		return NULL;
	}
	*temp = STREND;

	char* begin = NULL;
	char* end = NULL;
	char* token;
	unsigned int count = 1;

	const char delimiters[] = { ' ', ',', '-', '.', ':', ';', '(', ')', '[', ']', '!', '?' , STREND};

	token = mystrpbrk(censorship, delimiters);
	++count;

	while (token != NULL)
	{
		if (count == number)
		{
			begin = token;
		}
		else if (count == (number + 1))
		{
			end = token;
		}
		token = mystrpbrk(token + 1, delimiters);
		++count;
	}

	if (count < number)
	{
		puts("Sorry but there is no word with such number.");
		return FAIL;
	}

	if (begin == NULL)
	{
		puts("Sorry but there is no word with such number.");
		return FAIL;
	}
	unsigned int n = begin - censorship;

	temp = mystrncpy(temp, censorship, begin - censorship);
	temp[n] = STREND;

	if (end == NULL)
	{
		end = censorship + len;
	}
	n = end - censorship;
	temp = mystrcat(temp, censorship + n);
	myprintf(temp);
	puts("");
	return temp;
}

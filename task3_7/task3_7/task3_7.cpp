
/*
* @file			task3_7.cpp
* @brief		Program delete words with defined numbers. For now it's delete 2 and 5 word

* Copyright 2014 by Yuliia Lyubchik Inc.,
*
* This software is the confidential and proprietary information
* of Yuliia Lyubchik. ("Confidential Information").  You
* shall not disclose such Confidential Information and shall use
* it only with permission from Yuliia.
*
*/


#include "stdafx.h"
#include "task3_7.h"	 /*defines prototypes of used in this file functions*/
#include <stdio.h>
#include <stdlib.h>




int main( )
{
	Interface();
#ifdef USE_MY_DLL
	if (Check_Loading_Library() == FAIL)
	{
		puts("Can't load library.");
		return (int)FAIL;
	}
#endif

	char* riadok = NULL;
	unsigned char retCode;
	char* result = NULL;		/*string after deleting words*/
	unsigned int count = 0;		/*the quantity of deleted words*/

	retCode = Input(&riadok);
	if (retCode == FAIL)
	{
		puts("Error occurs while trying to input string.");
		return (int)FAIL;
	}
	

	printf("String after censoring word number %u: \n", NUM1);
	result = Delete_bad_word(riadok, NUM1);
	if (result == NULL)
	{
		printf("sorry, can not delete word number %u.\n", NUM1);
	}
	
	++count; 

	printf("String after censoring words number %u and %u: \n", NUM1, NUM2);
	result = Delete_bad_word(result, NUM2 - count);
	if (retCode == NULL)
	{
		printf("sorry, can not delete word number %u.\n", NUM2);
	}
	

	free(riadok);
	system("pause");
	return MAIN_SUCCESS;

}


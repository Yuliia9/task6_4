#ifndef TASK3_7_H_
#define TASK3_7_H_

/*
*@file		task3_7.h
*@brief		header file that defines prototypes of functions used in file task3_7.cpp
*/

#include "stdafx.h"

const unsigned char FAIL = 0;
const unsigned char SUCCESS = 1;
const unsigned int MAIN_SUCCESS = 0;

/*number of words needed to be deleted in string*/
const unsigned int NUM1 = 2;
const unsigned int NUM2 = 5;

/*for choosing what library to use*/
//#define USE_STRING_H
#define USE_MY_LIB
//#define USE_MY_DLL

/**
* @brief				This function displays general information about program to users
* @param	void
* @return	void
*/
void Interface(void);


/*
* @brief					Function for inputing string
* @param	[in/out]		char** riadok - a pointer to null pointer to string for sentences
*
*@return	unsigned char	Return ERROR if error occurs while trying to allocate memory for string
							Return SUCCESS if string was inputed
*/
unsigned char Input(char** riadok);

/**
* @brief				This function checks if string dll library was loaded
* @param	void
* @return	void
*/
unsigned int Check_Loading_Library(void);

/**
* @brief				Function finds the longest word in sequence of sentences
* @param	[in]		char* riadok - a pointer to inputed sequence of sentences
[in/out]	char** word - a pointer to pointer to longest word in sentences
*
*/
unsigned int Get_longest_word(char* riadok, char** word);

/*
* @brief					Function for deleting defined by number word in string
* @param	[in/out]		char* censorship - a pointer to string for deleting words.
			[in]			unsigned int number - number of word in sentence needed to be deleted
*
*@return	unsigned char	Return ERROR if error occurs while trying to get access to string
							Return SUCCESS if word in string censorship was deleted 
*/
char* Delete_bad_word( char* censorship, unsigned int number);

#endif








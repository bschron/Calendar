//
//  Support Functions.h
//  calendar
//
//  Created by Bruno Chroniaris on 11/5/14.
//  Copyright (c) 2014 UNIUM automação. All rights reserved.
//

#ifndef __calendar__Support_Functions__
#define __calendar__Support_Functions__

#include "Headers.h"

/*This fucntion will return the maximum provided value*/
int max (int a, int b);
/*takes two integers as argument, returns the minimum value*/
int min (int a, int b);
/*This function will return the size of a provided string*/
int sizeOfStr (char *str);
/*this function will print the first part a provided string that is formated with the provided separator to the *dest pointer and will return the pointer to right after the next separator is reached*/
char* returnNextWord (char *dest, char *word, char separator);
/*insert a Node with the word as name and HashWord as index for each word on the string, on the provided list, and returns a pointer to the list*/
Node* listWords (char *words, Node *list);
/*removes break of line from str*/
void take_lbreak (char *str);
/*just like fgets, but removes the line break from end of string*/
void nbgets (char *str, int num, FILE *stream);
/*gets a integer from stdin*/
int getNumber (void);
/*returns a integer with the number of characters befor the '\0' character on provided str*/
int sizeOfStr (char *str);
/*scans the provided stream until the unwanted character is reached (or if EOF or end of array is reached), removes the character from stream and attributes the characters to provided str. returns -1 if provided stream is NULL or destination str is NULL, else, returns 0. Returns 1 if EOF is reached before the unwanted character*/
int unwantedgets (char *dest, int size, char unwanted, FILE *stream);

#endif /* defined(__calendar__Support_Functions__) */

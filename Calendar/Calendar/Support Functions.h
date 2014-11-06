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
/*This function will return the size of a provided string*/
int sizeOfStr (char *str);
/*this function will print the first part a provided string that is formated with the provided separator to the *dest pointer and will return the pointer to right after the next separator is reached*/
char* returnNextWord (char *dest, char *word, char separator);
/*insert a Node with the word as name and HashWord as index for each word on the string, on the provided list, and returns a pointer to the list*/
Node* listWords (char *words, Node *list);

#endif /* defined(__calendar__Support_Functions__) */

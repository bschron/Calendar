//
//  Object List.h
//  Calendar
//
//  Created by Bruno Chroniaris on 11/19/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#ifndef __Calendar__Object_List__
#define __Calendar__Object_List__

#include "Headers.h"

/*returns the values of a TWC with empty flags.*/
TWC returnEmptyTWC (void);
/*Allocates a TWC with empty values and returns a pointer to it.*/
TWC* createEmptyTWC (void);
/*Takes a void pointer to object as argument. Creates a TWC and inserts the provided object.*/
TWC* createTWC (void *object);
/*Takes a pointer to TWC first and a pointer to TWC new as arguments. Inserts the provided new TWC as the first on the provided list and returns a pointer to it. If provided new pointer is NULL, returns the provided pointer to first.*/
TWC* insertTWC (TWC *first, TWC *new);
/*Takes a pointer to TWC first and a pointer to TWC remove as arguments. Where first is the first element from that list and remove is the element to be removed. Removes and frees that element from the list and returns a pointer to the first element of the list.*/
TWC* removeTWC (TWC* first, TWC *remove);
/*Takes a double pointer to the frist element of the TWC list. Frees every element on that list and attributes NULL to the provided pointer.*/
void freeAllTWC (TWC **first);
/*Takes a pointer to (TWC) the first element from the objectList as argument. Returns a integer representing the number of elements on the provided list.*/
int objectListLength (TWC* first);
/*Takes a double pointer to TWC first as argument. first is the first element from a provided object list, removes the first TWC from the provided list and returns a pointer to it's object.*/
void* popObject (TWC **first);
/*Takes a pointer to TWC *capsule as argument. Returns a pointer to the next TWC in list, NULL if there is none. Returns ERROR if provided pointer is NULL.*/
TWC* peekNextTWC (TWC *capsule);

#endif /* defined(__Calendar__Object_List__) */

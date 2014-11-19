//
//  AVL test cases.h
//  Calendar
//
//  Created by Bruno Chroniaris on 11/19/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#ifndef __Calendar__AVL_test_cases__
#define __Calendar__AVL_test_cases__

#include "Headers.h"


/*
 This is a function that executes all the test cases for a AVL. Will print detailed data about each test cases, where 1 is sucessful and 0 is not. Returns 0 if all test cases are OK, 1 if not.
 Tests for:
 - insertion
 - removal
 - balancing
 - possibles data loss
*/
int avlTestCases (EventBinarySearchTree *root);

/*Takes pointer to EventBinarySearchTree root, pointer to EventBinarySearchTree data, int nOfData and pointer to inserting function as arguments. inserts every data provided by data pointer to the tree root using the function insert and returns a pointer to root. Ends when data is NULL or nOfData is less or equal to zero, wich one comes first.*/
EventBinarySearchTree* insertDataToEventBinarySearchTree (EventBinarySearchTree *root, EventBinarySearchTree *data, int nOfData, void (*insert) (EventBinarySearchTree**, EventBinarySearchTree*));
/*Takes a pointer to Event events and a integer nOfEvents as arguments. Inserts nOfEvents events to the provided Event pointer and returns it. Stops when reaches provided nOfEvents.*/
Event* createRandomSetOfEvents (Event *events, int nOfEvents);

#endif /* defined(__Calendar__AVL_test_cases__) */

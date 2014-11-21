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
 - balancing
 - searching
 - removal
 - possibles data loss
*/
int avlTestCases (void);

/*Takes pointer to EventBinarySearchTree root, pointer to EventBinarySearchTree parent, pointer to EventBinarySearchTree data, int nOfData and pointer to inserting function as arguments. inserts every data provided by data pointer to the tree root using the function insert and returns a pointer to root. Ends when data is NULL or nOfData is less or equal to zero, wich one comes first.*/
EventBinarySearchTree* insertDataToEventBinarySearchTree (EventBinarySearchTree *root, EventBinarySearchTree *parent, Event *data, int nOfData, void (*insert) (EventBinarySearchTree**, EventBinarySearchTree*, EventBinarySearchTree *));
/*Takes a pointer to Event events and a integer nOfEvents as arguments. Inserts nOfEvents events to the provided Event pointer and returns it. Stops when reaches provided nOfEvents.*/
Event* createRandomSetOfEvents (Event *events, int nOfEvents);
/*takes a pointer to Event as argument and returns the number of events on that list (must provide pointer to the first item of the list). Returns 0 if provided pointer is NULL.*/
int eventListLength (Event *list);
/*Takes a pointer to EventBinarySearchTree root and a pointer to Event list as arguments. checks is every element on the provided list is also on the provided EventBinarySearchTree, returns 1 if so, 0 if not.*/
int checkIfGotEveryEventFromList (EventBinarySearchTree *root, Event *list);
/*Takes a integer result and a pointer to EventBinarySearchTree root as arguments. Runs the whole provided tree, calculating the balance factor, decreases the value of result by one for every unbalanced found spot. Returns result value unchanged if tree is completely balanced or if tree is NULL.*/
int checkIfEveryNodeIsBalanced (int result, EventBinarySearchTree *root);
/*Takes a integer result, double pointer to EventBinarySearchTree root and a pointer to Event list as arguments. Searches each element of list on the *root tree, if found event does not mach the provided, descreases the result by one, returns the new value of result. Returns result value unchanged if every elements on the provided list is found on the provided tree. Returns result value increased by one if provided root is NULL.*/
int checkSearching (int result, EventBinarySearchTree **root, Event *list);
/*Takes a integer result, a pointer to Event list, a integer nOfData and a pointer to function insert as arguments. inserts the provided list of events to a EventBinarySearchTree using the providede insert function and removes event by event, checking if the event was really removed. Decreases result by one if event was not removed as expected. Returns value of result. Value of result is returned unchanged if every EventBinarySearchTree is removed as expected.*/
int checkRemoval (int result, Event *list, int nOfData, void (*insert) (EventBinarySearchTree **, EventBinarySearchTree *, EventBinarySearchTree *));
/*Takes a integer result, a pointer to Event list, a integer nOfData and a pointer ot function insert as arguments. Creates a EventBinarySearchTree with every element on the provided list, using the provided inserting function, removes every element on it and checks the balance for every element remove from the tree. For any element removed imbalance found on the tree, decreases the result by one. Returns result decreased by one if provided list is NULL. Returns result value unchanged if no imbalance is found.*/
int checkRemovalBalance (int result, Event *list, int nOfData, void (*insert) (EventBinarySearchTree **, EventBinarySearchTree *, EventBinarySearchTree *));

#endif /* defined(__Calendar__AVL_test_cases__) */

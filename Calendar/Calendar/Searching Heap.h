//
//  Searching Hp.h
//  Calendar
//
//  Created by Bruno Chroniaris on 11/6/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#ifndef __Calendar__Searching_Hp__
#define __Calendar__Searching_Hp__

#include "Headers.h"

/*returns the value of the node parend one a hp, will return -1 if it's root*/
int hpParent (int child);
/*returns the valie of the node left child*/
int hpLeftChild (int parent);
/*returns the valie of the node right child*/
int hpRightChild (int parent);
/*returns a pointer to a new SearchingHp with empty values and flags*/
SearchingHp* createEmptyHp (void);
/*sets all pointer values to NULL and priority values to -1, and length to 0*/
void initializeSearchingHp (SearchingHp *hp);
/*enqueues event on the SearchingHp and calls hpfy, but if it already exists, will increase it's priority instead and calls hpdy*/
SearchingHp* enqueueSearchingHp (SearchingHp *hp, Event *item);
/*requires a pointer to the hp and the positon of the root or sub-root from wich will start the function*/
void hpfySearchingHp (SearchingHp *hp, int parent);
/*given two searching hp positions and a pointer to the hp, will switch the positions of the value and priorities of each item*/
void switchSearchingHpItems (SearchingHp *hp, int item1, int item2);
/*will deque the biggest element from the provided hp, hpfy the tree, and return the dequeued element. If the hp is empty or NULL, will return NULL*/
Event* dequeueSearchingHp (SearchingHp *hp);
/*requests the two SearchingHeap Childs and returns the one with biggest priority*/
int maxSearchingHpChild (SearchingHp *hp, int left, int right);
/*enqueues every single node from a EventBinarySearchTree to the provided heap. If the root is NULL, will return the with no changes made to the heap, else if the heap is null, will return NULL*/
SearchingHp* eventBinarySearchTreeToSearchingHp (SearchingHp *hp, EventBinarySearchTree *root);
/*enqueues every single node that's not a mirrored recurrency from a EventBinarySearchTree to the provided heap. If the root is NULL, will return the with no changes made to the heap, else if the heap is null, will return NULL*/
SearchingHp* eventBinarySearchTreeNotRecurrentToSearchingHp (SearchingHp *hp, EventBinarySearchTree *root);
/*enqueues every single node from the tree of a specific (defined by the hash variable) array position of the provided SearchTable. Creates a new heap, if the provided is NULL and will return the heap with no changes if it satisfies one if the following conditions: provided table is NULL, provided hash variable is smaller than zero or bigger than the array size, that spoecific position of the array is NULL*/
SearchingHp* searchTableElementsToSearchingHp (SearchingHp *hp, SearchTable *table, int hash);
/*enqueues every single node that's not a recurrency from the tree of a specific (defined by the hash variable) array position of the provided SearchTable. Creates a new heap, if the provided is NULL and will return the heap with no changes if it satisfies one if the following conditions: provided table is NULL, provided hash variable is smaller than zero or bigger than the array size, that spoecific position of the array is NULL*/
SearchingHp* searchTableNotRecurrentElementsToSearchingHp (SearchingHp *hp, SearchTable *table, int hash);
/*enqueues events with a hash equal to the provided word. will create a new heap if the heap is NULL and return it unchanged if table is NULL or word is equal to ""*/
SearchingHp* enqueueEventsWithSimilarWord (SearchingHp *hp, SearchTable *table, char *word);
/*gets word by word from provided text and enqueues events with similar words, will create a new heap if the provided heap is NULL and return it unchanged if the provided table is NULL or the title is equal to ""*/
SearchingHp* enqueueEventsWithSimilarText (SearchingHp *hp, SearchTable *table, char *text);
/*will return the priority of the highest priority element on that heap. WIll return -1 if heap is NULL or if heap size is 0*/
int peekHpHighestPriority (SearchingHp *hp);
/*enqueues Events from provided table that occurs on provided date on provided SearchingHp. Creates a new heap if the provided is NULL and returns the provided heap value unchanged if the provided table is NULL or provided date is invalid*/
SearchingHp* enqueueEventsWithProvidedDate (SearchingHp *hp, SearchTable *table, int day, int month, int year);
/*takes a pointer to SearchingHp and a pointer to Date as argument. Enqueues events for the week of the provided Date to provided Searching Heap. If provided pointer to SarchingHp is NULL, allocates a new one. If Pointer to Date is NULL, gets the current Date of the computer.*/
SearchingHp* enqueueEventsForThisWeek (SearchingHp *hp, Date *now);
/*takes a pointer to SearchingHp and a pointer to Date as argument. Enqueues events for the month of the provided Date to provided Searching Heap. If provided pointer to SarchingHp is NULL, allocates a new one. If Pointer to Date is NULL, gets the current Date of the computer.*/
SearchingHp* enqueueEventsForThisMonth (SearchingHp *hp, Date *now);
/*takes a pointer to a SearchingHp as argument, returns a pointer to a new Searching heap with the same values as the provided SearchingHeap. if the provided pointer is NULL, returns NULL*/
SearchingHp* duplicateSearchingHp (SearchingHp *hp);
/*takes a pointer to SearchingHp *hp, a integer position, a double pointer to Event **object and a pointer to integer *priority as arguments. Navigates to the required position of the required heap, attributes it's object and priority to it. Returns a pointer to that position's heap.*/
SearchingHp* getRightSearchingHeapItem (SearchingHp *hp, int position, Event **object, int *priority);
/*Takes a double pointer to SearchingHp **hp as argument. Navigates until the last heap and free's it if it's empty. This function is for memory saving onyl.*/
void cleanHp (SearchingHp **hp);
/*Takes a pointer to SearchingHp *hp and a integer position that represents the desired item's position on that heap. Returns a integer representing the priority of the required item.*/
int returnSearchingHeapItemPriority (SearchingHp *hp, int position);
/*Takes a pointer to SearchingHp *hp and a integer position that represents the desired item's position on that heap. Returns a pointer to the required position's item.*/
Event* returnSearchingHeapItemItem (SearchingHp *hp, int position);
/*Takes a pointer to SearchingHp *hp as argument. Returns a integer representing the number of positions totally allocated for the provided heap.*/
int totalHpSize (SearchingHp *hp);
/*Takes a pointer to SearchingHp *hp, a integer position, a pointer to Event *object and a integer priority as arguments. Attributes the provided object and the provided priority to the provided hp on the provided position.*/
void attributeInfoToSearchingHpPosition (SearchingHp *hp, int position, Event* object, int priority);
/*Takes a double pointer to SearchingHp **hp as argument. Frees the provided *hp and any *hp that comes after it on the list.*/
void freeSearchingHp (SearchingHp **hp);

#endif /* defined(__Calendar__Searching_Hp__) */

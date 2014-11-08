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
/*enqueues every single node from the tree of a specific (defined by the hash variable) array position of the provided SearchTable. Creates a new heap, if the provided is NULL and will return the heap with no changes if it satisfies one if the following conditions: provided table is NULL, provided hash variable is smaller than zero or bigger than the array size, that spoecific position of the array is NULL*/
SearchingHp* searchTableElementsToSearchingHp (SearchingHp *hp, SearchTable *table, int hash);
/*enqueues events with a hash equal to the provided word. will create a new heap if the heap is NULL and return it unchanged if table is NULL or word is equal to ""*/
SearchingHp* enqueueEventsWithSimilarWord (SearchingHp *hp, SearchTable *table, char *word);
/*gets word by word from provided text and enqueues events with similar words, will create a new heap if the provided heap is NULL and return it unchanged if the provided table is NULL or the title is equal to ""*/
SearchingHp* enqueueEventsWithSimilarText (SearchingHp *hp, SearchTable *table, char *text);

#endif /* defined(__Calendar__Searching_Hp__) */

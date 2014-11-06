//
//  Searching Heap.h
//  Calendar
//
//  Created by Bruno Chroniaris on 11/6/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#ifndef __Calendar__Searching_Heap__
#define __Calendar__Searching_Heap__

#include "Headers.h"

/*returns the value of the node parend one a heap, will return -1 if it's root*/
int heapParent (int child);
/*returns the valie of the node left child*/
int heapLeftChild (int parent);
/*returns the valie of the node right child*/
int heapRightChild (int parent);
/*returns a pointer to a new SearchingHeap with empty values and flags*/
SearchingHeap* createEmptyHeap (void);
/*sets all pointer values to NULL and priority values to -1, and length to 0*/
void initializeSearchingHeap (SearchingHeap *heap);
/*enqueues event on the SearchingHeap and calls heapfy, but if it already exists, will increase it's priority instead and calls heapdy*/
SearchingHeap* enqueueSearchingHeap (SearchingHeap *heap, Event *item);
/*requires a pointer to the heap and the positon of the root or sub-root from wich will start the function*/
void heapfySearchingHeap (SearchingHeap *heap, int parent);
/*given two searching heap positions and a pointer to the heap, will switch the positions of the value and priorities of each item*/
void switchSearchingHeapItems (SearchingHeap *heap, int item1, int item2);

#endif /* defined(__Calendar__Searching_Heap__) */

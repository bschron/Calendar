//
//  Structs.h
//  calendar
//
//  Created by Bruno Chroniaris on 11/5/14.
//  Copyright (c) 2014 UNIUM automação. All rights reserved.
//

#ifndef calendar_Structs_h
#define calendar_Structs_h

#include "Headers.h"

typedef struct calendar Calendar;
typedef struct event Event;
typedef struct sTable SearchTable;
typedef struct dTable DayTable;
typedef struct mTable MonthTable;
typedef struct eventBinarySearchTree EventBinarySearchTree;
typedef struct node Node;
typedef struct searchingHeap SearchingHeap;

struct calendar
{
    Event *events;
};

struct event
{
    Event *next;
    Event *previous;
    
    char title[Max];
    char desc[description];
    int day;
    int month;
    int year;
};

struct sTable
{
    EventBinarySearchTree *table[SearchTableSize];
};

struct dTable
{
    EventBinarySearchTree *root;
};

struct mTable
{
    EventBinarySearchTree *root;
    DayTable *day[31];
};

struct eventBinarySearchTree
{
    Event *event;
    int nameHash;
    
    EventBinarySearchTree *leftChild;
    EventBinarySearchTree *rightChild;
};

struct node
{
    Node* previous;
    Node* next;
    char name[Max];
    int index;
};

struct searchingHeap
{
    Event *heap[SearchHeapSize];
    int priority[SearchHeapSize];
    int heapLength;
};

#endif

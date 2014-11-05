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
typedef struct eventBinarySearchTree EventBinarySearchTree;

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
    Event *table[SearchTableSize];
};

struct eventBinarySearchTree
{
    Event *event;
    int nameHash;
    int tieBreakerFactor;
    
    EventBinarySearchTree *leftChild;
    EventBinarySearchTree *rightChild;
};

#endif

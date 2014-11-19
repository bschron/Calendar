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
typedef struct searchingHp SearchingHp;
typedef struct date Date;
typedef struct eventQueue EventQueue;
typedef struct eventCapsule EventCapsule;
typedef struct priorityQueue PriorityQueue;
typedef struct priorityQueueCapsule PQC;
typedef struct twoWayCapsule TWC;

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
    Date *date;
    
    int recurrency;//0 is not recurrent, >0 is recurrent root, <0 is not root. 1/-1 is weekly recurrency, 2/-2 is monthly recurrency, 3/-3 is yearly recurrency
    int *frequency;
    Event *recurrences;
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
    char name[Max*5];
    int index;
};

struct searchingHp
{
    Event *hp[SearchHpSize];
    int priority[SearchHpSize];
    int hpLength;
};

struct date
{
    int day;
    int month;
    int year;
};

struct eventQueue
{
    EventCapsule *first;
    EventCapsule *last;
    int queueLength;
    
};

struct eventCapsule
{
    Event *event;
    EventCapsule *next;
    EventCapsule *previous;
};

struct priorityQueue
{
    PQC *first;
    int length;
};

struct priorityQueueCapsule
{
    void *object;
    PQC *next;
    int priority;
};

struct twoWayCapsule
{
    void *object;
    TWC *next;
    TWC *previous;
};

#endif

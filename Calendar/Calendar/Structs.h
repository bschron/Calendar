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


typedef struct calendar Calendar;/*Calendar is a structure that contains a pointer to a list of events, that belongs to that calendar.*/

typedef struct event Event;
/*
 Event is a double linked list item that's usually attributed to a Calendar, but may also be used alone for other purposes.
 
 Event *next points to the Event on the list that comes right after the current Event. If there is no next event, it's value is set to NULL.
 Event *previous pointer to the Event on the list that comes right befose the current Event. If there is no previous event, it's value is set to NULL.
 
 char title[Max] represents the event title.
 char desc[description] represents the event description.
 Date *date represents this event's ocurring date.
 
 int recurrency is a flag that indicates the recurrency mode for this Event.
    0 = Event is defined as not recurrent
    1 or -1 = weekly recurrency
    2 or -2 = monthly recurrency
    3 or -3 = yearly recurrency
    recurrency Values lesser than zero represents that the current event is just a mirrored recurrence of the original event, that has the value bigger than zero.
 
 int *frequency is used as array that stores the data indicating that event's frequency. frequency may assume the following formats:
    NULL = Event is not recurrent or a mirrored recurrence
    frequency[7] = weekly recurrency
        each position represents a day of week, sunday-saturday, 1 flags that the event occurs on that day, 0 flags that the event does not occur on that day.
    frequency[31] = monthly recurrency
        each position represents a day of month, 1-31, 1 flags that the event occurs on that day, 0 flags that the event does not occur on that day.
            Warning.: events scheduled for days 29-31 may not occur on some months, depening on the month's length.
    frequency[2] = yearly recurrence
        Represents the day and month on year that this event occurs. Frequency[0] represents the day and frequency[1] the month.
            Warning.: events scheduled 29/02 may not occur on non-leap years
 
 Event *recurrences may assume two functions:
    - Points to a list of mirrored recurrences for this current Event, if it's a main event.
    - Points the main Event from wich this Event is mirrored from, if it's a mirrored event.
*/

typedef struct sTable SearchTable;
/*
 SearchTable is a table used for mapping events, making it easier to search, edit and remove events without loosing speed. The conflicts are solved using a binary search tree EventBinarySearchTree.
*/

typedef struct eventBinarySearchTree EventBinarySearchTree;
/*
 EventBinarySearchTree is a balanced (AVL) binary search tree. The key used is the memory address of the tree.
 
 Event *event is a pointer to the trees content.
 int nameHash is the sum of the title's hash and description's hash. Useful for debugging, helps keeping track of trees and drwaing trees. It's a not unique, but really useful way of identifying a tree.
 
 EventBinarySearchTree *leftChild is the left child of the tree. Is defined as NULL if there is none
 EventBinarySearchTree *rightChild is the right child of the tree. Is defined as NULL if there is none
 EventBinarySearchTree **parent, is the parent of the current tree. Watch this double pointer, it's allocated when tree is created and freed when tree is removed, it's allocated even when there is no parent. When current Tree is root, *parent has a value of NULL
*/

typedef struct node Node;
/*
 Node is a double linked list that contains a string and a integer as contents. Really useful for simple tasks.
 
 Node *previous points to the node that comes right before on the list, is defined as NULL if there is no previous node.
 Node *next points to the node that comes right after on the list, is defined as NULL if there is no next node.
 char name[] is the string content of the node
 int index is the integer contente of the node
*/

typedef struct searchingHp SearchingHp;
/*
 SearchingHp is a MAX-Heap priority Queue that contains a Event* as object. When a event is enqueued for the first time on that SearchingHp, it's priority is defined as 1 and is increased by one each time that event is provided to be added to that tree, but it's not added again thou. It's really useful for searching elements on search table and only get the elements that has the maximum matching cases, wich are most problably the desired ones.
 
 SearchingHp is not a simple static heap, it increases in size and links to another heaps when more space is needed. A first, primary, heap is created for regular usage, but when the heap is getting FULL, the program allocates a new SearchingHp that's only used for storage and links it to the primary heap using "*next", that's heap priority is defined as 1. This secondary heap will also allocates a new heap for storage when more space is needed.
 
 Event *hp[] is the array for storing the events, empty positions are defeined as NULL
 int priority[] is the array for storing the *hp[] priorities, empty positions are defined as -1
 int hpLength is the length of the heap, is defined as 0 when the heap is NULL. This value is only real when refering to the primary heap, the other accessories heaps that are used for storage has this value set as 0
 int hpNumber is the number of the heap, the primary heap is defined as 0, secondary is 1, tertiary is 2...
 SearchingHp *previous points to the heap used for storage that comes right before this current heap
 SearchinHp *next pointer to the heao used for storaged that comes right after this current heap
*/

typedef struct date Date;
/*
 Date is a simple calendar date, dd/mm/yyyy, has 3 integers as content
 
 int day is the integer that represents the date's day
 int month is the integer that represents the date's month
 int year is the integer that represents the date's year
*/

typedef struct eventQueue EventQueue;
/*
 Is a double linked simple queue that has Event* as object. This functions is used when FIFO is needed, really useful the needs to enqueue events by day's order, day by day.
 
 EventCapsule *first points to the structure that holds the first element of that queue, is defined as NULL when queue is empty
 EventCapsule *last points to the structure that holds the last element of that queue, is defined as NULL when queue is empty
 int queueLength represents the length of the queue, is defined as 0 when queue is empty
*/

typedef struct eventCapsule EventCapsule;
/*
 EventCapsule is a structure used for holding and enlisting a event without affecting the event's main list (e.g Calendar), it's used on EventQueues.
 
 Event *event points to the capsule's Event object
 EventCapsule *next points to the next capsule on that list, is defined as NULL when there is no next capsule
 EventCapsule *previous points to the previous capsule on that list, is defined as NULL when there is no next capsule
*/

typedef struct priorityQueue PriorityQueue;
/*
 PriorityQueue is a simple dynamic priority queue that's not attached to any particular type, it holds a list of PQC (Priority Queue Capsule) that has void* pointer as object.
 
 PQC *first points to the first capsule on the queue, is defined as NULL when the queue is NULL
 int length represents the length of the queue, is defined as 0 when the queue is empty
*/

typedef struct priorityQueueCapsule PQC;
/*
 PQC (Priority Queue Capsule) is a capsule for holding a object of any tipe, defined by a priority.
 
 void *object points the the capsule's object
 PQC *next points to the capsule on the list that's right after the current, is defined as NULL if there is no next capsule
 int priority is the priority of the capsule
*/

typedef struct twoWayCapsule TWC;
/*
 TWC (Two Way Capsule) is a capsule for holding a object of any type, used for making a double linked list of objects.
 
 void *object points the the capsule's object
 TWC *next points to the capsule on the list that's right after the current, is defined as NULL if there is no next capsule
 TWC *previous points to the capsule on the list that's right before the current, is defined as NULL if there is no previous capsule
*/

struct twoWayCapsule
{
    void *object;
    TWC *next;
    TWC *previous;
};

#endif

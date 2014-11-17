//
//  Object Priority Queue.h
//  Calendar
//
//  Created by Bruno Chroniaris on 11/17/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#ifndef __Calendar__Object_Priority_Queue__
#define __Calendar__Object_Priority_Queue__

#include "Headers.h"

//PQC
/*returns the value of a PQC with empty flags*/
PQC returnEmptyPQC (void);
/*Allocates a new PQC, attributes empty flagged values and returns a pointer to it.*/
PQC* createEmptyPQC (void);
/*Takes a void pointer to a object and a integer representing that object's priority as arguments. Allocates a new PQC, attributes the provided object and priority, and returns a pointer to it.*/
PQC* createPQC (void *object, int priority);

//Priority Queue (PriorityQueue is a min-priority queue that takes objects from any type, pointer to object and the object's priority must be provided.)
/*Allocates a new PriorityQueue, attributes empty queue values and returns a pointer to it.*/
PriorityQueue* createPriorityQueue (void);
/*Takes a pointer to the PriorityQueue, a pointer to the PQC, a void pointer to the object and a integer representing the objects priority as arguments. Enqueues the provided capsule/object to the provided queue and returns a pointer to the queue. Creates a new queue if the provided is NULL. Creates a new capsule, if the provided is NULL, and attributes the provided object and priprity to it. Ignores the pointer to object and integer priority if the provided capsule is not NULL.*/
PriorityQueue* enqueuePriorityQueue (PriorityQueue *queue, PQC* capsule, void* object, int priority);
/*Takes a pointer to the first PQC from the queue and a pointer to the new PQC. Inserts the new PQC in the right priority prosition and returns a pointer to the first PQC.*/
PQC* insertInRightPosition (PQC *first, PQC* capsule);

#endif /* defined(__Calendar__Object_Priority_Queue__) */

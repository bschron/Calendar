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
/*Takes a pointer to a PriorityQueue as argument. Frees the first capsule in line, decreases the queue length by 1, and returns a pointer to it's object.*/
void* dequeuePriorityQueue (PriorityQueue *queue);
/*Takes a double pointer to PriorityQueue as argument. Dequeues all elements from provided queue, frees the queue and attributes NULL to it's pointer. Returns unchanged if the provided double pointer is NULL or if the single pointer is NULL.*/
void freePriorityQueue (PriorityQueue **queue);
/*Takes a pointer to PriorityQyeye and a pointer to Date as arguments. Searches for events on the provided date and n-1 days after that, enqueues them to a Searching heap than enqueues to PriorityQueue, ordered by date, returns pointer to this queue. Creates a new queue if provided is NULL. Gets computers current time if provided startingDate is NULL. Returns empty queue is provided remaining days is lesser or equal to one. Frees the provided Date.*/
PriorityQueue* enqueuePriorityQueueEventsForNextNDays (PriorityQueue *queue, Date *startingDate, int remainingDays);
/*Takes a pointer to PriorityQueue as argument. Calculates the remaining days in this week (includes next sunday) and calls enqueuePriorityQueueEventsForNextNdays to that queue for the remaining days in week.*/
PriorityQueue* enqueuePriorityQueueEventsForThisWeek (PriorityQueue *queue);

//transfering
/*Takes a pointer to PriorityQueue and a pointer to SearchingHp as arguments. Dequeues the provided SearchingHp and inserts it's events into the provided PriorityQueue, the priority will be defined by distance between computer's current time and the event date. Returns a pointer to the PriorityQueue. Returns the provided queue unchanged if the provided SearchingHp is NULL or if it's length is equal or lesser to zero. Creates a new PriorityQueue if the provided is NULL.*/
PriorityQueue* searchingHpToPriorityQueueOrderedByDate (PriorityQueue *queue, SearchingHp *hp);
/*Takes two pointers to PriorityQueues as arguments. Allocates a new capsule for every capsule in the provided sourec queue, attributes it's objects and priorities to it and returns a pointer to the destination queue. Returns the destination queue unchanged if the provided source is NULL. Creates a new destination PriorityQueue if the provided is NULL.*/
PriorityQueue* copyPriorityQueue (PriorityQueue *dest, PriorityQueue *source);

#endif /* defined(__Calendar__Object_Priority_Queue__) */

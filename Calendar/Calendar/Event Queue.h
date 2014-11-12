//
//  Event Queue.h
//  Calendar
//
//  Created by Bruno Chroniaris on 11/12/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#ifndef __Calendar__Event_Queue__
#define __Calendar__Event_Queue__

#include "Headers.h"
/*returns the values of a empty event queue*/
EventQueue returnEmptyEventQueue (void);
/*returns a pointer to a new EventQueue*/
EventQueue* createEmptyQueue (void);
/*takes a pointer to EventQueue and a pointer to Event, enqueues the provided event on the provided queue, increases the queue length and returns a pointer to the EventQueue. Returns the queue unchanged if the provided pointer to event is NULL. Creates a new empty queue and recursively calls it self, if the proviede queue is NULL.*/
EventQueue* enqueueEventQueue (EventQueue *queue, Event *event);
/*takes a pointer to EventQueue as argument. Removes the first element from the queue, decreases the queue length, and returns the returns a pointer to the dequeued event. Returns NULL if provided pointer to EventQueue is NULL, if provided EventQueue length is equal or lesser to zero or if the first element of the EventQueue is NULL.*/
Event* dequeueEventQueue (EventQueue *queue);

#endif /* defined(__Calendar__Event_Queue__) */

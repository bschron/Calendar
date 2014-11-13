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
/*Takes a int representing the number of days to be printed, a pointer to EventQueue and a Pointer to Date as arguments. This function will print every event in the period of N days after the provided date. The function enqueues every event, day by day, of that time period, dequeues it, and enqueue to the provided EventQueue, preserving the date order. Creates a new EventQueue if the provided is NULL. Gets the current time, if the provided is NULL. Returns the queue unchanged if the provided number of days is 0. Returns a pointer to the provided queue.*/
EventQueue* eventQueueEnqueueEventsForNDays (int numberOfDays, EventQueue *queue, Date *now);
/*Takes a pointer to EventQueue as argument. Calculastes the remaining days on the current week and calls eventQueueEnqueueEventsForNDays, for that whole week. Returns a pointer to the EventQueue.*/
EventQueue* eventQueueEnqueueEventsForThisMonth (EventQueue *queue);
/*Takes a pointer to EventQueue as argument. Calculastes the remaining days on the current month and calls eventQueueEnqueueEventsForNDays, for that whole month. Returns a pointer to the EventQueue.*/
EventQueue* eventQueueEnqueueEventsForThisWeek (EventQueue *queue);

#endif /* defined(__Calendar__Event_Queue__) */

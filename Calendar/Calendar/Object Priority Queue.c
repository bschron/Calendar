//
//  Object Priority Queue.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/17/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Object Priority Queue.h"

PQC returnEmptyPQC (void)
{
    PQC empty;
    empty.next = NULL;
    empty.object = NULL;
    empty.priority = 0;
    
    return empty;
}

PQC* createEmptyPQC (void)
{
    PQC *new = (PQC*) malloc(sizeof(PQC));
    
    *new = returnEmptyPQC();
    
    return new;
}

PQC* createPQC (void *object, int priority)
{
    PQC *new = (PQC*) malloc(sizeof(PQC));
    
    new->next = NULL;
    new->priority = priority;
    new->object = object;
    
    return new;
}

PriorityQueue* createPriorityQueue (void)
{
    PriorityQueue *new = (PriorityQueue*) malloc(sizeof(PriorityQueue));
    
    new->first = NULL;
    new->length = 0;
    
    return new;
}

PriorityQueue* enqueuePriorityQueue (PriorityQueue *queue, PQC* capsule, void* object, int priority)
{
    if (queue == NULL)
    {
        return enqueuePriorityQueue(createPriorityQueue(), capsule, object, priority);
    }
    else if (capsule == NULL)
    {
        return enqueuePriorityQueue(queue, createPQC(object, priority), object, priority);
    }
    
    if (queue->length <= 0)
    {
        capsule->next = NULL;
        queue->first = capsule;
    }
    else
    {
        queue->first = insertInRightPosition(queue->first, capsule);
    }
    
    (queue->length)++;
    
    return queue;
}

PQC* insertInRightPosition (PQC *first, PQC* capsule)
{
    if (first == NULL)
    {
        capsule->next = NULL;
        first = capsule;
    }
    else if (first->priority >= capsule->priority)
    {
        capsule->next = first;
        first = capsule;
    }
    else
    {
        first->next = insertInRightPosition(first->next, capsule);
    }
    
    
    return first;
}

void* dequeuePriorityQueue (PriorityQueue *queue)
{
    if (queue == NULL)
    {
        return NULL;
    }
    else if (queue->length <= 0)
    {
        return NULL;
    }
    
    PQC *dequeuedCapsule = queue->first;
    void *dequeued = queue->first->object;
    
    queue->first = queue->first->next;
    
    (queue->length)--;
    
    free(dequeuedCapsule);
    
    return dequeued;
}

PriorityQueue* searchingHpToPriorityQueueOrderedByDate (PriorityQueue *queue, SearchingHp *hp)
{
    if (hp == NULL)
    {
        return queue;
    }
    else if (hp->hpLength <= 0)
    {
        return queue;
    }
    else if (queue == NULL)
    {
        return searchingHpToPriorityQueueOrderedByDate(createPriorityQueue(), hp);
    }
    
    Event *object = dequeueSearchingHp(hp);
    Date *now = getDate(NULL);
    
    queue = enqueuePriorityQueue(queue, NULL, object, daysBetweenDates(object->date, now));
    
    free(now);
    return searchingHpToPriorityQueueOrderedByDate(queue, hp);
}

void freePriorityQueue (PriorityQueue **queue)
{
    if (queue == NULL)
    {
        return;
    }
    else if (*queue == NULL)
    {
        return;
    }
    else if ((*queue)->length > 0)
    {
        dequeuePriorityQueue(*queue);
        return freePriorityQueue(queue);
    }
    
    free(*queue);
    
    *queue = NULL;
    
    return;
}

PriorityQueue* copyPriorityQueue (PriorityQueue *dest, PriorityQueue *source)
{
    if (source == NULL)
    {
        return dest;
    }
    else if (dest == NULL)
    {
        return copyPriorityQueue(createPriorityQueue(), source);
    }
    
    PQC *capsule;
    
    for (capsule = source->first; capsule!= NULL; capsule = capsule->next)
    {
        dest = enqueuePriorityQueue(dest, NULL, capsule->object, capsule->priority);
    }
    
    return dest;
}

PriorityQueue* enqueuePriorityQueueEventsForNextNDays (PriorityQueue *queue, Date *startingDate, int remainingDays)
{
    if (queue == NULL)
    {
        return enqueuePriorityQueueEventsForNextNDays(createPriorityQueue(), startingDate, remainingDays);
    }
    else if (startingDate == NULL)
    {
        return enqueuePriorityQueueEventsForNextNDays(queue, getDate(NULL), remainingDays);
    }
    else if (remainingDays <= 0)
    {
        free(startingDate);
        return queue;
    }

    SearchingHp *hp = enqueueEventsWithProvidedDate(NULL, dateSearchTable, startingDate->day, startingDate->month, startingDate->year);
    
    queue = searchingHpToPriorityQueueOrderedByDate(queue, hp);
    
    free(hp);
    
    return enqueuePriorityQueueEventsForNextNDays(queue, increaseDate(startingDate), remainingDays-1);
}

PriorityQueue* enqueuePriorityQueueEventsForThisWeek (PriorityQueue *queue)
{
    if (queue == NULL)
    {
        return enqueuePriorityQueueEventsForThisWeek(createPriorityQueue());
    }
    
    Date *now = getDate(NULL);
    int weekday = dayOfWeek(NULL, now);
    
    queue = enqueuePriorityQueueEventsForNextNDays(queue, now, 8-weekday);
    
    return queue;
}
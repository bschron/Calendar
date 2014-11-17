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
        return enqueuePriorityQueue(queue, createPQC(object, priority), NULL, not_in_use);
    }
    
    if (queue->length <= 0)
    {
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
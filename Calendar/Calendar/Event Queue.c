//
//  Event Queue.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/12/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Event Queue.h"

EventQueue* createEmptyQueue (void)
{
    EventQueue *new = (EventQueue*) malloc(sizeof(EventQueue));
    *new = returnEmptyEventQueue();
    return new;
}

EventQueue* enqueueEventQueue (EventQueue *queue, Event *event)
{
    if (event == NULL)
    {
        return queue;
    }
    else if (queue == NULL)
    {
        return enqueueEventQueue(createEmptyQueue(), event);
    }
    
    EventCapsule *new = createEmptyEventCapsule();
    new->event = event;
    
    if (queue->queueLength == 0)
    {
        new->next = new->previous = NULL;
        queue->first = queue->last = new;
    }
    else
    {
        new->previous = queue->last;
        new->next = NULL;
        queue->last->next = new;
        queue->last = new;
    }
    
    (queue->queueLength)++;
    
    return queue;
}

EventQueue returnEmptyEventQueue (void)
{
    EventQueue empty;
    empty.first = NULL;
    empty.last = NULL;
    empty.queueLength = 0;
    
    return empty;
}

Event* dequeueEventQueue (EventQueue *queue)
{
    if (queue == NULL)
    {
        return NULL;
    }
    else if (queue->queueLength <= 0 || queue->first == NULL)
    {
        return NULL;
    }
    
    Event* event = queue->first->event;
    EventCapsule *dequeued = queue->first;
    
    if (queue->queueLength == 1)
    {
        queue->first = NULL;
        queue->last = NULL;
    }
    else
    {
        queue->first = queue->first->next;
        queue->first->previous = NULL;
    }
    
    (queue->queueLength)--;
    
    free(dequeued);
    
    return event;
}
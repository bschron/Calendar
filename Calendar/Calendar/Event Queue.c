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

EventQueue* eventQueueEnqueueEventsForNDays (int numberOfDays, EventQueue *queue, Date *now)
{
    if (queue == NULL)
    {
        return eventQueueEnqueueEventsForNDays(numberOfDays, createEmptyQueue(), now);
    }
    else if (now == NULL)
    {
        now = getDate(NULL);
        queue = eventQueueEnqueueEventsForNDays(numberOfDays, queue, now);
        free(now);
        return queue;
    }
    else if (numberOfDays == 0)
    {
        return queue;
    }
    
    SearchingHp *result = NULL;
    Event *dequeued = NULL;
    
    for (result = enqueueEventsWithProvidedDate(result, dateSearchTable, now->day, now->month, now->year); numberOfDays>0; numberOfDays--, now = increaseDate(now), result = enqueueEventsWithProvidedDate(result, dateSearchTable, now->day, now->month, now->year))
    {
        for (dequeued = dequeueSearchingHp(result); dequeued != NULL; dequeued = dequeueSearchingHp(result))
        {
            queue = enqueueEventQueue(queue, dequeued);
        }
    }
    
    free(result);
    
    return queue;
}

EventQueue* eventQueueEnqueueEventsForThisWeek (EventQueue *queue)
{
    Date *now = getDate(NULL);
    queue = eventQueueEnqueueEventsForNDays(7-dayOfWeek(NULL, now), queue, NULL);
    free(now);
    return  queue;
}

EventQueue* eventQueueEnqueueEventsForThisMonth (EventQueue *queue)
{
    Date *now = getDate(NULL);
    int nDays = (daysInMonth(now->month) - now->day) + 1;
    
    if (now->month == 2 && now->day < 29 && leapYear(now->year))
    {
        nDays++;
    }
    
    queue = eventQueueEnqueueEventsForNDays(nDays, queue, now);
    
    free(now);
    return queue;
}
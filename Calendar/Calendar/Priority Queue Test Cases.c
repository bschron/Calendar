//
//  Priority Queue Test Cases.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/21/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Priority Queue Test Cases.h"

PriorityQueue* insertDataToPriorityQueue (PriorityQueue *queue, Event *list, int startingPriority)
{
    if (list == NULL)
    {
        return queue;
    }
    else if (queue == NULL)
    {
        return insertDataToPriorityQueue(createPriorityQueue(), list, startingPriority);
    }
    
    queue = enqueuePriorityQueue(queue, NULL, list, startingPriority);
    
    return insertDataToPriorityQueue(queue, peekNextEvent(list), startingPriority+1);
}

int checkPQEnqueueing (Event *list, int listLength, int result)
{
    PriorityQueue *queue = createPriorityQueue();
    int notFound = 0;
    Event *current = NULL;
    Event *current2 = NULL;
    
    queue = insertDataToPriorityQueue(queue, list, 0);
    
    for (current = dequeuePriorityQueue(queue); current != NULL; current = dequeuePriorityQueue(queue))
    {
        for (notFound = 1, current2 = list; current2 != NULL; moveToNextEvent(&current2))
        {
            if (current == current2)
            {
                notFound = 0;
                break;
            }
        }
        if (notFound)
        {
            result--;
        }
    }
    
    freePriorityQueue(&queue);
    
    return result;
}

int PQTEstCases (void)
{
    int finalResult = 1;
    int n = 666;
    FILE *outputf = stdout;
    
    //preparing data list
    Event *events = createRandomSetOfEvents(NULL, n);
    
    for (n = 10; n <= 10; n++)
    {
        //Enqueueing and Dequeueing
        {
            int initial = 1;
            int result = checkPQEnqueueing(events, n, initial);
            fprintf(outputf, "Enqueueing and Dequeueing - %d\n", result/initial);
            if (result != initial)
            {
                finalResult--;
            }
        }
        
        //printing Queue
        {
            PriorityQueue *queue = enqueuePriorityQueueEventsForThisWeek(NULL);
            printEventsTitleOfObjectPriorityQueue(&queue);
        }
    }
    
    //final result
    fprintf(outputf, "Final Result - %d\n", finalResult);
    
    freeAllEvents(&events);
    
    return finalResult;
}


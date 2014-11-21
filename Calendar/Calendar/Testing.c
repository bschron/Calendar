//
//  Testing.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/17/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Testing.h"

void testing (void)
{
    int priority = 0;
    Event *list = createRandomSetOfEvents(NULL, 666);
    Event *current = NULL;
    
    PriorityQueue *queue = createPriorityQueue();
    
    for (current = list, priority = 0; current != NULL; current = current->next, priority++)
    {
        queue = enqueuePriorityQueue(queue, NULL, current, priority);
    }
    
    PriorityQueue *queue2 = NULL;
    
    for (current = list, priority = 666; current != NULL; priority--, current = current->next)
    {
        queue = enqueuePriorityQueue(queue, NULL, current, priority);
    }
    
    freeAllEvents(&list);
    
    freePriorityQueue(&queue);
    freePriorityQueue(&queue2);
    
    getchar();
}
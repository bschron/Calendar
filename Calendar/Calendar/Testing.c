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
    int objects[10], i;
    int priorities[10];
    PriorityQueue *queue = NULL;
    for (i=0; i<10; i++)
    {
        objects[i] = i+1;
        priorities[i] = 10-i;
    }
    
    queue = enqueuePriorityQueue(queue, NULL, objects+0, priorities[0]);
    queue = enqueuePriorityQueue(queue, NULL, objects+2, priorities[2]);
    queue = enqueuePriorityQueue(queue, NULL, objects+1, priorities[1]);
    queue = enqueuePriorityQueue(queue, NULL, objects+9, priorities[9]);
    queue = enqueuePriorityQueue(queue, NULL, objects+8, priorities[8]);
    queue = enqueuePriorityQueue(queue, NULL, objects+6, priorities[6]);
    queue = enqueuePriorityQueue(queue, NULL, objects+7, priorities[7]);
    queue = enqueuePriorityQueue(queue, NULL, objects+4, priorities[4]);
    queue = enqueuePriorityQueue(queue, NULL, objects+5, priorities[5]);
    queue = enqueuePriorityQueue(queue, NULL, objects+3, priorities[3]);
    
    getchar();
}
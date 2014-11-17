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
    
    queue = enqueuePriorityQueue(queue, NULL, &objects[0], priorities[0]);
    
    getchar();
}
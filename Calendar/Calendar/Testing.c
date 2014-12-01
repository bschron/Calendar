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
    int length = 22;
    
    Event* list = createRandomSetOfEvents(NULL, length);
    SearchingHp *hp = NULL;
    Event *current = NULL;
    Event *dequeued = NULL;
    int i, i2;
    
    for (i = 0; i < 10; i++)
    {
        for (current = list, i2 = 0; current != NULL && i2 < length-(i*i); moveToNextEvent(&current), i2++)
        {
            hp = enqueueSearchingHp(hp, current);
        }
    }
    
    for (dequeued = dequeueSearchingHp(hp); dequeued != NULL; dequeued = dequeueSearchingHp(hp));
    
    getchar();
}
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
    int length = 3;
    
    Event* list = createRandomSetOfEvents(NULL, length);
    SearchingHp *hp = NULL;
    Event *current = NULL;
    int i;
    
    for (i = 0; i < 2; i++)
    {
        for (current = list; current != NULL; current = current->next)
        {
            hp = enqueueSearchingHp(hp, current);
        }
    }
    
    getchar();
}
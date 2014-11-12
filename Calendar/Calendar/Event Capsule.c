//
//  Event Capsule.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/12/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Event Capsule.h"

EventCapsule* createEmptyEventCapsule (void)
{
    EventCapsule *new = (EventCapsule*) malloc(sizeof(EventCapsule));
    
    *new = returnEmptyCapsule();
    
    return new;
}

EventCapsule returnEmptyCapsule (void)
{
    EventCapsule empty;
    
    empty.event = NULL;
    empty.next = NULL;
    empty.previous = NULL;
    
    return empty;
}
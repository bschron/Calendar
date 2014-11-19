//
//  Object List.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/19/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Object List.h"

TWC returnEmptyTWC (void)
{
    TWC empty;
    empty.next = NULL;
    empty.object = NULL;
    empty.previous = NULL;
    
    return empty;
}

TWC* createEmptyTWC (void)
{
    TWC *new = (TWC*) malloc(sizeof(TWC));
    
    *new = returnEmptyTWC();
    
    return new;
}

TWC* createTWC (void *object)
{
    TWC *new = createEmptyTWC();
    
    new->object = object;
    
    return new;
}

TWC* insertTWC (TWC *first, TWC *new)
{
    if (new == NULL)
    {
        return first;
    }
    else if (first == NULL)
    {
        new->next = NULL;
        new->previous = NULL;
        return new;
    }
    
    new->next = first;
    first->previous = new;
    new->previous = NULL;
    
    return new;
}

TWC* removeTWC (TWC* first, TWC *remove)
{
    if (remove == NULL)
    {
        return first;
    }
    
    if (first == remove)
    {
        first = first->next;
        first->previous = NULL;
    }
    else if (remove->next == NULL)
    {
        remove->previous->next = NULL;
    }
    else
    {
        remove->previous->next = remove->next;
        remove->next->previous = remove->previous;
    }
    
    free(remove);
    return first;
}

void freeAllTWC (TWC **first)
{
    if (first == NULL)
    {
        return;
    }
    else if (*first == NULL)
    {
        return;
    }
    
    TWC **next = &(*first)->next;
    free(*first);
    *first = NULL;
    
    return freeAllTWC(next);
}
//
//  Object List.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/19/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Object List.h"

struct twoWayCapsule
{
    void *object;
    TWC *next;
    TWC *previous;
};

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
        if (first->next != NULL)
        {
            first->next->previous = NULL;
        }
        first = first->next;
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

int objectListLength (TWC* first)
{
    if (first == NULL)
    {
        return 0;
    }
    
    return objectListLength(first->next) + 1;
}

void* popObject (TWC **first)
{
    if (first == NULL)
    {
        return NULL;
    }
    else if (*first == NULL)
    {
        return NULL;
    }
    
    void *popped = (*first)->object;
    
    *first = removeTWC(*first, *first);
    
    return popped;
}

TWC* peekNextTWC (TWC *capsule)
{
    if (capsule == NULL)
    {
        return (TWC*) ERROR;
    }
    
    return capsule->next;
}
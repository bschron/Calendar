//
//  Searching Hp.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/6/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Searching Heap.h"

int hpParent (int child)
{
    if (child == 0)
    {
        return -1;
    }
    else if (child%2 == 0)
    {
        return (child>>1)-1;
    }
    else
    {
        return child>>1;
    }
}

int hpLeftChild (int parent)
{
    return (parent<<1) +1;
}

int hpRightChild (int parent)
{
    return (parent<<1) +2;
}

SearchingHp* createEmptyHp (void)
{
    SearchingHp *new = (SearchingHp*) malloc(sizeof(SearchingHp));
    
    initializeSearchingHp(new);
    
    return new;
}

void hpfySearchingHp (SearchingHp *hp, int parent)
{
    if (parent < 0 || hp == NULL || parent > SearchHpSize-1)
    {
        return;
    }
    else if (parent != 0)
    {
        int parentParent = hpParent(parent);
        
        if (hp->priority[parent] > hp->priority[parentParent])
        {
            hpfySearchingHp(hp, parentParent);
        }
    }
    
    int leftChild = hpLeftChild(parent);
    int rightChild = hpRightChild(parent);
    if (hp->hp[leftChild] == NULL)
    {
        leftChild = -1;
    }
    if (hp->hp[rightChild] == NULL)
    {
        rightChild = -1;
    }
    int biggestChild = max(leftChild, rightChild);
    
    if (hp->hp[biggestChild] != NULL && hp->priority[parent] < hp->priority[biggestChild])
    {
        switchSearchingHpItems(hp, parent, biggestChild);
        hpfySearchingHp(hp, biggestChild);
        hpfySearchingHp(hp, parent);
    }
    
    return;
}

void switchSearchingHpItems (SearchingHp *hp, int item1, int item2)
{
    int transitionInt;
    Event *transitionEvent;
    
    transitionEvent = hp->hp[item1];
    transitionInt = hp->priority[item1];
    
    hp->hp[item1] = hp->hp[item2];
    hp->priority[item1] = hp->priority[item2];
    
    hp->hp[item2] = transitionEvent;
    hp->priority[item2] = transitionInt;
}

SearchingHp* enqueueSearchingHp (SearchingHp *hp, Event *item)
{
    if (item == NULL)
    {
        return hp;
    }
    else if (hp == NULL)
    {
        return enqueueSearchingHp(createEmptyHp(), item);
    }
    
    int i;
    
    for (i = 0; i<SearchHpSize && item != hp->hp[i] && hp->hp[i] != NULL; i++);
    
    if (item == hp->hp[i])
    {
        (hp->priority[i])++;
        hpfySearchingHp(hp, i);
    }
    else if (hp->hpLength < SearchHpSize)
    {
        hp->hp[hp->hpLength-1] = item;
        hp->priority[hp->hpLength-1] = 1;
        hpfySearchingHp(hp, hp->hpLength-1);
        (hp->hpLength)++;
    }
    
    return hp;
}

void initializeSearchingHp (SearchingHp *hp)

{
    int i;
    
    for (i=0; i<SearchHpSize; i++)
    {
        hp->hp[i] = NULL;
        hp->priority[i] = -1;
    }
    
    hp->hpLength = 0;
}

Event* dequeueSearchingHp (SearchingHp *hp)
{
    if (hp == NULL)
    {
        return NULL;
    }
    else if (hp->hpLength <= 0)
    {
        return NULL;
    }
    
    //get first
    Event *dequeued = hp->hp[0];
    
    //replace first with last
    hp->hp[0] = hp->hp[hp->hpLength-1];
    hp->priority[0] = hp->priority[hp->hpLength-1];
    //remove last
    hp->hp[hp->hpLength-1] = NULL;
    hp->priority[hp->hpLength-1] = -1;
    //decrease hp length
    (hp->hpLength)--;
    
    //hpfy
    hpfySearchingHp(hp, 0);
    
    //return dequeued
    return dequeued;
}
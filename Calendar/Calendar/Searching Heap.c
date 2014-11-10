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
        return (child/2)-1;
    }
    else
    {
        return child/2;
    }
}

int hpLeftChild (int parent)
{
    return (parent*2) +1;
}

int hpRightChild (int parent)
{
    return (parent*2) +2;
}

SearchingHp* createEmptyHp (void)
{
    SearchingHp *new = (SearchingHp*) malloc(sizeof(SearchingHp));
    
    initializeSearchingHp(new);
    
    return new;
}

int peekHpHighestPriority (SearchingHp *hp)
{
    if (hp == NULL)
    {
        return -1;
    }
    else if (hp->hpLength == 0)
    {
        return -1;
    }
    
    return hp->priority[0];
}

void hpfySearchingHp (SearchingHp *hp, int parent)
{
    if (parent < 0 || hp == NULL || parent > SearchHpSize-1)
    {
        return;
    }
    else if (hp->hp[parent] == NULL)
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
    int biggestChild = maxSearchingHpChild(hp, leftChild, rightChild);
    
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
        hp->hp[i] = item;
        hp->priority[i] = 1;
        hpfySearchingHp(hp, i);
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

int maxSearchingHpChild (SearchingHp *hp, int left, int right)
{
    if (hp->priority[left] > hp->priority[right])
    {
        return left;
    }
    else
    {
        return right;
    }
}

SearchingHp* searchTableElementsToSearchingHp (SearchingHp *hp, SearchTable *table, int hash)
{
    if (table == NULL)
    {
        return hp;
    }
    else if (hash < 0 || hash >= SearchTableSize)
    {
        return hp;
    }
    else if (table->table[hash] == NULL)
    {
        return hp;
    }
    else if (hp == NULL)
    {
        return searchTableElementsToSearchingHp(createEmptyHp(), table, hash);
    }
    
    hp = eventBinarySearchTreeToSearchingHp(hp, table->table[hash]);
    
    return hp;
}

SearchingHp* eventBinarySearchTreeToSearchingHp (SearchingHp *hp, EventBinarySearchTree *root)
{
    if (root == NULL)
    {
        return hp;
    }
    else if (hp == NULL)
    {
        return NULL;
    }
    
    hp = enqueueSearchingHp(hp, root->event);
    hp = eventBinarySearchTreeToSearchingHp(hp, root->leftChild);
    return eventBinarySearchTreeToSearchingHp(hp, root->rightChild);
}

SearchingHp* enqueueEventsWithSimilarWord (SearchingHp *hp, SearchTable *table, char *word)
{
    if (table == NULL || strcmp(word, "") == 0)
    {
        return hp;
    }
    else if (hp == NULL)
    {
        return enqueueEventsWithSimilarWord(createEmptyHp(), table, word);
    }
    
    int hash = hashWord(word);
    
    return searchTableElementsToSearchingHp(hp, table, hash);
}

SearchingHp* enqueueEventsWithSimilarText (SearchingHp *hp, SearchTable *table, char *text)
{
    if (table == NULL || strcmp(text, "") == 0)
    {
        return hp;
    }
    else if (hp == NULL)
    {
        return enqueueEventsWithSimilarText(createEmptyHp(), table, text);
    }
    
    Node *textWords = NULL;
    textWords = listWords(text, textWords);
    //there was some error
    if (textWords == NULL)
    {
        return hp;
    }
    
    Node word;
    //enqueue events, word by word
    for (word = popNode(&textWords); !emptyNode(&word); word = popNode(&textWords))
    {
        hp = enqueueEventsWithSimilarWord(hp, table, word.name);
    }
    
    return hp;
}

SearchingHp* enqueueEventsWithProvidedDate (SearchingHp *hp, SearchTable *table, int day, int month, int year)
{
    if (table == NULL)
    {
        return hp;
    }
    else if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
    {
        return hp;
    }
    else if (hp == NULL)
    {
        return enqueueEventsWithProvidedDate(createEmptyHp(), table, day, month, year);
    }
    
    SearchingHp *provisory = NULL;
    SearchingHp *provisory2 = NULL;
    Event *dequeued = NULL;
    
    char strDay[4], strMonth[4], strYear[Max];
    
    snprintf(strDay, sizeof(strDay)/sizeof(char)-1, "%d", day);
    snprintf(strMonth, sizeof(strMonth)/sizeof(char)-1, "%d", month);
    snprintf(strYear, sizeof(strYear)/sizeof(char)-1, "%d", year);
    
    provisory = searchTableElementsToSearchingHp(provisory, table, hashWord(strDay));
    provisory = searchTableElementsToSearchingHp(provisory, table, hashWord(strMonth));
    provisory = searchTableElementsToSearchingHp(provisory, table, hashWord(strYear));
    //get only Events with at least 3 matchings
    while (peekHpHighestPriority(provisory) >= 3)
    {
        dequeued = dequeueSearchingHp(provisory);
        provisory2 = enqueueSearchingHp(provisory2, dequeued);
    }
    //clear provisory heap
    for (dequeued = dequeueSearchingHp(provisory); dequeued != NULL; dequeued = dequeueSearchingHp(provisory));
    //get only events with that exact date
    for (dequeued = dequeueSearchingHp(provisory2); dequeued != NULL; dequeued = dequeueSearchingHp(provisory2))
    {
        if (dequeued->date->day == day && dequeued->date->month == month && dequeued->date->year == year)
        {
            hp = enqueueSearchingHp(hp, dequeued);
        }
    }
    
    return hp;
}
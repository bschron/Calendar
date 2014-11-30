//
//  Searching Hp.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/6/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Searching Heap.h"

//TADs

struct searchingHp
{
    Event *hp[SearchHpSize];
    int priority[SearchHpSize];
    int hpLength;
    int hpNumber;
    SearchingHp *previous;
    SearchingHp *next;
};

//Functions

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
    else if (returnSearchingHeapItemItem(hp, parent) == NULL)
    {
        return;
    }
    else if (parent != 0)
    {
        int parentParent = hpParent(parent);
        
        if (returnSearchingHeapItemPriority(hp, parent) > returnSearchingHeapItemPriority(hp, parentParent))
        {
            hpfySearchingHp(hp, parentParent);
        }
    }
    
    int leftChild = hpLeftChild(parent);
    int rightChild = hpRightChild(parent);
    if (returnSearchingHeapItemItem(hp, leftChild) == NULL)
    {
        leftChild = -1;
    }
    if (returnSearchingHeapItemItem(hp, rightChild) == NULL)
    {
        rightChild = -1;
    }
    int biggestChild = maxSearchingHpChild(hp, leftChild, rightChild);
    
    if (returnSearchingHeapItemItem(hp, biggestChild) != NULL && returnSearchingHeapItemPriority(hp, parent) < returnSearchingHeapItemPriority(hp, biggestChild))
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
    SearchingHp *hp1 = getRightSearchingHeapItem(hp, item1, NULL, NULL);
    SearchingHp *hp2 = getRightSearchingHeapItem(hp, item2, NULL, NULL);
    
    if (hp1->hpNumber != 0)
    {
        item1 = item1 % (hp1->hpNumber*SearchHpSize);
    }
    if (hp2->hpNumber != 0)
    {
        item2 = item2 % (hp2->hpNumber*SearchHpSize);
    }
    
    transitionEvent = hp1->hp[item1];
    transitionInt = hp1->priority[item1];
    
    hp1->hp[item1] = hp2->hp[item2];
    hp1->priority[item1] = hp2->priority[item2];
    
    hp2->hp[item2] = transitionEvent;
    hp2->priority[item2] = transitionInt;
    
    return;
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
    
    for (i = 0; i<totalHpSize(hp) && item != returnSearchingHeapItemItem(hp, i) && NULL != returnSearchingHeapItemItem(hp, i); i++);
    
    if (item == returnSearchingHeapItemItem(hp, i))
    {
        attributeInfoToSearchingHpPosition(hp, i, returnSearchingHeapItemItem(hp, i), returnSearchingHeapItemPriority(hp, i)+1);
        hpfySearchingHp(hp, i);
    }
    else
    {
        attributeInfoToSearchingHpPosition(hp, i, item, 1);
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
    hp->hpNumber = 0;
    hp->next = NULL;
    hp->previous = 0;
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
    hp->hp[0] = returnSearchingHeapItemItem(hp, hp->hpLength-1);
    hp->priority[0] = returnSearchingHeapItemPriority(hp, hp->hpLength-1);
    //remove last
    attributeInfoToSearchingHpPosition(hp, hp->hpLength-1, NULL, -1);
    //decrease hp length
    (hp->hpLength)--;
    
    //hpfy
    hpfySearchingHp(hp, 0);
    
    //return dequeued
    return dequeued;
}

int maxSearchingHpChild (SearchingHp *hp, int left, int right)
{
    int bigger;
    
    if (returnSearchingHeapItemPriority(hp, left) > returnSearchingHeapItemPriority(hp, right))
    {
        bigger = left;
    }
    else
    {
        bigger = right;
    }
    
    return bigger;
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
    else if (peekTable(table)[hash] == NULL)
    {
        return hp;
    }
    else if (hp == NULL)
    {
        return searchTableElementsToSearchingHp(createEmptyHp(), table, hash);
    }
    
    hp = eventBinarySearchTreeToSearchingHp(hp, peekTable(table)[hash]);
    
    return hp;
}

SearchingHp* searchTableNotRecurrentElementsToSearchingHp (SearchingHp *hp, SearchTable *table, int hash)
{
    if (table == NULL)
    {
        return hp;
    }
    else if (hash < 0 || hash >= SearchTableSize)
    {
        return hp;
    }
    else if (peekTable(table)[hash] == NULL)
    {
        return hp;
    }
    else if (hp == NULL)
    {
        return searchTableNotRecurrentElementsToSearchingHp(createEmptyHp(), table, hash);
    }
    
    hp = eventBinarySearchTreeNotRecurrentToSearchingHp(hp, peekTable(table)[hash]);
    
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
    
    hp = enqueueSearchingHp(hp, peekTreeEvent(root));
    hp = eventBinarySearchTreeToSearchingHp(hp, peekLeftChild(root));
    hp = eventBinarySearchTreeToSearchingHp(hp, peekRightChild(root));
    
    return hp;
}

SearchingHp* eventBinarySearchTreeNotRecurrentToSearchingHp (SearchingHp *hp, EventBinarySearchTree *root)
{
    if (root == NULL)
    {
        return hp;
    }
    else if (hp == NULL)
    {
        return NULL;
    }
    
    if (peekEventRecurrency(peekTreeEvent(root)) >= 0)
    {
        hp = enqueueSearchingHp(hp, peekTreeEvent(root));
    }
    hp = eventBinarySearchTreeNotRecurrentToSearchingHp(hp, peekLeftChild(root));
    hp = eventBinarySearchTreeNotRecurrentToSearchingHp(hp, peekRightChild(root));
    
    return hp;
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
    
    return searchTableNotRecurrentElementsToSearchingHp(hp, table, hash);
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
    
    Node *word;
    //enqueue events, word by word
    for (word = popNode(&textWords); !emptyNode(word); word = popNode(&textWords))
    {
        hp = enqueueEventsWithSimilarWord(hp, table, peekNodeName(word));
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
    
    char strDay[6], strMonth[6], strYear[Max];
    
    snprintf(strDay, sizeof(strDay)/sizeof(char)-1, "%d", day);
    snprintf(strMonth, sizeof(strMonth)/sizeof(char)-1, "%d", month);
    snprintf(strYear, sizeof(strYear)/sizeof(char)-1, "%d", year);
    
    TWC *provisory = NULL;
    TWC *list = NULL;
    TWC* current = NULL;
    TWC *next = NULL;
    
    hp = searchTableElementsToSearchingHp(hp, table, hashWord(strDay));
    hp = searchTableElementsToSearchingHp(hp, table, hashWord(strMonth));
    hp = searchTableElementsToSearchingHp(hp, table, hashWord(strYear));
    
    while (hp->hpLength > 0)
    {
        Event *current = NULL;
        if (peekHpHighestPriority(hp) >= 3)
        {
            current = dequeueSearchingHp(hp);
        }
        else
        {
            dequeueSearchingHp(hp);
        }
        
        if (current != NULL)
        {
            provisory = insertTWC(provisory, createTWC(current));
        }
    }
    
    for (current = provisory; current != NULL; current = next)
    {
        next = peekNextTWC(current);
        Event* popped = popObject(&provisory);
        
        if (peekEventDateDay(popped) == day && peekEventDateMonth(popped) == month && peekEventDateYear(popped) == year)
        {
            list = insertTWC(list, createTWC(popped));
        }
    }
    
    while (list != NULL)
    {
        Event *current = popObject(&list);
        hp = enqueueSearchingHp(hp, current);
    }
    
    return hp;
}

SearchingHp* enqueueEventsForThisWeek (SearchingHp *hp, Date *now)
{
    if (hp == NULL)
    {
        return enqueueEventsForThisWeek(createEmptyHp(), now);
    }
    else if (now == NULL)
    {
        return enqueueEventsForThisWeek(hp, getDate(NULL));
    }
    
    int weekRemainingDays = remainingDaysInWeek(now);
    int i;
    
    for (i=0; i<weekRemainingDays; i++, now=increaseDate(now))
    {
        hp = enqueueEventsWithProvidedDate(hp, dateSearchTable, peekDateDay(now), peekDateMonth(now), peekDateYear(now));
    }
    
    return hp;
}

SearchingHp* enqueueEventsForThisMonth (SearchingHp *hp, Date *now)
{
    if (hp == NULL)
    {
        return enqueueEventsForThisMonth(createEmptyHp(), now);
    }
    else if (now == NULL)
    {
        return enqueueEventsForThisMonth(hp, getDate(NULL));
    }
    
    int remainingDays = remainingDaysInMonth(now);
    int i;
    
    for (i=0; i<=remainingDays; i++, now=increaseDate(now))
    {
        hp = enqueueEventsWithProvidedDate(hp, dateSearchTable, peekDateDay(now), peekDateMonth(now), peekDateYear(now));
    }
    
    return hp;
}

SearchingHp* duplicateSearchingHp (SearchingHp *hp)
{
    if (hp == NULL)
    {
        return NULL;
    }
    
    SearchingHp *new = createEmptyHp();
    
    int i;
    for (i = 0; i<hp->hpLength; i++)
    {
        attributeInfoToSearchingHpPosition(new, i, returnSearchingHeapItemItem(hp, i), returnSearchingHeapItemPriority(hp, i));
    }
    new->hpLength = hp->hpLength;
    
    return new;
}

SearchingHp* getRightSearchingHeapItem (SearchingHp *hp, int position, Event **object, int *priority)
{
    if (hp == NULL)
    {
        return NULL;
    }
    else if (position < 0)
    {
        return hp;
    }
    //get desired Heap Number
    int hpNumber = position/SearchHpSize;
    //recursively go to desired heap
    if (hp->hpNumber < hpNumber)
    {
        if (hp->next == NULL)
        {
            hp->next = createEmptyHp();
            hp->next->hpNumber = hp->hpNumber+1;
            hp->next->previous = hp;
        }
        
        return getRightSearchingHeapItem(hp->next, position, object, priority);
    }
    else if (hp->hpNumber > hpNumber)
    {
        return getRightSearchingHeapItem(hp->previous, position, object, priority);
    }
    
    //from now, we are already on the right heap
    int hpPosition = 0;
    if (hpNumber == 0)
    {
        hpPosition = position;
    }
    else
    {
        hpPosition = position % (hpNumber*SearchHpSize);
    }
    
    if (object != NULL)
    {
        *object = hp->hp[hpPosition];
    }
    if (priority != NULL)
    {
        *priority = hp->priority[hpPosition];
    }
    
    //cleanHp(&hp);
    
    return hp;
}

void cleanHp (SearchingHp **hp)
{
    if (hp == NULL)
    {
        return;
    }
    else if (*hp == NULL)
    {
        return;
    }
    //go to last heap
    if ((*hp)->next != NULL)
    {
        cleanHp(&(*hp)->next);
    }
    
    if ((*hp)->next == NULL && (*hp)->hpLength <= 0 && (*hp)->previous != NULL)
    {
        (*hp)->previous->next = NULL;
        free(*hp);
    }
    
    return;
}

int returnSearchingHeapItemPriority (SearchingHp *hp, int position)
{
    Event *object;
    int priority;
    
    getRightSearchingHeapItem(hp, position, &object, &priority);
    
    return priority;
}

Event* returnSearchingHeapItemItem (SearchingHp *hp, int position)
{
    Event *object;
    int priority;
    
    getRightSearchingHeapItem(hp, position, &object, &priority);
    
    return object;
}

int totalHpSize (SearchingHp *hp)
{
    if (hp == NULL)
    {
        return -1;
    }
    
    if (hp->next != NULL)
    {
        return totalHpSize(hp->next);
    }
    
    return (hp->hpNumber+1)*SearchHpSize;
}

void attributeInfoToSearchingHpPosition (SearchingHp *hp, int position, Event* object, int priority)
{
    hp = getRightSearchingHeapItem(hp, position, NULL, NULL);
    
    if (hp->hpNumber != 0)
    {
        position = position % (hp->hpNumber * SearchHpSize);
    }
    
    hp->hp[position] = object;
    hp->priority[position] = priority;
    
    return;
}

void freeSearchingHp (SearchingHp **hp)
{
    if (hp == NULL)
    {
        return;
    }
    else if (*hp == NULL)
    {
        return;
    }
    
    if ((*hp)->next != NULL)
    {
        freeSearchingHp(&(*hp)->next);
    }
    
    free(*hp);
    *hp = NULL;
    
    return;
}

int peekSearchingHpLength (SearchingHp *hp)
{
    if (hp == NULL)
    {
        return ERROR;
    }
    
    return hp->hpLength;
}
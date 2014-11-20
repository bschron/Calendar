//
//  Search Table.c
//  calendar
//
//  Created by Bruno Chroniaris on 11/5/14.
//  Copyright (c) 2014 UNIUM automação. All rights reserved.
//

#include "Search Table.h"

SearchTable* createEmptySearchTable (void)
{
    SearchTable *new = (SearchTable*) malloc(sizeof(SearchTable));
    
    initializeSearchTable(new);
    
    return new;
}

void initializeSearchTable (SearchTable *var)
{
    int i;
    
    for (i = 0; i<SearchTableSize; i++)
    {
        var->table[i] = NULL;
    }
}

int hashWord (char *word)
{
    int hash = wordSum(word);
    //hash -= wordPointerSum(word);
    //char number[Max];
    //snprintf(number, sizeof(number)/sizeof(char), "%d", hash);
    //hash *= wordPointerSum(number);
    hash = hash %SearchTableSize;
    
    return hash;
}

int wordSum (char *word)
{
    if (word == NULL)
    {
        return 0;
    }
    else if (*word == '\0')
    {
        return 0;
    }
    
    return (tolower(*word) - '0') + wordSum(word+1);
}

int wordPointerSum (char *word)
{
    if (word == NULL)
    {
        return 0;
    }
    else if (*word == '\0')
    {
        return 0;
    }
    
    void *pointer = NULL;
    pointer = word;
    
    char address[Max];
    
    snprintf(address, sizeof(address)/sizeof(char), "%s", pointer);
    
    return wordSum(address) + wordPointerSum(word+1);
}

void mapEventOnSearchTables (Event *event)
{
    mapEventTitle(event);
    mapEventDescription(event);
    mapEventDate(event);
}

void mapEventTitle (Event *event)
{
    Node *words = NULL;
    Node popped;
    
    words = listWords(event->title, words);
    
    for (popped = popNode(&words); !emptyNode(&popped); popped = popNode(&words))
    {
        insertEventBinarySearchTree(&titleSearchTable->table[popped.index], createEventBinarySearchTree(event), NULL);
    }
    
    return;
}

void mapEventDescription (Event *event)
{
    Node *words = NULL;
    Node popped;
    
    words = listWords(event->desc, words);
    
    for (popped = popNode(&words); !emptyNode(&popped); popped = popNode(&words))
    {
        insertEventBinarySearchTree(&descriptionSearchTable->table[popped.index], createEventBinarySearchTree(event), NULL);
    }
    
    return;
}

void mapEventDate (Event *event)
{
    char day[3];
    char month[3];
    char year[Max];
    
    sprintf(day, "%d", event->date->day);
    sprintf(month, "%d", event->date->month);
    sprintf(year, "%d", event->date->year);
    
    insertEventBinarySearchTree(&dateSearchTable->table[hashWord(day)], createEventBinarySearchTree(event), NULL);
    insertEventBinarySearchTree(&dateSearchTable->table[hashWord(month)], createEventBinarySearchTree(event), NULL);
    insertEventBinarySearchTree(&dateSearchTable->table[hashWord(year)], createEventBinarySearchTree(event), NULL);
    
    return;
}

void removeEventReferences (Event *event)
{
    removeEventDateReference(event);
    removeEventTitleReference(event);
    removeEventDescReference(event);
}

void removeEventDateReference (Event *event)
{
    if (event == NULL)
    {
        return;
    }
    
    char day[3], month[3], year[Max];
    int dayHash, monthHash, yearHash;
    
    sprintf(day, "%d", event->date->day);
    sprintf(month, "%d", event->date->month);
    sprintf(year, "%d", event->date->year);
    
    dayHash = hashWord(day);
    monthHash = hashWord(month);
    yearHash = hashWord(year);
    //day
    EventBinarySearchTree **result = NULL;
    result = searchEventBinarySearchTree(&dateSearchTable->table[dayHash], event);
    dateSearchTable->table[dayHash] = removeEventBinarySearchTree(dateSearchTable->table[dayHash], result);
    //month
    result = searchEventBinarySearchTree(&dateSearchTable->table[monthHash], event);
    dateSearchTable->table[monthHash] = removeEventBinarySearchTree(dateSearchTable->table[monthHash], result);
    //year
    result = searchEventBinarySearchTree(&dateSearchTable->table[yearHash], event);
    dateSearchTable->table[yearHash] = removeEventBinarySearchTree(dateSearchTable->table[yearHash], result);
    
    return;
}

void removeEventTitleReference (Event *event)
{
    Node *words = NULL;
    Node pop;
    EventBinarySearchTree **result = NULL;
    
    words = listWords(event->title, words);
    
    for (pop = popNode(&words); !emptyNode(&pop); pop = popNode(&words))
    {
        result = searchEventBinarySearchTree(&titleSearchTable->table[pop.index], event);
        titleSearchTable->table[pop.index] = removeEventBinarySearchTree(titleSearchTable->table[pop.index], result);
    }
    
    return;
}

void removeEventDescReference (Event *event)
{
    Node *words = NULL;
    Node pop;
    EventBinarySearchTree **result = NULL;
    
    words = listWords(event->desc, words);
    
    for (pop = popNode(&words); !emptyNode(&pop); pop = popNode(&words))
    {
        result = searchEventBinarySearchTree(&descriptionSearchTable->table[pop.index], event);
        descriptionSearchTable->table[pop.index] = removeEventBinarySearchTree(descriptionSearchTable->table[pop.index], result);
    }
    
    return;
}
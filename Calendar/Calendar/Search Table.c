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
    
    return (*word - '0') + wordSum(word+1);
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
}

void mapEventTitle (Event *event)
{
    Node *words = NULL;
    Node popped;
    
    words = listWords(event->title, words);
    
    for (popped = popNode(&words); !emptyNode(&popped); popped = popNode(&words))
    {
        insertEventBinarySearchTree(&titleSearchTable->table[popped.index], createEventBinarySearchTree(event));
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
        insertEventBinarySearchTree(&descriptionSearchTable->table[popped.index], createEventBinarySearchTree(event));
    }
    
    return;
}
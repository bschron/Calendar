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
    
    int i;
    
    for (i=0; i<SearchTableSize; i++)
    {
        new->table[i] = NULL;
    }
    
    return new;
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

void mapEventOnSearchTable (Event *event)
{
    
}
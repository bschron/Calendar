//
//  Support Functions.c
//  calendar
//
//  Created by Bruno Chroniaris on 11/5/14.
//  Copyright (c) 2014 UNIUM automação. All rights reserved.
//

#include "Support Functions.h"

int max (int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int sizeOfStr (char *str)
{
    int i;
    
    for (i=0; *(str+i) != '\0'; i++);
    
    return i;
}

Node* listWords (char *words, Node *list)
{
    if (words == NULL)
    {
        return list;
    }
    else if (*words == '\0')
    {
        return list;
    }
    
    char *p;
    char *word = (char*) malloc(sizeof(char)*Max);
    
    p = returnNextWord(word, words, ' ');
    
    list = insertNode(list, word, hashWord(word));
    free(word);
    
    return listWords(p, list);
}
char* returnNextWord (char *dest, char *word, char separator)
{
    if (word == NULL)
    {
        return NULL;
    }
    else if (*word == '\0')
    {
        return NULL;
    }
    
    char *aux = NULL;
    sprintf(dest, "");
    
    for (aux = word; *aux != '\0' && *aux != separator; aux++)
    {
        sprintf(dest, "%s%c", dest, *aux);
    }
    
    if (*aux == separator)
    {
        word = aux+1;
    }
    else
    {
        word = aux;
    }
    
    return word;
}
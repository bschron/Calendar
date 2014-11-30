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

int min (int a, int b)
{
    return a + b - max(a, b);
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

void take_lbreak (char *str)
{
    char *pos;
    if ((pos=strchr(str, '\n')) != NULL)
    {
        *pos = '\0';
    }
}

void nbgets (char *str, int num, FILE *stream)
{
    fgets(str, num, stream);
    take_lbreak(str);
}

int getNumber (void)
{
    int number;
    
    scanf("%d", &number);
    getchar();
    
    return number;
}

int fgetNumber (FILE *stream)
{
    int number;
    
    fscanf(stream, "%d", &number);
    fgetc(stream);
    
    return number;
}

int unwantedgets (char *dest, int size, char unwanted, FILE *stream)
{
    if (stream == NULL || dest == NULL)
    {
        return -1;
    }
    else if (size <= 1)
    {
        *dest = '\0';
        return 0;
    }
    
    char character = fgetc(stream);
    
    if (character != unwanted)
    {
        *dest = character;
        return unwantedgets(dest+1, size-1, unwanted, stream);
    }
    else if (character == EOF)
    {
        return 1;
    }
    
    *dest = '\0';
    return 0;
}

int lastTwoDigitsOfInt (int integer)
{
    if (integer < 100)
    {
        return integer;
    }
    
    int i = integer/100;
    i *= 100;
    
    return integer - i;
}

int validDate (Date *date)
{
    if (date == NULL)
    {
        return 0;
    }
    
    int valid = 1;
    
    if (peekDateYear(date) < 100)
    {
        valid = 0;
    }
    else if (peekDateMonth(date) > 12 || peekDateMonth(date) < 1)
    {
        valid = 0;
    }
    else if (leapYear(peekDateYear(date)) && peekDateMonth(date) == 2 && peekDateDay(date) > 29)
    {
        valid = 0;
    }
    else if (peekDateDay(date) > daysInMonth(peekDateMonth(date)))
    {
        valid = 0;
    }
    else if (peekDateDay(date) < 1)
    {
        valid = 0;
    }
    
    return valid;
}

int get1or0 (void)
{
    char input[10];
    int output;
    
    nbgets(input, 9, stdin);
    
    if (*input == '1' || *input == 's' || *input == 'y')
    {
        output = 1;
    }
    else
    {
        output = 0;
    }
    
    return output;
}

void copyIntegerArray (int *dest, int *from, int smallestLength)
{
    if (smallestLength == 0 || dest == NULL || from == NULL)
    {
        return;
    }
    
    *dest = *from;
    
    return copyIntegerArray(dest+1, from+1, smallestLength-1);
}

void loadingIcon (int *state, int *delay)
{
    char icon = '-';//  - \ | /
    
    if (*state > 3)
    {
        *state = 0;
    }
    /*
    (*delay)++;
    if (*delay >= 6666666)
    {
        delay = 0;
    }
    if (*delay != 1)
    {
        return;
    }
    */
    switch (*state)
    {
        case 0:
            icon = 92;
            (*state)++;
            break;
        case 1:
            icon = '|';
            (*state)++;
            break;
        case 2:
            icon = '/';
            (*state)++;
            break;
        case 3:
            icon = '-';
            *state = 0;
            break;
            
        default:
            break;
    }
    system("clear");
    printf("\nLOADING %c\n", icon);
}
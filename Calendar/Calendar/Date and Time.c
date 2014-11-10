//
//  Date and Time.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/9/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Date and Time.h"

Date* getDate (Date *date)
{
    if (date == NULL)
    {
        return getDate(createEmptyDate());
    }
    
    struct timeval now;
    struct tm *tmp;
    char timestr[Max];
    int rc;
    char number[10];
    char *breakpoint = timestr;
    
    rc = gettimeofday(&now, 0);
    if (rc != 0)
    {
        free(date);
        return createEmptyDate();
    }
    
    
    tmp = localtime(&now.tv_sec);
    if (tmp == 0)
    {
        free(date);
        return createEmptyDate();
    }
    
    strftime(timestr, sizeof(timestr), "%d/%m/%Y", tmp);
    
    breakpoint = returnNextWord(number, breakpoint, '/');
    date->day = atoi(number);
    breakpoint = returnNextWord(number, breakpoint, '/');
    date->month = atoi(number);
    breakpoint = returnNextWord(number, breakpoint, '/');
    date->year = atoi(number);
    
    return date;
}
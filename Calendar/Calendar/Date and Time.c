//
//  Date and Time.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/9/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Date and Time.h"

int getDate (int *day, int *month, int *year)
{
    struct timeval now;
    struct tm *tmp;
    char timestr[Max];
    int rc;
    char number[10];
    char *breakpoint = timestr;
    
    rc = gettimeofday(&now, 0);
    if (rc != 0)
    {
        return -1;
    }
    
    
    tmp = localtime(&now.tv_sec);
    if (tmp == 0)
    {
        return -1;
    }
    
    strftime(timestr, sizeof(timestr), "%d/%m/%Y", tmp);
    
    breakpoint = returnNextWord(number, breakpoint, '/');
    *day = atoi(number);
    breakpoint = returnNextWord(number, breakpoint, '/');
    *month = atoi(number);
    breakpoint = returnNextWord(number, breakpoint, '/');
    *year = atoi(number);
    
    return 0;
}
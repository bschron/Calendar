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

int daysTimeDistance (Date *date1, Date *date2)
{
    if (date1 == NULL || date2 == NULL)
    {
        return -1;
    }
    
    int diff = 0;
    Date *furthest = maxDate(date1, date2);
    Date *less = minDate(date1, date2);
    if (furthest == less)//if both dates are the same, max and min functions will allways return a pointer to date 2, and both pointer will be equal. In this case, we return 0, cuz there is no distance in days between days
    {
        return 0;
    }
    //days between the two years
    diff = daysBetweenYears(less->year, furthest->year);
    //days in Date months
    if (less->year == furthest->year && less->month == furthest->month)
    {
        diff += furthest->day - less->day;
    }
    else
    {
        diff += daysInMonth(less->month) - less->day;
        diff += furthest->day;
    }
    //Days between months
    if (less->year == furthest->year)
    {
        diff += daysBetweenMonths(less->month, furthest->month);
    }
    else
    {
        diff += daysBetweenMonths(less->month, 1);
        diff += daysBetweenMonths(12, furthest->month);
    }
    //leap yars considerations
    if (less->month <= 2 && leapYear(less->year))
    {
        diff += 1;
    }
    if (furthest->month > 2 && leapYear(furthest->year))
    {
        diff+=1;
    }
    
    return diff;
}

Date* maxDate (Date *date1, Date *date2)
{
    if (date1 == NULL || date2 == NULL)
    {
        return NULL;
    }
    else if (date1->year > date2->year)
    {
        return date1;
    }
    else if (date2->year > date1->year)
    {
        return date2;
    }
    else if (date1->month > date2->month)
    {
        return date1;
    }
    else if (date2->month > date1->month)
    {
        return date2;
    }
    else if (date1->day > date2->day)
    {
        return date1;
    }
    else
    {
        return date2;
    }
}

Date* minDate (Date *date1, Date *date2)
{
    if (date1 == NULL || date2 == NULL)
    {
        return NULL;
    }
    else if (date1->year > date2->year)
    {
        return date2;
    }
    else if (date2->year > date1->year)
    {
        return date1;
    }
    else if (date1->month > date2->month)
    {
        return date2;
    }
    else if (date2->month > date1->month)
    {
        return date1;
    }
    else if (date1->day > date2->day)
    {
        return date2;
    }
    else
    {
        return date2;
    }
}

int leapYear (int year)
{
    if (year%4 != 0)
    {
        return 0;
    }
    else if (year%100 != 0)
    {
        return 1;
    }
    else if (year%400 != 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int leapsYearsBetween (int year1, int year2)
{
    if (year1 == year2)
    {
        return 0;
    }
    else if (leapYear(year1) == 1)
    {
        return leapsYearsBetween(year1+1, year2) +1;
    }
    else
    {
        return leapsYearsBetween(year1+1, year2);
    }
}

int daysInMonth (int month)
{
    switch (month)
    {
        case 1:
            return 31;
            break;
        case 2:
            return 28;
            break;
        case 3:
            return 31;
            break;
        case 4:
            return 30;
            break;
        case 5:
            return 31;
            break;
        case 6:
            return 30;
            break;
        case 7:
            return 31;
            break;
        case 8:
            return 31;
            break;
        case 9:
            return 30;
            break;
        case 10:
            return 31;
            break;
        case 11:
            return 30;
            break;
        case 12:
            return 31;
            break;
            
        default:
            return -1;
            break;
    }
}

int daysBetweenMonths (int month1, int month2)
{
    if (month1 != month2)
    {
        month1++;
    }
    if (month1 > 12)
    {
        month1 -= 12;
    }
    if (month1 == month2)
    {
        return 0;
    }
    
    return daysBetweenMonths(month1, month2) + daysInMonth(month1);
}

int daysBetweenYears (int year1, int year2)
{
    if (year1 != year2)
    {
        year1++;
    }
    if (year1 == year2)
    {
        return 0;
    }
    
    return daysBetweenYears(year1, year2) + 365 + leapYear(year1);
}
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
    else if (date1->year < date2->year)
    {
        return date1;
    }
    else if (date2->year < date1->year)
    {
        return date2;
    }
    else if (date1->month < date2->month)
    {
        return date1;
    }
    else if (date2->month < date1->month)
    {
        return date2;
    }
    else if (date1->day < date2->day)
    {
        return date1;
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

int dayOfWeek (char *dest, Date *date)
{
    if (date == NULL)
    {
        return -1;
    }
    
    int day = (date->day + monthTableNumber(date->month, date->year) + lastTwoDigitsOfInt(date->year) + (lastTwoDigitsOfInt(date->year)/4) + centuryNumber(date->year))%7;
    
    if (dest != NULL)
    {
        weekDayIntToStr(dest, day);
    }
    
    return day ;
}

int centuryNumber (int year)
{
    if (year<100)
    {
        return -1;
    }
    
    year /= 100;
    
    if (year%4 == 0)
    {
        return 6;
    }
    else if ((year-1)%4 == 0)
    {
        return 4;
    }
    else if ((year-2)%4 == 0)
    {
        return 2;
    }
    else if ((year-3)%4 == 0)
    {
        return 0;
    }
    else
    {
        return 0;
    }
}

int monthTableNumber (int month, int year)
{
    switch (month)
    {
        case 1:
            if (leapYear(year))
            {
                return 6;
            }
            else
            {
                return 0;
            }
            break;
        case 2:
            if (leapYear(year))
            {
                return 2;
            }
            else
            {
                return 3;
            }
            break;
        case 3:
            return 3;
            break;
        case 4:
            return 6;
            break;
        case 5:
            return 1;
            break;
        case 6:
            return 4;
            break;
        case 7:
            return 6;
            break;
        case 8:
            return 2;
            break;
        case 9:
            return 5;
            break;
        case 10:
            return 0;
            break;
        case 11:
            return 3;
            break;
        case 12:
            return 5;
            break;
            
        default:
            return -1;
            break;
    }
}

void weekDayIntToStr (char *dest, int day)
{
    switch (day)
    {
        case 0:
            sprintf(dest, "domingo");
            break;
        case 1:
            sprintf(dest, "segunda");
            break;
        case 2:
            sprintf(dest, "terca");
            break;
        case 3:
            sprintf(dest, "quarta");
            break;
        case 4:
            sprintf(dest, "quinta");
            break;
        case 5:
            sprintf(dest, "sexta");
            break;
        case 6:
            sprintf(dest, "sabado");
            break;
            
        default:
            sprintf(dest, "");
            break;
    }
}

void monthIntToStr (char *dest, int month)
{
    if (dest == NULL)
    {
        return;
    }
    
    switch (month)
    {
        case 1:
            sprintf(dest, "Janeiro");
            break;
        case 2:
            sprintf(dest, "Fevereiro");
            break;
        case 3:
            sprintf(dest, "Marco");
            break;
        case 4:
            sprintf(dest, "Abril");
            break;
        case 5:
            sprintf(dest, "Maio");
            break;
        case 6:
            sprintf(dest, "Junho");
            break;
        case 7:
            sprintf(dest, "Julho");
            break;
        case 8:
            sprintf(dest, "Agosto");
            break;
        case 9:
            sprintf(dest, "Setembro");
            break;
        case 10:
            sprintf(dest, "Outubro");
            break;
        case 11:
            sprintf(dest, "Novembro");
            break;
        case 12:
            sprintf(dest, "Dezembro");
            break;
            
        default:
            sprintf(dest, "");
            break;
    }
}

int remainingDaysInWeek (Date *date)
{
    if (date == NULL)
    {
        return -1;
    }
    
    int day = dayOfWeek(NULL, date);
    
    return 7-day;
}

Date* increaseDate (Date *date)
{
    if (date == NULL)
    {
        return NULL;
    }
    
    if (leapYear(date->year) && date->month == 2 && date->day == 29)
    {
        date->month = 3;
        date->day = 1;
    }
    else if (date->month == 12 && date->day == 31)
    {
        (date->year++);
        date->month = 1;
        date->day=1;
    }
    else if (date->day+1 > daysInMonth(date->month))
    {
        date->day = 1;
        (date->month)++;
    }
    else
    {
        (date->day)++;
    }
    
    return date;
}

int remainingDaysInMonth (Date *date)
{
    if (date == NULL)
    {
        return -1;
    }
    
    int remaining;
    
    if (date->month == 2 && leapYear(date->year))
    {
        remaining = 29 - date->day-1;//-1, since we want to include the current
    }
    else
    {
        remaining = daysInMonth(date->month) - date->day;//-1, since we want to include the current day
    }
    
    return remaining;
}

Date* increaseDateByNDays (Date *date, int n)
{
    if (date == NULL)
    {
        return NULL;
    }
    else if (n <= 0)
    {
        return date;
    }
    
    return increaseDateByNDays(increaseDate(date), n-1);
}

int nextDayOfWeekToOccur (int *frequency, int nextDay)
{
    if (nextDay > 6)
    {
        return nextDayOfWeekToOccur(frequency, 0);
    }
    else if (frequency[nextDay])
    {
        return nextDay;
    }
    else
    {
        return nextDayOfWeekToOccur(frequency, nextDay+1);
    }
}

Date* advanceToNextNWeekDay (Date *date, int n)
{
    if (n < 0 || n > 6)
    {
        return date;
    }
    else if (date == NULL)
    {
        return advanceToNextNWeekDay(getDate(NULL), n);
    }
    
    int weekDay;
    
    date = increaseDate(date);
    weekDay = dayOfWeek(NULL, date);
    
    if (n != weekDay)
    {
        return advanceToNextNWeekDay(date, n);
    }
    
    return date;
}

Date* nextDayOfMonthToOccur (int *frequency, Date *current)
{
    if (current == NULL)
    {
        return nextDayOfMonthToOccur(frequency, getDate(NULL));
    }
    
    current = increaseDate(current);
    
    if (frequency[current->day] == 1)
    {
        return current;
    }
    
    return nextDayOfMonthToOccur(frequency, current);
}

Date* nextDayOfYearToOccur (int *frequency, Date *current)
{
    if (frequency[0] > daysInMonth(frequency[1]) && frequency[1] != 2)
    {
        frequency[0] = daysInMonth(frequency[1]);
    }
    else if (frequency[0] > 30)
    {
        frequency[0] = 30;
    }
    
    current = increaseDate(current);
    
    
    if (leapYear(current->year) || frequency[1] != 2 || frequency[0] <= 29)
    {
        if (current->day == frequency[0] && current->month == frequency[1])
        {
            return current;
        }
    }
    else
    {
        if (current->day == 30 && current->month == 2)
        {
            return current;
        }
    }
    
    return nextDayOfYearToOccur(frequency, current);
}

int passedDate (Date *date)
{
    if (date == NULL)
    {
        return 0;
    }
    
    Date *now = getDate(NULL);
    int past = 0;
    
    if (date->year < now->year)
    {
        past = 1;
    }
    else if (date->year > now->year)
    {
        past = 0;
    }
    else if (date->month < now->month)
    {
        past = 1;
    }
    else if (date->month > now->month)
    {
        past = 0;
    }
    else if (date->day < now->day)
    {
        past = 1;
    }
    else
    {
        past = 0;
    }
    
    free(now);
    return past;
}

Date nextTimeToOccur (int recurrency, int *frequency)
{   
    Date *now = getDate(NULL);
    Date output;
    if (recurrency == 1)
    {
        int weekDay = nextDayOfWeekToOccur(frequency, dayOfWeek(NULL, now));
        now = advanceToNextNWeekDay(now, weekDay);
    }
    else if (recurrency == 2)
    {
        now = nextDayOfMonthToOccur(frequency, now);
    }
    else if (recurrency == 3)
    {
        now = nextDayOfYearToOccur(frequency, now);
    }
    
    output = *now;
    free(now);
    return output;
}

int daysBetweenDates (Date *first, Date *second)
{
    if (first == NULL || second == NULL)
    {
        return -1;
    }
    else if (first == second)
    {
        return 0;
    }
    
    int output;
    Date *maxD = maxDate(first, second);
    Date *minD = minDate(first, second);
    
    minD = createDate(minD->day, minD->month, minD->year);
    
    for (output=0; minD->day != maxD->day || minD->month != maxD->month || minD->year != maxD->year; minD = increaseDate(minD), output++);
    
    free(minD);
    return output;
}
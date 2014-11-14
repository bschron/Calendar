//
//  Events Tree.c
//  calendar
//
//  Created by Bruno Chroniaris on 11/5/14.
//  Copyright (c) 2014 UNIUM automação. All rights reserved.
//

#include "Events Tree.h"

Event* createEmptyEvent (void)
{
    Event *new = (Event*) malloc(sizeof(Event));
    
    *new = returnEmptyEvent();
    
    return new;
}

Event* createEvent (int day, int month, int year, char *desc, char *title, int recurrency, int *frequency)
{
    Event *new = (Event*) malloc(sizeof(Event));
    new->date = createEmptyDate();
    
    new->date->day = day;
    new->date->month = month;
    new->date->year = year;
    new->next = NULL;
    new->previous = NULL;
    snprintf(new->title, Max, "%s", title);
    snprintf(new->desc, description, "%s", desc);
    new->recurrency = recurrency;
    new->frequency = frequency;
    new->recurrences = createRecurrentEvents(title, desc, new->date, recurrency, frequency);
    
    return new;
}

Event returnEmptyEvent (void)
{
    Event empty;
    
    empty.date = createEmptyDate();
    empty.next = NULL;
    empty.previous = NULL;
    sprintf(empty.desc, "");
    sprintf(empty.title, "");
    empty.recurrency = 0;
    empty.recurrences = NULL;
    empty.frequency = NULL;
    
    return empty;
}

Calendar* insertEvent (Calendar *calendar, int day, int month, int year, char *desc, char *title)
{
    Event *new = NULL;
    if (calendar == NULL)
    {
        return insertEvent(createEmptyCalendar(), day, month, year, desc, title);
    }
    else
    {
        new = createEmptyEvent();
        
        new->date->day = day;
        new->date->month = month;
        new->date->year = year;
        snprintf(new->title, Max, "%s", title);
        snprintf(new->desc, description, "%s", desc);
    }
    
    if (calendar->events == NULL)
    {
        new->next = NULL;
        new->previous = NULL;
        
        calendar->events = new;
    }
    else
    {
        new->next = calendar->events;
        calendar->events->previous = new;
        calendar->events = new;
    }
    //map event on searching tables
    mapEventOnSearchTables(new);
    
    return calendar;
}

Calendar* removeEvent (Calendar *calendar, Event *remove)
{
    if (calendar == NULL || remove == NULL)
    {
        return NULL;
    }
    
    if (calendar->events == remove)
    {
        calendar->events = remove->next;
        calendar->events->previous = NULL;
    }
    else if (remove->next == NULL)
    {
        remove->previous->next = NULL;
    }
    else
    {
        remove->previous->next = remove->next;
        remove->next->previous = remove->previous;
    }
    
    free(remove->date);
    free(remove);
    
    exportEvents(calendar);
    
    return calendar;
}

Calendar returnEmptyCalendar (void)
{
    Calendar empty;
    
    empty.events = NULL;
    
    return empty;
}

Calendar* createEmptyCalendar (void)
{
    Calendar *new = (Calendar*) malloc(sizeof(Calendar));
    
    *new = returnEmptyCalendar();
    
    return new;
}

Date* createEmptyDate (void)
{
    Date *new = (Date*) malloc(sizeof(Date));
    
    new->day = 0;
    new->month = 0;
    new->year = 0;
    
    return new;
}

Date* createDate (int day, int month, int year)
{
    if (day <= 0 || month <=0 || year <=0)
    {
        return NULL;
    }
    else if (month > 12)
    {
        return NULL;
    }
    else if (month == 2 && leapYear(year) && day > 29)
    {
        return NULL;
    }
    else if (day > daysInMonth(month))
    {
        return NULL;
    }
    
    Date *new = createEmptyDate();
    
    new->day = day;
    new->month = month;
    new->year = year;
    
    return new;
}

void editEvent (Event *event, Date *date, char *title, char *desc)
{
    if (event == NULL || date == NULL || title == NULL || desc == NULL)
    {
        return;
    }
    
    //remove references
    removeEventReferences(event);
    
    event->date->day = date->day;
    event->date->month = date->month;
    event->date->year = date->year;
    sprintf(event->title, "%s", title);
    sprintf(event->desc, "%s", desc);
    
    //renew references
    mapEventOnSearchTables(event);
    
    return;
}

void freeEvent (Event **event)
{
    if (event == NULL)
    {
        return;
    }
    
    free((*event)->date);
    free(*event);
    
    return;
}

Event *eventInsertEvent (Event *first, Event *new)
{
    if (new == NULL)
    {
        return NULL;
    }
    
    if (first == NULL)
    {
        new->next = NULL;
        new->previous = NULL;
        first = new;
    }
    else
    {
        first->previous = new;
        new->next = first;
        new->previous = NULL;
        first = new;
    }
    
    return first;
}

Event* createRecurrentEvents (char *title, char *desc, Date *starting, int recurrency, int *frequency)
{
    Event *first = createEmptyEvent();
    Event *new = NULL;
    Date *date = createDate(starting->day, starting->month, starting->year);
    int weekDay = dayOfWeek(NULL, date);
    int i;
    //create first
    sprintf(first->title, "%s", title);
    sprintf(first->desc, "%s", desc);
    first->next = NULL;
    first->previous = NULL;
    first->recurrences = NULL;
    first->frequency = NULL;
    first->recurrency = recurrency*-1;
    first->date = date;
    if (recurrency == 1)
    {
        first->date = increaseDate(first->date);
        weekDay = dayOfWeek(NULL, first->date);
        weekDay = nextDayOfWeekToOccur(frequency, weekDay);
        first->date = advanceToNextNWeekDay(first->date, weekDay);
    }
    else if (recurrency == 2)
    {
        first->date = nextDayOfMonthToOccur(frequency, first->date);
    }
    else if (recurrency == 3)
    {
        first->date = nextDayOfYearToOccur(frequency, first->date);
    }
    //create others
    if (recurrency == 1)
    {
        date = createDate(first->date->day, first->date->month, first->date->year);
        for (i=0; i<NumberOfRecurrences-1; i++, date=createDate(new->date->day, new->date->month, new->date->year))
        {
            date = increaseDate(date);
            weekDay = nextDayOfWeekToOccur(frequency, dayOfWeek(NULL, date));
            new = createEmptyEvent();
            sprintf(new->title, "%s", title);
            sprintf(new->desc, "%s", desc);
            new->recurrences = NULL;
            new->frequency = NULL;
            new->recurrency = first->recurrency;
            new->date = advanceToNextNWeekDay(date, weekDay);
            first = eventInsertEvent(first, new);
        }
    }
    else if (recurrency == 2)
    {
        date = createDate(first->date->day, first->date->month, first->date->year);
        for (i=0; i<NumberOfRecurrences-1; i++, date=createDate(new->date->day, new->date->month, new->date->year))
        {
            new = createEmptyEvent();
            sprintf(new->title, "%s", title);
            sprintf(new->desc, "%s", desc);
            new->recurrences = NULL;
            new->frequency = NULL;
            new->recurrency = first->recurrency;
            new->date = nextDayOfMonthToOccur(frequency, date);
            first = eventInsertEvent(first, new);
        }
    }
    else if (recurrency == 3)
    {
        date = createDate(first->date->day, first->date->month, first->date->year);
        for (i=0; i<NumberOfRecurrences-1; i++, date=createDate(new->date->day, new->date->month, new->date->year))
        {
            new = createEmptyEvent();
            sprintf(new->title, "%s", title);
            sprintf(new->desc, "%s", desc);
            new->recurrences = NULL;
            new->frequency = NULL;
            new->recurrency = first->recurrency;
            new->date = nextDayOfYearToOccur(frequency, date);
            first = eventInsertEvent(first, new);
        }
    }
    
    return first;
}
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
    if (recurrency == 0)
    {
        new->recurrences = NULL;
    }
    else
    {
        
        new->recurrences = createRecurrentEvents(new, title, desc, new->date, recurrency, frequency);
    }
    
    mapEventOnSearchTables(new);
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

Calendar* insertEvent (Calendar *calendar, Event *event)
{
    if (event == NULL)
    {
        return calendar;
    }
    else if (calendar == NULL)
    {
        return insertEvent(createEmptyCalendar(), event);
    }
    
    removeEventReferences(event);
    
    Event *new = (Event*) malloc(sizeof(Event));
    
    new->date = event->date;
    strcpy(new->desc, event->desc);
    new->frequency = event->frequency;
    new->next = event->next;
    new->previous = event->previous;
    new->recurrences = event->recurrences;
    new->recurrency = event->recurrency;
    strcpy(new->title, event->title);
    
    mapEventOnSearchTables(new);
    
    free(event);
    
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
    
    return calendar;
}

Calendar* removeEvent (Calendar *calendar, Event *remove)
{
    if (calendar == NULL || remove == NULL)
    {
        return NULL;
    }
    else if (remove->recurrency < 0)
    {
        return removeEvent(calendar, remove->recurrences);
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
    
    removeEventReferences(remove);
    
    freeEvent(&remove);
    
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
    if ((*event)->recurrences != NULL && (*event)->recurrency > 0)
    {
        Event current;
        for (current = *(*event)->recurrences;(*event)->recurrences != NULL; current = *(*event)->recurrences)
        {
            removeEventReferences((*event)->recurrences);
            freeEvent(&(*event)->recurrences);
            (*event)->recurrences = current.next;
            if ((*event)->recurrences == NULL)
            {
                break;
            }
        }
    }
    if ((*event)->frequency != NULL)
    {
        free((*event)->frequency);
        (*event)->frequency = NULL;
    }
    
    removeEventReferences(*event);
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

Event* createRecurrentEvents (Event *main, char *title, char *desc, Date *starting, int recurrency, int *frequency)
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
    first->recurrences = main;
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
    mapEventOnSearchTables(first);
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
            new->recurrences = main;
            new->frequency = NULL;
            new->recurrency = first->recurrency;
            new->date = advanceToNextNWeekDay(date, weekDay);
            first = eventInsertEvent(first, new);
            mapEventOnSearchTables(new);
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
            new->recurrences = main;
            new->frequency = NULL;
            new->recurrency = first->recurrency;
            new->date = nextDayOfMonthToOccur(frequency, date);
            first = eventInsertEvent(first, new);
            mapEventOnSearchTables(new);
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
            new->recurrences = main;
            new->frequency = NULL;
            new->recurrency = first->recurrency;
            new->date = nextDayOfYearToOccur(frequency, date);
            first = eventInsertEvent(first, new);
            mapEventOnSearchTables(new);
        }
    }
    
    return first;
}

int recurrentEventFrequencyLength (int recurrency)
{
    int output = 1;
    
    if (recurrency == 1)
    {
        output = 7;
    }
    else if (recurrency == 2)
    {
        output = 31;
    }
    else if (recurrency == 3)
    {
        output = 2;
    }
    
    return output;
}

Calendar* updateCalendar (Calendar *calendar)
{
    Event **current = NULL;
    
    for (current = &calendar->events; *current != NULL; current = &(*current)->next)
    {
        if ((*current)->recurrency > 0 && passedDate((*current)->date))
        {
            Event save = **current;
            Date saveDate = *(save.date);
            int *saveFrequency = (int*) malloc(sizeof(int)*recurrentEventFrequencyLength(save.recurrency));
            copyIntegerArray(saveFrequency, save.frequency, recurrentEventFrequencyLength(save.recurrency));
            removeEventReferences(*current);
            freeEvent(current);
            saveDate = nextTimeToOccur(save.recurrency, saveFrequency);
            *current = createEvent(saveDate.day, saveDate.month, saveDate.year, save.desc, save.title, save.recurrency, saveFrequency);
            (*current)->previous = save.previous;
            (*current)->next = save.next;
        }
    }
    
    return calendar;
}

void freeAllEvents (Event **events)
{
    if (events == NULL)
    {
        return;
    }
    else if (*events == NULL)
    {
        return;
    }
    
    Event *tofee = *events;
    
    *events = (*events)->next;
    
    freeEvent(&tofee);
    
    return freeAllEvents(events);
}
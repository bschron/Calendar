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

Event returnEmptyEvent (void)
{
    Event empty;
    
    empty.day = 0;
    empty.month = 0;
    empty.year = 0;
    empty.next = NULL;
    empty.previous = NULL;
    sprintf(empty.desc, "");
    sprintf(empty.title, "");
    
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
        
        new->day = day;
        new->month = month;
        new->year = year;
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
    
    //insert event int hash
    
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
    
    free(remove);
    
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
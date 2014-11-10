//
//  Output.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/10/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Output.h"

void printBulletedListLine (FILE *stream, char *str)
{
    if (stream == NULL || str == NULL)
    {
        return;
    }
    
    fprintf(stream, "*%s\n", str);
}

void printEvent (FILE *stream, Event *event)
{
    if (event == NULL)
    {
        return;
    }
    else if (stream == NULL)
    {
        return;
    }
    
    char weekDay[10];
    dayOfWeek(weekDay, event->date);
    
    fprintf(stream, "*%s\n", event->title);
    fprintf(stream, "%s - %d/%d/%d\n", weekDay, event->date->day, event->date->month, event->date->year);
    fprintf(stream, "%s\n\n", event->desc);
    
    return;
}

void printEventTitle (FILE *stream, Event *event)
{
    if (event == NULL)
    {
        return;
    }
    else if (stream == NULL)
    {
        return;
    }
    
    char weekDay[10];
    dayOfWeek(weekDay, event->date);
    
    fprintf(stream, "*%s   -%s\n", event->title, weekDay);
    
    return;
}

void printHeapOfEvents (FILE *stream, SearchingHp *events)
{
    if (stream == NULL || events == NULL)
    {
        return;
    }
    else if (events->hpLength == 0)
    {
        return;
    }
    
    Event *dequeued = dequeueSearchingHp(events);
    
    if (dequeued == NULL)
    {
        return;
    }
    
    printEvent(stream, dequeued);
    
    return printHeapOfEvents(stream, events);
}

void printEventTitlesOfHeapOfEvents (FILE *stream, SearchingHp *events)
{
    if (stream == NULL || events == NULL)
    {
        return;
    }
    else if (events->hpLength == 0)
    {
        return;
    }
    
    Event *dequeued = dequeueSearchingHp(events);
    
    if (dequeued == NULL)
    {
        return;
    }
    
    printEventTitle(stream, dequeued);
    
    return printEventTitlesOfHeapOfEvents(stream, events);
}
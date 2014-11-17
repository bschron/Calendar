//
//  File Management.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/9/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "File Management.h"

void exportEvents (Calendar *calendar)
{
    if (calendar == NULL)
    {
        return;
    }
    else if (calendar->events == NULL)
    {
        return;
    }
    
    char output[Max];
    char output2[Max];
    char *home = getenv("HOME");//path to home folder
    sprintf(output, "%s%s", home, MainDir);
    int exists = access(output, R_OK);
    Node *list = NULL;
    
    //creates if it does not exist
    if (exists != 0)
    {
        mkdir(output, chmod(output, 2));
    }
    
    sprintf(output2, "%s/%s%s", output, MainCalendar, CalendarFileExtension);
    FILE *export = fopen(output2, "w");
    Node pop;
    //inserts every formated data on the lists Node->name
    list = listEventsExportingStr(list, calendar->events);
    //prints every event on the list
    for (pop = popNode(&list); !emptyNode(&pop); pop=popNode(&list))
    {
        fprintf(export, "%s\n", pop.name);
    }
    
    if (list != NULL)
    {
        free(list);
    }
    
    fclose(export);
}

Node* listEventsExportingStr (Node *list, Event *events)
{
    if (events == NULL)
    {
        return list;
    }
    /*
    else if (list == NULL)
    {
        Node *new = (Node*) malloc(sizeof(Node));
        return listEventsExportingStr(new, events);
    }
    */
    
    char output[Max*5];
    
    //treat recurrent event differently than regular events
    if (events->recurrency == 0)
    {
        snprintf(output, sizeof(output)/sizeof(char), "*%s-%s-%d/%d/%d", events->title, events->desc, events->date->day, events->date->month, events->date->year);
    }
    else
    {
        printRecurrentEventFileExportingToStr(output, sizeof(output)/sizeof(char), events);
    }
    
    list = insertNode(list, output, not_in_use);
    
    return listEventsExportingStr(list, events->next);
}

Calendar* importCalendarFromFile (Calendar* calendar, FILE *file)
{
    if (file == NULL)
    {
        return calendar;
    }
    else if (calendar == NULL)
    {
        return importCalendarFromFile(createEmptyCalendar(), file);
    }
    //gets first character from line
    char character = fgetc(file);
    //checks if the end of file was reached
    if (character == EOF)
    {
        return calendar;
    }
    else if (character == '*')//start reading event
    {
        Event *new = createEmptyEvent();
        
        new = getEventMainInformationsFromStream(file, new);
        
        calendar = insertEvent(calendar, new);
        
        return importCalendarFromFile(calendar, file);
    }
    else if (character == '+')
    {
        Event *new = createEmptyEvent();
        
        new = getEventMainInformationsFromStream(file, new);
        new = getRecurrentAdditionalInformationsFromStream(file, new);
        
        calendar = insertEvent(calendar, new);
        
        return importCalendarFromFile(calendar, file);
    }
    else//does not match any case, maybe file is corrupted
    {
        return calendar;
    }
}

Calendar* importCalendarFromMainDirectory (Calendar *calendar)
{
    if (calendar == NULL)
    {
        return importCalendarFromMainDirectory(createEmptyCalendar());
    }
    
    char output[Max];
    char *home = getenv("HOME");//path to home folder
    sprintf(output, "%s%s/%s%s", home, MainDir, MainCalendar, CalendarFileExtension);
    FILE *file = fopen(output, "r");
    
    //if file does not exist
    if (file == NULL)
    {
        return calendar;
    }
    
    calendar = importCalendarFromFile(calendar, file);
    
    return calendar;
}

void printRecurrentEventFileExportingToStr (char *dest, int destLength, Event *event)
{
    char frequencyStr[Max];
    
    if (event->recurrency != 2)
    {
        int frequecyLength = 0;
        int i;
        if (event->recurrency == 1)
        {
            frequecyLength = 7;
        }
        else if (event->recurrency == 2)
        {
            frequecyLength = 31;
        }
        
        for (i=0; i<frequecyLength; i++)
        {
            frequencyStr[i] = event->frequency[i]+'0';
        }
    }
    
    if (event->recurrency == 1 || event->recurrency == 2)
    {
        snprintf(dest, destLength, "+%s-%s-%d/%d/%d-%d-%s", event->title, event->desc, event->date->day, event->date->month, event->date->year, event->recurrency, frequencyStr);
    }
    else if (event->recurrency == 3)
    {
        snprintf(dest, destLength, "+%s-%s-%d/%d/%d-%d-%d/%d", event->title, event->desc, event->date->day, event->date->month, event->date->year, event->recurrency, event->frequency[0], event->frequency[1]);
    }
    
    return;
}

Event* getEventMainInformationsFromStream (FILE *stream, Event *event)
{
    if (stream == NULL)
    {
        return event;
    }
    else if (event == NULL)
    {
        return getEventMainInformationsFromStream(stream, createEmptyEvent());
    }
    
    unwantedgets(event->title, Max, '-', stream);
    unwantedgets(event->desc, description, '-', stream);
    fscanf(stream, "%d", &event->date->day);
    fgetc(stream);
    fscanf(stream, "%d", &event->date->month);
    fgetc(stream);
    fscanf(stream, "%d", &event->date->year);
    fgetc(stream);
    
    return event;
}

Event *getRecurrentAdditionalInformationsFromStream (FILE *stream, Event *event)
{
    if (stream == NULL || event == NULL)
    {
        return event;
    }
    
    int frequencyLength = 0;
    int i;
    
    event->recurrency = fgetNumber(stream);

    if (event->recurrency == 1)
    {
        frequencyLength = 7;
    }
    else if (event->recurrency == 2)
    {
        frequencyLength = 31;
    }
    
    if (event->recurrency == 1 || event->recurrency == 2)
    {
        event->frequency = (int*) malloc(sizeof(int)*frequencyLength);
        
        for (i = 0; i < frequencyLength; i++)
        {
            event->frequency[i] = fgetc(stream) - '0';
        }
        fgetc(stream);//gets line break
    }
    else if (event->recurrency == 3)
    {
        event->frequency = (int*) malloc(sizeof(int)*2);
        event->frequency[0] = fgetNumber(stream);
        event->frequency[1] = fgetNumber(stream);//gets like break
    }
    
    return event;
}
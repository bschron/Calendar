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
    else if (emptyCalendar(calendar))
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
    list = listEventsExportingStr(list, peekCalendarFirstEvent(calendar));
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
    if (peekEventRecurrency(events) == 0)
    {
        snprintf(output, sizeof(output)/sizeof(char), "*%s-%s-%d/%d/%d", peekEventTitle(events), peekEventDesc(events), peekEventDateDay(events), peekEventDateMonth(events), peekEventDateYear(events));
    }
    else
    {
        printRecurrentEventFileExportingToStr(output, sizeof(output)/sizeof(char), events);
    }
    
    list = insertNode(list, output, not_in_use);
    
    return listEventsExportingStr(list, peekNextEvent(events));
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
        Event *provisory = createEmptyEvent();
        Event *new = NULL;
        int *provFrequency = (int*) malloc(sizeof(int));
        
        provisory = getEventMainInformationsFromStream(file, provisory);
        provisory = getRecurrentAdditionalInformationsFromStream(file, provisory);
        //using createEvent function so recurrences will be created.
        new = createEvent(peekEventDateDay(provisory), peekEventDateMonth(provisory), peekEventDateYear(provisory), peekEventDesc(provisory), peekEventTitle(provisory), peekEventRecurrency(provisory), peekEventFrequency(provisory));
        
        calendar = insertEvent(calendar, new);
        
        //created a new provisory frequency, just to evoid SIGNALRBIT while running
        setEventFrequency(provisory, provFrequency);
        freeEvent(&provisory);
        
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
    
    if (peekEventRecurrency(event) != 3)
    {
        int frequecyLength = 0;
        int i;
        if (peekEventRecurrency(event) == 1)
        {
            frequecyLength = 7;
        }
        else if (peekEventRecurrency(event) == 2)
        {
            frequecyLength = 31;
        }
        
        int *frequency = peekEventFrequency(event);
        for (i=0; i<frequecyLength; i++)
        {
            frequencyStr[i] = frequency[i]+'0';
        }
    }
    
    if (peekEventRecurrency(event) == 1 || peekEventRecurrency(event) == 2)
    {
        snprintf(dest, destLength, "+%s-%s-%d/%d/%d-%d-%s", peekEventTitle(event), peekEventDesc(event), peekEventDateDay(event), peekEventDateMonth(event), peekEventDateYear(event), peekEventRecurrency(event), frequencyStr);
    }
    else if (peekEventRecurrency(event) == 3)
    {
        int *frequency = peekEventFrequency(event);
        snprintf(dest, destLength, "+%s-%s-%d/%d/%d-%d-%d/%d", peekEventTitle(event), peekEventDesc(event), peekEventDateDay(event), peekEventDateMonth(event), peekEventDateYear(event), peekEventRecurrency(event), frequency[0], frequency[1]);
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
    
    int day, month, year;
    
    unwantedgets(peekEventTitle(event), Max, '-', stream);
    unwantedgets(peekEventDesc(event), description, '-', stream);
    fscanf(stream, "%d", &day);
    fgetc(stream);
    fscanf(stream, "%d", &month);
    fgetc(stream);
    fscanf(stream, "%d", &year);
    fgetc(stream);
    
    setEventDateDay(event, day);
    setEventDateMonth(event, month);
    setEventDateYear(event, year);
    
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
    int *frequency = NULL;
    
    setEventRecurrency(event, fgetNumber(stream));

    if (peekEventRecurrency(event) == 1)
    {
        frequencyLength = 7;
    }
    else if (peekEventRecurrency(event) == 2)
    {
        frequencyLength = 31;
    }
    
    if (peekEventRecurrency(event) == 1 || peekEventRecurrency(event) == 2)
    {
        frequency = (int*) malloc(sizeof(int)*frequencyLength);
        setEventFrequency(event, frequency);
        
        for (i = 0; i < frequencyLength; i++)
        {
            frequency[i] = fgetc(stream) - '0';
        }
        fgetc(stream);//gets line break
    }
    else if (peekEventRecurrency(event) == 3)
    {
        frequency = (int*) malloc(sizeof(int)*2);
        setEventFrequency(event, frequency);
        
        frequency[0] = fgetNumber(stream);
        frequency[1] = fgetNumber(stream);//gets like break
    }
    
    return event;
}
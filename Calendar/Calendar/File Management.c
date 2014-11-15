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
        char *title = (char*) malloc(sizeof(char)*Max);
        char *desc = (char*) malloc(sizeof(char)*description);
        int *date = (int*) malloc(sizeof(int)*3);//date has 3 positions that are divided in the following order, day/month/year
        
        unwantedgets(title, Max, '-', file);
        unwantedgets(desc, description, '-', file);
        fscanf(file, "%d", &date[0]);
        fgetc(file);
        fscanf(file, "%d", &date[1]);
        fgetc(file);
        fscanf(file, "%d", &date[2]);
        fgetc(file);
        
        calendar = insertEvent(calendar, date[0], date[1], date[2], desc, title);
        free(title);
        free(desc);
        free(date);
        
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
        snprintf(dest, destLength, "*%s-%s-%d/%d/%d-%d-%s", event->title, event->desc, event->date->day, event->date->month, event->date->year, event->recurrency, frequencyStr);
    }
    else if (event->recurrency == 3)
    {
        snprintf(dest, destLength, "*%s-%s-%d/%d/%d-%d-%d/%d", event->title, event->desc, event->date->day, event->date->month, event->date->year, event->recurrency, event->frequency[0], event->frequency[1]);
    }
    
    return;
}
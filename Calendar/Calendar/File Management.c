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
    char *home = getenv("HOME");//path to home folder
    sprintf(output, "%s%s", home, MainDir);
    int exists = access(output, R_OK);
    Node *list = NULL;
    
    //creates if it does not exist
    if (exists != 0)
    {
        mkdir(output, chmod(output, 2));
    }
    
    sprintf(output, "%s/%s%s", output, MainCalendar, CalendarFileExtension);
    FILE *export = fopen(output, "w");
    //inserts every formated data on the lists Node->name
    list = listEventsExportingStr(list, calendar->events);
    //prints every event on the list
    for (; list->next != NULL; list = removeNode(list, list))
    {
        fprintf(export, "%s\n", list->name);
    }
    
    fclose(export);
}

Node* listEventsExportingStr (Node *list, Event *events)
{
    if (events == NULL)
    {
        return list;
    }
    else if (list == NULL)
    {
        Node *new = (Node*) malloc(sizeof(Node));
        return listEventsExportingStr(new, events);
    }
    
    char output[Max*5];
    
    snprintf(output, sizeof(output)/sizeof(char), "*%s-%s-%d/%d/%d", events->title, events->desc, events->date->day, events->date->month, events->date->year);
    
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
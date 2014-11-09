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
    sprintf(output, "%s/Documents/spyridonsCalendar", home);
    int exists = access(output, R_OK);
    Node *list = NULL;
    
    //creates if it does not exist
    if (exists != 0)
    {
        mkdir(output, chmod(output, 2));
    }
    
    sprintf(output, "%s/calendar.spyridon", output);
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
    
    snprintf(output, sizeof(output)/sizeof(char), "*%s-%s-%d/%d/%d", events->title, events->desc, events->day, events->month, events->year);
    
    list = insertNode(list, output, not_in_use);
    
    return listEventsExportingStr(list, events->next);
}
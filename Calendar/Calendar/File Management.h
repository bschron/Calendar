//
//  File Management.h
//  Calendar
//
//  Created by Bruno Chroniaris on 11/9/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#ifndef __Calendar__File_Management__
#define __Calendar__File_Management__

#include "Headers.h"

/*inserts a node with a formated string for every Event provided. the formated str is ready to be written on file. created a new list if the provided is NULL and returns the provided list value unchanged if the provided event is NULL. Function keeps calling itself till there is no more events left*/
Node* listEventsExportingStr (Node *list, Event *events);
/*exports informations about every scheduled event on the provided calendar to a file in the system Library. If the file Does not Exist, creates it. Will overwrite any existing file, updating the added and remove events. returns with no changes if the provided calendar is NULL of if the provided calendar has no scheduled events (calendar->events == NULL)*/
void exportEvents (Calendar *calendar);
/*reads provided file, line by line(until EOF), and attributes events info to provided calendar. Returns calendar unchanged if provided pointer to file is NULL, and creates a new calendar if provided one is NULL.*/
Calendar* importCalendarFromFile (Calendar* calendar, FILE *file);
/*imports calendar info from main calendar file. returns provided calendar unchanged if file does not exist and creates a new calendar if provided is NULL. Returns pointer to the calendar.*/
Calendar* importCalendarFromMainDirectory (Calendar *calendar);
/*Takes  pointer to str, a int representing the length of that str and a pointer to Event. prints the provided recurrent event info to the provided str.*/
void printRecurrentEventFileExportingToStr (char *dest, int destLength, Event *event);

#endif /* defined(__Calendar__File_Management__) */

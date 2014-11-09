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

#endif /* defined(__Calendar__File_Management__) */

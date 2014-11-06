//
//  Events Tree.h
//  calendar
//
//  Created by Bruno Chroniaris on 11/5/14.
//  Copyright (c) 2014 UNIUM automação. All rights reserved.
//

#ifndef __calendar__Events_Tree__
#define __calendar__Events_Tree__

#include "Headers.h"

//Event
Event returnEmptyEvent (void);
Event* createEmptyEvent (void);
Event* createEvent (int day, int month, int year, char *desc, char *title);
/*This function will insert a event into a calendar, with the provided parameters and add this event to the hash table, if the calendar is NULL, it will create a new calendar */
Calendar* insertEvent (Calendar *calendar, int day, int month, int year, char *desc, char *title);
/*this function will remove a event provided from a provided calendar, if calendar is NULL, will return NULL*/
Calendar* removeEvent (Calendar *calendar, Event *event);

//Calendar
Calendar returnEmptyCalendar (void);
Calendar* createEmptyCalendar (void);

#endif /* defined(__calendar__Events_Tree__) */

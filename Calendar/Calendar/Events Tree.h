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
/*returns a event with empty flags*/
Event returnEmptyEvent (void);
/*returns a pointer to a new event with empty flags*/
Event* createEmptyEvent (void);
/*returns a pointer to a new event with the provided content*/
Event* createEvent (int day, int month, int year, char *desc, char *title);
/*This function will insert a event into a calendar, with the provided parameters and add this event to the hash table, if the calendar is NULL, it will create a new calendar */
Calendar* insertEvent (Calendar *calendar, int day, int month, int year, char *desc, char *title);
/*this function will remove a event provided from a provided calendar, if calendar is NULL, will return NULL*/
Calendar* removeEvent (Calendar *calendar, Event *event);
/*takes a pointer to Event, a pointer to Date, pointer title str and pointer to description str. Attribute those new values to provided event and returns. if any of the provided pointers is NULL, returns without changes to the event*/
void editEvent (Event *event, Date *date, char *title, char *desc);
/*Takes double pointer to Event. Frees event and event Date. If Event == NULL, returns*/
void freeEvent (Event **event);

//Calendar
/*returns a Calendar with empty falgs*/
Calendar returnEmptyCalendar (void);
/*returna a pointer to a new calendar with empty flags*/
Calendar* createEmptyCalendar (void);

//Date
/*creates a new date TAD and sets its values to empty flags, returns the pointer to the new Date*/
Date* createEmptyDate (void);
/*takes three int as arguments, attributes that values to a new Date and returns a pointer to it. Returns NULL if provided date is invalid*/
Date* createDate (int day, int month, int year);

#endif /* defined(__calendar__Events_Tree__) */

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
Event* createEvent (int day, int month, int year, char *desc, char *title, int recurrency, int *frequency);
void editEvent (Event *event, Date *date, char *title, char *desc);
/*Takes double pointer to Event. Frees event and event Date. If Event == NULL, returns*/
void freeEvent (Event **event);
/*takes two pointer to Event as argument, the first been the first node of a list of events and the second is the new node to be inserted on that lins of events. This functions insertes the new node to the provided list of events and return a pointer to eh first element. Returns NULL is the provided new element is a NULL pointer.*/
Event *eventInsertEvent (Event *first, Event *new);
/*Takes a integer, representing the event recurrency variable, and returns the length of the frequency array, depending of the recurrency. returns 1 if does not match any case.*/
int recurrentEventFrequencyLength (int recurrency);
/*Takes a pointer to calendar as argument. Checks every event on this calendar and checks if any of the recurrent events is outdated. Updates the info of all the outdated recurrent events.*/
Calendar* updateCalendar (Calendar *calendar);

//Calendar
/*returns a Calendar with empty falgs*/
Calendar returnEmptyCalendar (void);
/*returna a pointer to a new calendar with empty flags*/
Calendar* createEmptyCalendar (void);
/*Takes a pointer to Calendar and pointer to Event as argument. Inserts the provided invent on the provided calendar. If the provided pointer to calendar is NULL, creates a new one. returns the calendar unchanged if the proviede event is NULL.*/
Calendar* insertEvent (Calendar *calendar, Event *event);
/*this function will remove a event provided from a provided calendar, if calendar is NULL, will return NULL*/
Calendar* removeEvent (Calendar *calendar, Event *event);
/*takes a pointer to Event, a pointer to Date, pointer title str and pointer to description str. Attribute those new values to provided event and returns. if any of the provided pointers is NULL, returns without changes to the event*/

//Date
/*creates a new date TAD and sets its values to empty flags, returns the pointer to the new Date*/
Date* createEmptyDate (void);
/*takes three int as arguments, attributes that values to a new Date and returns a pointer to it. Returns NULL if provided date is invalid*/
Date* createDate (int day, int month, int year);
/*takes a pointer to char title, a pointer to char desc, a pointer to Date starting, a integer recurrency and a pointer to integer frequency as arguments. Tilte is the str of the event title and desc the str of event description. starting is a pointer to the root event date. recurrency is the integer that represents the kind of recurrency for this event. frequency is a array representing the way the events will repeat in time. This function creates NumberOfRecurrences recurrences for this event, inserts them in a list and returns a pointer to the first element of that list.*/
Event* createRecurrentEvents (Event *main, char *title, char *desc, Date *starting, int recurrency, int *frequency);

#endif /* defined(__calendar__Events_Tree__) */

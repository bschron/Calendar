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

void editEvent (Calendar *calendar, Event *event, Date *date, char *title, char *desc);
/*Takes double pointer to Event. Frees event and event Date. If Event == NULL, returns*/
void freeEvent (Event **event);
/*takes two pointer to Event as argument, the first been the first node of a list of events and the second is the new node to be inserted on that lins of events. This functions insertes the new node to the provided list of events and return a pointer to eh first element. Returns NULL is the provided new element is a NULL pointer.*/
Event *eventInsertEvent (Event *first, Event *new);
/*Takes a integer, representing the event recurrency variable, and returns the length of the frequency array, depending of the recurrency. returns 1 if does not match any case.*/
int recurrentEventFrequencyLength (int recurrency);
/*Takes a pointer to calendar as argument. Checks every event on this calendar and checks if any of the recurrent events is outdated. Updates the info of all the outdated recurrent events.*/
Calendar* updateCalendar (Calendar *calendar);
/*Takes a double pointer to Event events as argument. Frees every node on the provided list.*/
void freeAllEvents (Event **events);
/*Takes a double pointer to Event as argument. Attributes the next Event in list to the provided pointer's pointer and returns a pointer to the next element in list. Attributes and returns NULL is the next is NULL.*/
Event* moveToNextEvent (Event **current);
/*Takes a double pointer to Event as argument. Attributes the previous Event in list to the provided pointer's pointer and returns a pointer to the previous element in list. Attributes and returns NULL is the previous is NULL.*/
Event* moveToPreviousEvent (Event **current);
/*Takes a pointer to Event as argument. Returns a pointer to the Event's title's string. Returns NULL if the provided pointer is NULL.*/
char* peekEventTitle (Event *event);
/*Takes a pointer to Event as argument. Returns a pointer to the Event's description's string. Returns NULL if the provided pointer is NULL.*/
char* peekEventDesc (Event *event);
/*Takes a pointer to Event *event and a integer day. Attributes the provided day to the provoded event's Date's day and returns 0. Returns 1 if provided pointer is NULL or provided day is invalid.*/
int setEventDateDay (Event *event, int day);
/*Takes a pointer to Event *event and a integer month. Attributes the provided month to the provoded event's Date's day and returns 0. Returns 1 if provided pointer is NULL or provided month is invalid.*/
int setEventDateMonth (Event *event, int month);
/*Takes a pointer to Event *event and a integer year. Attributes the provided year to the provoded event's Date's year and returns 0. Returns 1 if provided pointer is NULL or provided year is invalid.*/
int setEventDateYear (Event *event, int year);
/*Takes a pointer to Event *event as argument. Returns a pointer to the provided event's Date. Returns NULL if provided event is NULL or event's date is NULL.*/
Date* peekEventDate (Event *event);
/*Takes a pointer to Event *event as argument. Returns a pointer to the next event in list. Returns NULL if provided pointer is NULL or next element is NULL.*/
Event* peekNextEvent (Event *event);
/*Takes a pointer to Event *event as argument. Returns a pointer to the previous event in list. Returns NULL if provided pointer is NULL or previous element is NULL.*/
Event* peekPreviousEvent (Event *event);
/*Takes a pointer to Event *event as argument. Returns the provided event's recurrency. Returns ERROR if provided event is NULL.*/
int peekEventRecurrency (Event *event);
/*Takes a pointer to Event *event as argument. Returns the provide event's recurrence list. Returns NULL if provided event is NULL.*/
Event* peekEventRecurrences (Event *event);
/*Takes a pointer to Event *event as argument. Returns the provided event's frequency data. Returns NULL if provided event is NULL.*/
int* peekEventFrequency (Event *event);
/*Takes a pointer to Event *event as argument. Returns the provided event's date's day. Returns ERROR if provided event is NULL or provided event's date is NULL.*/
int peekEventDateDay (Event *event);
/*Takes a pointer to Event *event as argument. Returns the provided event's date's month. Returns ERROR if provided event is NULL or provided event's date is NULL.*/
int peekEventDateMonth (Event *event);
/*Takes a pointer to Event *event as argument. Returns the provided event's date's year. Returns ERROR if provided event is NULL or provided event's date is NULL.*/
int peekEventDateYear (Event *event);
/*Takes a pointer to Event *event and a pointer to integer *frequency as arguments. Attributes the provided frequency to the provided event and returns 0. returns ERROR if provided pointer to event is NULL.*/
int setEventFrequency (Event *event, int *frequency);
/*Takes a pointer to Event *event and a integer recurrency as arguments. Attributes the provided recurrency to the providede event and returns 0. Returns -1 and unchanged if provided pointer to event is NULL.*/
int setEventRecurrency (Event *event, int recurrency);
/*Takes a pointer to Event *event and a pointer to Event *recurrences as arguments. Attributes the provided recurrences to the provided event and returns 0. Returns 0 and unchanged if the provided *event pointer is NULL.*/
int setEventRecurrences (Event *event, Event *recurrences);

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
/*Takes a pointer to calendar as argument, returns a pointer to the first element from the provided calendar's Event list. Returns NULL if calendar is empty.*/
Event* peekCalendarFirstEvent (Calendar *calendar);
/*Takes a pointer to calendar as argument. Returns 1 if provided calendar is empty, 0 if not. Returns -1 if provided pointer is NULL.*/
int emptyCalendar (Calendar *calendar);

//Date
/*creates a new date TAD and sets its values to empty flags, returns the pointer to the new Date*/
Date* createEmptyDate (void);
/*takes three int as arguments, attributes that values to a new Date and returns a pointer to it. Returns NULL if provided date is invalid*/
Date* createDate (int day, int month, int year);
/*takes a pointer to char title, a pointer to char desc, a pointer to Date starting, a integer recurrency and a pointer to integer frequency as arguments. Tilte is the str of the event title and desc the str of event description. starting is a pointer to the root event date. recurrency is the integer that represents the kind of recurrency for this event. frequency is a array representing the way the events will repeat in time. This function creates NumberOfRecurrences recurrences for this event, inserts them in a list and returns a pointer to the first element of that list.*/
Event* createRecurrentEvents (Event *main, char *title, char *desc, Date *starting, int recurrency, int *frequency);
/*Takes a pointer to Date *date as argument. Returns the provided Date's day. Returns ERROR if provided pointer is NULL*/
int peekDateDay (Date *date);
/*Takes a pointer to Date *date as argument. Returns the provided Date's month. Returns ERROR if provided pointer is NULL*/
int peekDateMonth (Date *date);
/*Takes a pointer to Date *date as argument. Returns the provided Date's year. Returns ERROR if provided pointer is NULL*/
int peekDateYear (Date *date);
/*Takes a pointer to Date *date, a integer day, a integer month and a integer year as arguments. Sets the provided day, month and year to the provided Date and returns a pointer to the provided date. Returns NULL if provided date is NULL.*/
Date* setDate (Date *date, int day, int month, int year);
/*Takes a pointer to Date *dest and a pointer to Date *source as arguments. Attributes source's values to dest and returns a pointer to dest. Returns NULL if any of provided pointers is NULL.*/
Date* setDateByDate (Date *dest, Date *source);
/*Takes a pointer to Date *date and a integer day as arguments. Set's the provided day to provided date and returns a pointer to provided date. Returns ERROR if provided pointer is NULL.*/
Date* setDateDay (Date *date, int day);
/*Takes a pointer to Date *date and a integer month as arguments. Set's the provided month to provided date and returns a pointer to provided date. Returns ERROR if provided pointer is NULL.*/
Date* setDateMonth (Date *date, int month);
/*Takes a pointer to Date *date and a integer year as arguments. Set's the provided year to provided date and returns a pointer to provided date. Returns ERROR if provided pointer is NULL.*/
Date* setDateYear (Date *date, int year);

#endif /* defined(__calendar__Events_Tree__) */

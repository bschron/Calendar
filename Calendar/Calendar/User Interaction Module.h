//
//  User Interaction Module.h
//  Calendar
//
//  Created by Bruno Chroniaris on 11/10/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#ifndef __Calendar__User_Interaction_Module__
#define __Calendar__User_Interaction_Module__

#include "Headers.h"

/*user interface do add events, takes a pointer to Calendar as argument. Requests, form the user, informations about the new event. Only takes valid informations. Will return without changes if the user types "0" at the Title and Description field. Returns if provided pointer is NULL.*/
void userAddEvent (Calendar *calendar);
/*User interface to edit events. Takes a pointer to Calendar as argument. Calls userSearchEvent() and asks wich info about the selected event he wants to edit. The user may edit the title, the description, the date, and, remove the event. Returns unchanged if provided pointer is NULL or if selected option is '0'.*/
void userEditEvent (Calendar *calendar);
/*User interface to search for events. Takes a pointer to Calendar as argument. Returns NULL if calendar is NULL, if it's not possible to find any results, or, if the selected option is '0'. The user may search by title, description, date or keyword.*/
Event* userSearchEvent (Calendar *calendar);
/*Module of userSearchEvent() function, requests from the user the words to search for and calls enqueueEventsWithSimilarText. Takes a pointer to Calendar as argument. Returns NULL if provided calendar is NULL. Returns a SearchingHp with maching events.*/
SearchingHp* userSearchEventByTitle (Calendar *calendar);
/*Module of userSearchEvent() function, requests from the user the words to search for and calls enqueueEventsWithSimilarText. Takes a pointer to Calendar as argument. Returns NULL if provided calendar is NULL. Returns a SearchingHp with maching events.*/
SearchingHp* userSearchEventByDesc (Calendar *calendar);
/*Module of userSearchEvent() function, requests from the user the date to search for and calls enqueueEventsWithProvidedDate. Takes a pointer to Calendar as argument. Returns NULL if provided calendar is NULL. Returns a SearchingHp with maching events.*/
SearchingHp* userSearchEventByDate (Calendar *calendar);
/*Module of userSearchEvent() function, requests from the user the words to search for and calls enqueueEventsWithSimilarText. Takes a pointer to Calendar as argument. Returns NULL if provided calendar is NULL. Returns a SearchingHp with maching events. This function searches on both the description and title tables.*/
SearchingHp* userSearchEventByKeywords (Calendar *calendar);
/*Module of userEditEvent(), requests form the user the info to replace in the event, depending on previously selected option. Takes a int option, pointer to Date, pointer to char, int destLength and pointer to Event as argument.*/
void userEditEventGetInput (int option, Date *date, char *dest, int destLength);
/*Module of userEditEvent(), performs the edition on the requested event.Takes a int option, pointer to Date, pointer to char, int destLength, pointer to Event and pointer to Calendar as argument.*/
void userEditEventEditEvent (int option, Date *date, char *str, int destLength, Event *event, Calendar *calendar);
/*Takes pointer to Event as argument. Requests recurrency information for this event and attributes this information to the provided event.*/
void userSetupRecorrentEvent (Event *event);
/*Takes pointer to Event as argument. Requests recurrency information for this event and attributes this information to the provided event.*/
void userSetupRecorrentEventWeeklyEvent (Event *event);
/*Takes pointer to Event as argument. Requests recurrency information for this event and attributes this information to the provided event.*/
void userSetupRecorrentEventMonthlyEvent (Event *event);
/*Takes pointer to Event as argument. Requests recurrency information for this event and attributes this information to the provided event.*/
void userSetupRecorrentEventYearlyEvent (Event *event);

#endif /* defined(__Calendar__User_Interaction_Module__) */

//
//  Output.h
//  Calendar
//
//  Created by Bruno Chroniaris on 11/10/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#ifndef __Calendar__Output__
#define __Calendar__Output__

#include "Headers.h"

/*gets a pointer to a stream and a pointer to a str. Prints the provided str to the provided stream. If any of the provided pointer is NULL, returns without changes;*/
void printBulletedListLine (FILE *stream, char *str);
/*takes a pointer to a stream and a pointer to a event as argument. Prints the provided Event info to the provided stream. If any of the provided pointer is NULL, returns unchanged.*/
void printEvent (FILE *stream, Event *event);
/*takes a pointer to a stream and a pointer to a event as argument. Prints the provided Event Title to the provided stream. If any of the provided pointer is NULL, returns unchanged.*/
void printEventTitle (FILE *stream, Event *event);
/*takes a pointer to a stream and a pointer to a SearchingHp as argument. Dequeues the provided SearchingHp and prints the Events Info, keeps calling it self recursively until there is no more events left in the provided heap. returns if any of the provided pointers is NULL*/
void printHeapOfEvents (FILE *stream, SearchingHp *events);
/*takes a pointer to a stream and a pointer to a SearchingHp as argument. Dequeues the provided SearchingHp and prints the Events Titles, keeps calling it self recursively until there is no more events left in the provided heap. returns if any of the provided pointers is NULL*/
void printEventTitlesOfHeapOfEvents (FILE *stream, SearchingHp *events);

#endif /* defined(__Calendar__Output__) */

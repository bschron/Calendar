//
//  Search Table.h
//  calendar
//
//  Created by Bruno Chroniaris on 11/5/14.
//  Copyright (c) 2014 UNIUM automação. All rights reserved.
//

#ifndef __calendar__Search_Table__
#define __calendar__Search_Table__

#include "Headers.h"

/*returns a pointer to a new search table with empty flags*/
SearchTable* createEmptySearchTable (void);
/*returns a hash integer to the provided word*/
int hashWord (char *word);
/*returns the sum of every character on that string*/
int wordSum (char *word);
/*returns the sum of the sum of every character from every memory position from the provided string*/
int wordPointerSum (char *word);
/*maps the provided event on the search tables*/
void mapEventOnSearchTables (Event *event);
/*inserts each word from the provided Event title to the titleSearchTable table*/
void mapEventTitle (Event *event);
/*inserts each words from the provided Event Description to the descriptionSearchTable table*/
void mapEventDescription (Event *event);
/*inserts each event day, month and year to dateSearchTable table*/
void mapEventDate (Event *event);
/*sets all table pointers to NULL*/
void initializeSearchTable (SearchTable *var);

#endif /* defined(__calendar__Search_Table__) */

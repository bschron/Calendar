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

SearchTable* createEmptySearchTable (void);
int hashWord (char *word);
int wordSum (char *word);
int wordPointerSum (char *word);
void mapEventOnSearchTable (Event *event);

#endif /* defined(__calendar__Search_Table__) */

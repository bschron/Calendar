//
//  Date and Time.h
//  Calendar
//
//  Created by Bruno Chroniaris on 11/9/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#ifndef __Calendar__Date_and_Time__
#define __Calendar__Date_and_Time__

#include "Headers.h"

/*Takes a pointer to a Date structure and attributtes the current time values to it. Allocates a new Date if the provided pointer is NULL and if there is some failure attributing the current time, returns a Date with empty values flags.*/
Date* getDate (Date *date);

#endif /* defined(__Calendar__Date_and_Time__) */

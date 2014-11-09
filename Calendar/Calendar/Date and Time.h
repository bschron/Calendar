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

/*takes three pointers to integer, for day, month and year, respectively. Attributes the current Date from the computer, with the following format: dd-mm-yyyy. returns -1 if there was some error getting the current time and 0 if everything is ok*/
int getDate (int *day, int *month, int *year);

#endif /* defined(__Calendar__Date_and_Time__) */

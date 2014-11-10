//
//  Main.h
//  Calendar
//
//  Created by Bruno Chroniaris on 11/6/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#ifndef Calendar_Main_h
#define Calendar_Main_h

#include "Headers.h"
int main (void);
/*prints Main Menu options*/
void printMainMenu (void);
/*gets the option selected by the user, call the requested function and returns 1. If the user selects the option 0, will return 0, wich means that the user wants to quite the program. If the User enters a invalid input, will inform the user of the wrong input and recursively call the function again*/
int getMainMenuOptions (Calendar *calendar);
#endif

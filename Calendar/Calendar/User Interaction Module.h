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


void userAddEvent (Calendar *calendar);

void userEditEvent (Calendar *calendar);

Event* userSearchEvent (Calendar *calendar);

SearchingHp* userSearchEventByTitle (Calendar *calendar);

SearchingHp* userSearchEventByDesc (Calendar *calendar);

SearchingHp* userSearchEventByDate (Calendar *calendar);

SearchingHp* userSearchEventByKeywords (Calendar *calendar);


#endif /* defined(__Calendar__User_Interaction_Module__) */

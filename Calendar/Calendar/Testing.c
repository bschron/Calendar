//
//  Testing.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/17/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Testing.h"

void testing (Calendar *main)
{
    int nOfData = 3;
    int i;
    
    Event *testEvents = createRandomSetOfEvents(NULL, nOfData);
    EventBinarySearchTree *root = insertDataToEventBinarySearchTree(NULL, testEvents, nOfData, insertEventBinarySearchTree);
    
    int result = checkIfGotEveryEventFromList(root, testEvents);
    
    getchar();
}
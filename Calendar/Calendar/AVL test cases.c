//
//  AVL test cases.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/19/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "AVL test cases.h"

int avlTestCases (EventBinarySearchTree *root)
{
    return 1;
}

EventBinarySearchTree* insertDataToEventBinarySearchTree (EventBinarySearchTree *root, EventBinarySearchTree *data, int nOfData, void (*insert) (EventBinarySearchTree**, EventBinarySearchTree*))
{
    if (data == NULL || nOfData <= 0)
    {
        return root;
    }
    
    //insertEventBinarySearchTree(&root, data);
    (*insert) (&root, data);
    
    return insertDataToEventBinarySearchTree(root, data+1, nOfData-1, insert);
}

Event* createRandomSetOfEvents (Event *events, int nOfEvents)
{
    if (nOfEvents == 0)
    {
        return events;
    }
    
    int n = 1;
    Date *date = createDate(1, 2, 2014);
    
    if (events != NULL)
    {
        sscanf(events->title, "%*s %d", &n);
        n++;
        *date = *events->date;
        date = increaseDate(date);
    }
    
    char *title = (char*) malloc(sizeof(char)*Max);
    sprintf(title, "test %d", n);
    events = eventInsertEvent(events, createEvent(1, 2, 2012, "testing event", title, 0, NULL));
    free(title);
    free(date);
    return createRandomSetOfEvents(events, nOfEvents-1);
}
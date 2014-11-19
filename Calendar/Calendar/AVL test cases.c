//
//  AVL test cases.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/19/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "AVL test cases.h"

int avlTestCases (void)
{
    int nOfEventsForTesting = 666;
    FILE *outputf = stdin;//output file
    EventBinarySearchTree *tree = NULL;
    int finalResult = 1;
    
    //list of events for testing
    Event *testCasesEvents = createRandomSetOfEvents(NULL, 666);
    //insert testing events to AVL
    tree = insertDataToEventBinarySearchTree(tree, testCasesEvents, nOfEventsForTesting, insertEventBinarySearchTree);
    
    //check if all elements are on the list
    {
        int result = checkIfGotEveryEventFromList(tree, testCasesEvents);
        fprintf(outputf, "Inserting - %d", result);
        if (result == 0)
        {
            finalResult--;
        }
    }
    
    
    //free
    freeAllEvents(&testCasesEvents);
    freeAllEventBinarySearchTree(&tree);
    
    return finalResult;
}

EventBinarySearchTree* insertDataToEventBinarySearchTree (EventBinarySearchTree *root, Event *data, int nOfData, void (*insert) (EventBinarySearchTree**, EventBinarySearchTree*))
{
    if (data == NULL || nOfData <= 0)
    {
        return root;
    }
    
    //insertEventBinarySearchTree(&root, data);
    (*insert) (&root, createEventBinarySearchTree(data));
    
    return insertDataToEventBinarySearchTree(root, data->next, nOfData-1, insert);
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

int checkIfGotEveryEventFromList (EventBinarySearchTree *root, Event *list)
{
    if (list == NULL)
    {
        return -1;
    }
    else if (root == NULL)
    {
        return -1;
    }
    
    int i, i2;
    int length = eventListLength(list);
    Event *events[length];
    TWC *enlisted = NULL;
    enlisted = EventBinarySearchTreeToList(root, enlisted);
    int length2 = objectListLength(enlisted);
    Event *enlistedEvents[length2];
    int results[length];
    int result = 1;
    
    if (length != length2)
    {
        freeAllTWC(&enlisted);
        return 0;
    }
    
    //set events array
    for (i = 0, events[length-1] = list; i<length; i++)
    {
        if (i != 0)//if not first
        {
            events[length-1] = events[length-1]->next;
        }
        events[i] = events[length-1];
        enlistedEvents[i] = popObject(&enlisted);
    }
    //set results to 0
    for (i = 0; i<length; i++)
    {
        results[i] = 0;
    }
    /*the next function will go event by event, from events array, and search for a event on the enlistedEvents array that is exactely the same. If found, will write 1, meaning success, to the results array on the position of the first array.*/
    for (i = 0; i<length; i++)
    {
        for (i2 = 0; i2<length2 && events[i] != NULL; i2++)
        {
            if (events[i] == enlistedEvents[i2])
            {
                results[i] = 1;
                enlistedEvents[i2] = NULL;
                break;
            }
        }
    }
    /*the following loop searches for a position on the results array that has value differente than 1. If any, will set this function result to 0.*/
    for (i = 0; i<length; i++)
    {
        if (results[i] != 1)
        {
            result = 0;
        }
    }
    
    freeAllTWC(&enlisted);
    return result;
}

int eventListLength (Event *list)
{
    if (list == NULL)
    {
        return 0;
    }
    
    return eventListLength(list->next) + 1;
}
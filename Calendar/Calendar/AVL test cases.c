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
    int nOfEventsForTesting = 4;
    FILE *outputf = stdout;//output file
    EventBinarySearchTree *tree = NULL;
    int finalResult = 1;
    fprintf(outputf, "AVL test cases: %d\n", nOfEventsForTesting);
    
    //list of events for testing
    Event *testCasesEvents = createRandomSetOfEvents(NULL, nOfEventsForTesting);
    //insert testing events to AVL
    tree = insertDataToEventBinarySearchTree(tree, testCasesEvents, nOfEventsForTesting, insertEventBinarySearchTree);
    
    //check if all elements are on the list
    {
        int result = checkIfGotEveryEventFromList(tree, testCasesEvents);
        fprintf(outputf, "Inserting - %d\n", result);
        if (result == 0)
        {
            finalResult--;
        }
    }
    
    //check if balancing is ok
    {
        int initial = 1;
        int result = checkIfEveryNodeIsBalanced(initial, tree);
        fprintf(outputf, "Balancing - %d\n", result/initial);
        if (result != initial)
        {
            finalResult--;
        }
    }
    //check if searching is ok
    {
        int initial = 1;
        int result = checkSearching(initial, &tree, testCasesEvents);
        fprintf(outputf, "Searching - %d\n", result/initial);
        if (result != initial)
        {
            finalResult--;
        }
    }
    //check if removing is ok
    {
        int initial = 1;
        int result = checkRemoval(initial, testCasesEvents, nOfEventsForTesting, insertEventBinarySearchTree);
        fprintf(outputf, "Removing - %d\n", result/initial);
        if (result != initial)
        {
            finalResult--;
        }
    }
    //check removal balance
    {
        int initial  = 1;
        int result = checkRemovalBalance(initial, testCasesEvents, nOfEventsForTesting, insertEventBinarySearchTree);
        fprintf(outputf, "Removal Balance - %d\n", result/initial);
        if (result != initial)
        {
            finalResult--;
        }
    }
    //free
    freeAllEvents(&testCasesEvents);
    freeAllEventBinarySearchTree(&tree);
    
    fprintf(outputf, "\n\nFinal Result: %d\n", finalResult);
    
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

int checkIfEveryNodeIsBalanced (int result, EventBinarySearchTree *root)
{
    if (root == NULL)
    {
        return result;
    }
    
    if (eventBinarySearchTreeBalanceFactor(root) < -1 || eventBinarySearchTreeBalanceFactor(root) > 1)
    {
        result--;
    }
    
    result = checkIfEveryNodeIsBalanced(result, root->leftChild);
    result = checkIfEveryNodeIsBalanced(result, root->rightChild);
    
    return result;
}

int checkSearching (int result, EventBinarySearchTree **root, Event *list)
{
    if (root == NULL)
    {
        return result-1;
    }
    else if (*root == NULL)
    {
        return result-1;
    }
    else if (list == NULL)
    {
        return result;
    }
    
    EventBinarySearchTree **found = searchEventBinarySearchTree(root, list);
    
    if ((*found)->event != list)
    {
        result--;
    }
    
    return checkSearching(result, root, list->next);
}

int checkRemoval (int result, Event *list, int nOfData, void (*insert) (EventBinarySearchTree **, EventBinarySearchTree *))
{
    if (list == NULL)
    {
        return result-1;
    }
    
    Event *current = NULL;
    EventBinarySearchTree *tree = insertDataToEventBinarySearchTree(NULL, list, nOfData, insert);
    
    for (current = list; current!= NULL; current = current->next)
    {
        EventBinarySearchTree **remove = searchEventBinarySearchTree(&tree, current);
        Event *event = (*remove)->event;
        removeEventBinarySearchTree(remove);
        if (searchEventBinarySearchTree(&tree, event) != NULL)
        {
            result--;
        }
    }
    freeAllEventBinarySearchTree(&tree);
    //goes straigth to last element of the list
    for (current = list; current->next != NULL; current = current->next);
    tree = insertDataToEventBinarySearchTree(NULL, list, nOfData, insert);
    for (; current != NULL; current = current->previous)
    {
        EventBinarySearchTree **remove = searchEventBinarySearchTree(&tree, current);
        Event *event = (*remove)->event;
        removeEventBinarySearchTree(remove);
        if (searchEventBinarySearchTree(&tree, event) != NULL)
        {
            result--;
        }
    }
    freeAllEventBinarySearchTree(&tree);
    
    return result;
}

int checkRemovalBalance (int result, Event *list, int nOfData, void (*insert) (EventBinarySearchTree **, EventBinarySearchTree *))
{
    if (list == NULL)
    {
        return result-1;
    }
    
    Event *current = NULL;
    EventBinarySearchTree *tree = insertDataToEventBinarySearchTree(NULL, list, nOfData, insert);
    for (current = list; current!=NULL; current = current->next)
    {
        EventBinarySearchTree **remove = searchEventBinarySearchTree(&tree, current);
        removeEventBinarySearchTree(remove);
        result = checkIfEveryNodeIsBalanced(result, tree);
    }
    
    freeAllEventBinarySearchTree(&tree);
    return result;
}
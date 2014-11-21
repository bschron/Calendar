//
//  Testing.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/17/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Testing.h"

void testing (void)
{
    avlTestCases();
    /*
    int n = 8;
    
    Event *list = createRandomSetOfEvents(NULL, n);
    EventBinarySearchTree *tree = insertDataToEventBinarySearchTree(NULL, NULL, list, n, insertEventBinarySearchTree);
    
    tree = balanceTillRoot(*eventBinarySearchTreeLeftMostChild(&tree), tree);
    
    int i = checkIfEveryNodeIsBalanced(1, tree);
    */
    getchar();
}
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

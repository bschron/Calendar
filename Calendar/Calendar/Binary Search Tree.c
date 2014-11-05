//
//  Binary Search Tree.c
//  calendar
//
//  Created by Bruno Chroniaris on 11/5/14.
//  Copyright (c) 2014 UNIUM automação. All rights reserved.
//

#include "Binary Search Tree.h"

EventBinarySearchTree* createEmptyBinaryTree (void)
{
    EventBinarySearchTree *new = (EventBinarySearchTree*) malloc(sizeof(EventBinarySearchTree));
    
    *new = returnEmptyEventBinarySearchTree();
    
    return new;
}

EventBinarySearchTree returnEmptyEventBinarySearchTree (void)
{
    EventBinarySearchTree empty;
    
    empty.event = NULL;
    empty.leftChild = NULL;
    empty.nameHash = 0;
    empty.rightChild = NULL;
    empty.tieBreakerFactor = 0;
    
    return empty;
}

int eventBinarySearchThreeHeigth (EventBinarySearchTree *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else if (root->rightChild == NULL && root->leftChild == NULL)
    {
        return 1;
    }
    else
    {
        return max(eventBinarySearchThreeHeigth(root->leftChild), eventBinarySearchThreeHeigth(root->rightChild)) + 1;
    }
}
//
//  Binary Search Tree.h
//  calendar
//
//  Created by Bruno Chroniaris on 11/5/14.
//  Copyright (c) 2014 UNIUM automação. All rights reserved.
//

#ifndef __calendar__Binary_Search_Tree__
#define __calendar__Binary_Search_Tree__

#include "Headers.h"


EventBinarySearchTree* createEmptyEventBinaryTree (void);
EventBinarySearchTree* createEventBinarySearchTree (Event *event);
EventBinarySearchTree returnEmptyEventBinarySearchTree (void);
int eventBinarySearchThreeHeigth (EventBinarySearchTree *root);
void insertEventBinarySearchTree (EventBinarySearchTree **root, EventBinarySearchTree *new);
EventBinarySearchTree** searchEventBinarySearchTree (EventBinarySearchTree **root, Event *wanted);
EventBinarySearchTree** eventBinarySearchTreeLeftMostChild (EventBinarySearchTree **root);
EventBinarySearchTree** eventBinarySearchTreeRightMostChild (EventBinarySearchTree **root);
void removeEventBinarySearchTree (EventBinarySearchTree **remove);
//AVL
EventBinarySearchTree* eventBinarySearchTreeLLCase (EventBinarySearchTree *root);
EventBinarySearchTree* eventBinarySearchTreeRRCase (EventBinarySearchTree *root);
EventBinarySearchTree* eventBinarySearchTreeLRCase (EventBinarySearchTree *root);
EventBinarySearchTree* eventBinarySearchTreeRLCase (EventBinarySearchTree *root);
int eventBinarySearchTreeBalanceFactor (EventBinarySearchTree *root);
EventBinarySearchTree* balanceEventBinarySearchTree (EventBinarySearchTree *root);

#endif /* defined(__calendar__Binary_Search_Tree__) */

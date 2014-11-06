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

/*returns a pointer to a new EventBinarySearchTree with empty flags*/
EventBinarySearchTree* createEmptyEventBinaryTree (void);
/*returns a pointer to a new EventBinarySearchTree with the provided event values*/
EventBinarySearchTree* createEventBinarySearchTree (Event *event);
/*returns a EventBinarySearchTree with empty flags*/
EventBinarySearchTree returnEmptyEventBinarySearchTree (void);
/*returns the value of the provided EventBinarySearchTree Heigth*/
int eventBinarySearchThreeHeigth (EventBinarySearchTree *root);
/*inserts a new EventBinarySearchTree to the provided root, if the provided EventBinarySEarchTree pointer is NULL, will return and do nothing*/
void insertEventBinarySearchTree (EventBinarySearchTree **root, EventBinarySearchTree *new);
/*searches a EventBinarySearchTree, below the provided root, with the provided event and returns a double pointer to it. If a matching case is not found, will return a NULL pointer*/
EventBinarySearchTree** searchEventBinarySearchTree (EventBinarySearchTree **root, Event *wanted);
/*returns a double pointer to the left most child from the provided EventBinarySearchTree*/
EventBinarySearchTree** eventBinarySearchTreeLeftMostChild (EventBinarySearchTree **root);
/*returns a double pointer to the right most child from the provided EventBinarySearchTree*/
EventBinarySearchTree** eventBinarySearchTreeRightMostChild (EventBinarySearchTree **root);
/*removes the providede EventBinarySearchTree, respecting the BinaryTree properties*/
void removeEventBinarySearchTree (EventBinarySearchTree **remove);
//AVL
/*the functions below are responsible to balancing the tree for a LOGn search*/
EventBinarySearchTree* eventBinarySearchTreeLLCase (EventBinarySearchTree *root);
EventBinarySearchTree* eventBinarySearchTreeRRCase (EventBinarySearchTree *root);
EventBinarySearchTree* eventBinarySearchTreeLRCase (EventBinarySearchTree *root);
EventBinarySearchTree* eventBinarySearchTreeRLCase (EventBinarySearchTree *root);
int eventBinarySearchTreeBalanceFactor (EventBinarySearchTree *root);
EventBinarySearchTree* balanceEventBinarySearchTree (EventBinarySearchTree *root);

#endif /* defined(__calendar__Binary_Search_Tree__) */

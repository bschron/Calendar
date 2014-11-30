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
/*Takes a pointer to Event *events as argument. Allocates a new EventBinarySearchTree, attributes the provided pointer as argument and returns a pointer to the newly allocated EventBinarySearchTree.*/
EventBinarySearchTree* createEventBinarySearchTree (Event *event);
/*returns a EventBinarySearchTree with empty flags*/
EventBinarySearchTree returnEmptyEventBinarySearchTree (void);
/*returns the value of the provided EventBinarySearchTree Heigth*/
int eventBinarySearchThreeHeigth (EventBinarySearchTree *root);
/*inserts a new EventBinarySearchTree to the provided root, if the provided EventBinarySEarchTree pointer is NULL, will return and do nothing*/
void insertEventBinarySearchTree (EventBinarySearchTree **root, EventBinarySearchTree *new, EventBinarySearchTree *parent);
/*searches a EventBinarySearchTree, below the provided root, with the provided event and returns a double pointer to it. If a matching case is not found, will return a NULL pointer*/
EventBinarySearchTree** searchEventBinarySearchTree (EventBinarySearchTree **root, Event *wanted);
/*returns a double pointer to the left most child from the provided EventBinarySearchTree*/
EventBinarySearchTree** eventBinarySearchTreeLeftMostChild (EventBinarySearchTree **root);
/*returns a double pointer to the right most child from the provided EventBinarySearchTree*/
EventBinarySearchTree** eventBinarySearchTreeRightMostChild (EventBinarySearchTree **root);
/*removes the providede EventBinarySearchTree, respecting the BinaryTree properties*/
EventBinarySearchTree* removeEventBinarySearchTree (EventBinarySearchTree *root, EventBinarySearchTree **remove);
/*Takes a pointer to EventBinarySearchTree root and a pointer to TWC list as arguments. Inserts every event from the provided EventBinarySearchTree to the provided object list. Returns the list unchanged if provided root is NULL.*/
TWC* EventBinarySearchTreeToList (EventBinarySearchTree *root, TWC *list);
/*takes a double pointer to EventBinarySearchTree as argument. Frees every element of the provided tree and set the provided pointer to NULL.*/
void freeAllEventBinarySearchTree (EventBinarySearchTree **root);
/*Takes a double pointer to EventBinarySearchTree as argument. Frees te provided tree and attributes NULL to it's pointer.*/
void freeEventBinarySearchTree (EventBinarySearchTree **tree);
/*Takes a pointer to EventBinarySearchTRee *root as argument. Returns a pointer to the provided root's left child. Returns NULL if provided pointer is NULL.*/
EventBinarySearchTree* peekLeftChild (EventBinarySearchTree *root);
/*Takes a pointer to EventBinarySearchTRee *root as argument. Returns a pointer to the provided root's right child. Returns NULL if provided pointer is NULL.*/
EventBinarySearchTree* peekRightChild (EventBinarySearchTree *root);
/*Takes a pointer to EventBinarySearchTree *root s argument. Returns a pointer to the provided tree's event. Returns NULL if the provided pointer is NULL.*/
Event* peekTreeEvent (EventBinarySearchTree *root);

//AVL
/*the functions below are responsible to balancing the tree for a LOGn search*/
EventBinarySearchTree* eventBinarySearchTreeLLCase (EventBinarySearchTree *root);
EventBinarySearchTree* eventBinarySearchTreeRRCase (EventBinarySearchTree *root);
EventBinarySearchTree* eventBinarySearchTreeLRCase (EventBinarySearchTree *root);
EventBinarySearchTree* eventBinarySearchTreeRLCase (EventBinarySearchTree *root);
int eventBinarySearchTreeBalanceFactor (EventBinarySearchTree *root);
EventBinarySearchTree* balanceEventBinarySearchTree (EventBinarySearchTree *root);
EventBinarySearchTree* balanceTillRoot (EventBinarySearchTree *start, EventBinarySearchTree *root);

#endif /* defined(__calendar__Binary_Search_Tree__) */

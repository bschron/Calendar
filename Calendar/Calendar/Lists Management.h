//
//  Lists Management.h
//  Calendar
//
//  Created by Bruno Chroniaris on 11/6/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#ifndef __Calendar__Lists_Management__
#define __Calendar__Lists_Management__

#include "Headers.h"

/*inserts a node with the provided values to the provided list and returns a pointer to the new Node*/
Node* insertNode (Node* first, char* name, int index);
/*removes provided Node from list and returns a pointer to the first element*/
Node* removeNode (Node* remove, Node* first);
/*searches for a matching case with the provided name an returns a pointer to it, if the name is a empty string, the list is empty or there is no matching case, will return a NULL pointer*/
Node* searchNodeByName (Node* first, char* name);
/*searches a node with the provided index and returns a pointer to it, if there is no matching case or the list is empty, will return a NULL pointer*/
Node* searchNodeByIndex (Node* first, int index);
/*free all nodes from the provided list and return a NULL pointer to the first element*/
Node* freeAllNodes (Node* first);
/*looks the provided node and returns 1 if it has all the empty flags, else returns 0*/
int emptyNode (Node *item);
/*returns a Node with empty flags*/
Node returnEmptyNode (void);
/*returns the value of the first node from the list and removes it. But if list is NULL, will return a node with empty flags*/
Node popNode (Node **first);

#endif /* defined(__Calendar__Lists_Management__) */

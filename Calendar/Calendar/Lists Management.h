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

Node* insertNode (Node* first, char* name, int index);
Node* removeNode (Node* remove, Node* first);
Node* searchNodeByName (Node* first, char* name);
Node* searchNodeByIndex (Node* first, int index);
Node* freeAllNodes (Node* first);
int isNodeEmpty (Node *item);
Node returnEmptyNode (void);

#endif /* defined(__Calendar__Lists_Management__) */

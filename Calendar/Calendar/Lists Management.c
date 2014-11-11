//
//  Lists Management.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/6/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Lists Management.h"

Node *insertNode (Node* first, char* name, int index)
{
    Node* pointer;
    
    if (first == NULL)
    {
        pointer = (Node*) malloc(sizeof(Node));
        strcpy(pointer->name, name);
        pointer->index = index;
        pointer->next = NULL;
        pointer->previous = NULL;
        return pointer;
    }
    else if (first->previous != NULL)
    {
        return insertNode(first->previous, name, index);
    }
    else
    {
        pointer = (Node*) malloc(sizeof(Node));
        strcpy(pointer->name, name);
        pointer->index = index;
        pointer->previous = first->previous;
        pointer->next = first;
        first->previous = pointer;
        return pointer;
    }
}

Node popNode (Node **first)
{
    if (*first == NULL)
    {
        return returnEmptyNode();
    }
    
    Node popped = **first;
    
    *first = removeNode(*first, *first);
    
    return popped;
}

Node* removeNode (Node* remove, Node* first)
{
    Node* pointer;
    
    if (first == NULL || remove == NULL)
    {
        return first;
    }
    else if (first->previous != NULL)
    {
        return removeNode(remove, first->previous);
    }
    else if (remove->previous == NULL && remove->next == NULL)
    {
        free(remove);
        return NULL;
    }
    else if (remove == first && remove->next != NULL)
    {
        remove->next->previous = NULL;
        pointer = remove->next;
        free(remove);
        return pointer;
    }
    else if (remove == first)
    {
        free(remove);
        return NULL;
    }
    else if (remove->next == NULL)
    {
        remove->previous->next = NULL;
        free(remove);
        return first;
    }
    else
    {
        remove->previous->next = remove->next;
        remove->next->previous = remove->previous;
        free(remove);
        return first;
    }
}

Node* searchNodeByName (Node* first, char* name)
{
    if (first == NULL || strcmp(name, "") == 0)
    {
        return NULL;
    }
    else if (strcmp(first->name, name) == 0)
    {
        return first;
    }
    else if (first->next != NULL)
    {
        return searchNodeByName(first->next, name);
    }
    else
    {
        return NULL;
    }
}

Node* searchNodeByIndex (Node* first, int index)
{
    if (first == NULL)
    {
        return NULL;
    }
    else if (first->index == index)
    {
        return first;
    }
    else if (first->next != NULL)
    {
        return searchNodeByIndex(first->next, index);
    }
    else
    {
        return NULL;
    }
}

Node* freeAllNodes (Node* first)
{
    if (first == NULL)
    {
        return NULL;
    }
    else
    {
        Node *next = first->next;
        
        free(first);
        if (next == NULL)
        {
            return NULL;
        }
        else
        {
            return freeAllNodes(next);
        }
    }
}

int emptyNode (Node *item)
{
    if (item == NULL)
    {
        return 1;
    }
    else if (item->index == not_in_use && sizeOfStr(item->name) == 0 && item->next == NULL && item->previous == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Node returnEmptyNode (void)
{
    Node empty;
    snprintf(empty.name, sizeof(empty.name)/sizeof(char), "");
    empty.index = -1;
    empty.next = NULL;
    empty.previous = NULL;
    return empty;
}
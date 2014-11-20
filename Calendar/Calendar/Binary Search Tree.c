//
//  Binary Search Tree.c
//  calendar
//
//  Created by Bruno Chroniaris on 11/5/14.
//  Copyright (c) 2014 UNIUM automação. All rights reserved.
//

#include "Binary Search Tree.h"

EventBinarySearchTree* createEmptyEventBinaryTree (void)
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
    
    return empty;
}

EventBinarySearchTree* createEventBinarySearchTree (Event *event)
{
    EventBinarySearchTree *new = createEmptyEventBinaryTree();
    
    new->event = event;
    new->nameHash = hashWord(event->title)+hashWord(event->desc);
    
    return new;
}

void insertEventBinarySearchTree (EventBinarySearchTree **root, EventBinarySearchTree *new)
{
    if (new == NULL)
    {
        return;
    }
    else if (*root == NULL)
    {
        *root = new;
        return;
    }
    
    EventBinarySearchTree **next = NULL;
    
    if ((*root)->event < new->event)
    {
        next = &(*root)->rightChild;
    }
    else
    {
        next = &(*root)->leftChild;
    }
    
    *root = balanceEventBinarySearchTree(*root);
    
    insertEventBinarySearchTree(next, new);
    
    *root = balanceEventBinarySearchTree(*root);
    return;
}

EventBinarySearchTree** searchEventBinarySearchTree (EventBinarySearchTree **root, Event *wanted)
{
    if (*root == NULL || wanted == NULL)
    {
        return NULL;
    }
    
    EventBinarySearchTree *wantedStaple = createEventBinarySearchTree(wanted);
    
    if ((*root)->event == wantedStaple->event)
    {
        free(wantedStaple);
        return root;
    }
    else if ((*root)->event < wantedStaple->event)
    {
        free(wantedStaple);
        return searchEventBinarySearchTree(&(*root)->rightChild, wanted);
    }
    else
    {
        free(wantedStaple);
        return searchEventBinarySearchTree(&(*root)->leftChild, wanted);
    }
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

void removeEventBinarySearchTree (EventBinarySearchTree **remove)
{
    if (remove == NULL)
    {
        return;
    }
    else if (*remove == NULL)
    {
        return;
    }
    else if ((*remove)->leftChild == NULL && (*remove)->rightChild == NULL)
    {
        free(*remove);
        *remove = NULL;
    }
    else if ((*remove)->leftChild == NULL)
    {
        EventBinarySearchTree *rmv = *remove;
        
        *remove = (*remove)->rightChild;
        
        *remove = balanceEventBinarySearchTree(*remove);
        
        free(rmv);
        rmv = NULL;
        
        return;
    }
    else if ((*remove)->rightChild == NULL)
    {
        EventBinarySearchTree *rmv = *remove;
        
        *remove = (*remove)->leftChild;
        
        *remove = balanceEventBinarySearchTree(*remove);
        
        free(rmv);
        rmv = NULL;
        
        return;
    }
    else if (eventBinarySearchThreeHeigth((*remove)->leftChild) > eventBinarySearchThreeHeigth((*remove)->rightChild))
    {
        EventBinarySearchTree **substitute = eventBinarySearchTreeRightMostChild(&(*remove)->leftChild);
        
        (*remove)->event = (*substitute)->event;
        (*remove)->nameHash = (*substitute)->nameHash;
        
        removeEventBinarySearchTree(substitute);
        
        *remove = balanceEventBinarySearchTree(*remove);
        
        return;
    }
    else
    {
        EventBinarySearchTree **substitute = eventBinarySearchTreeLeftMostChild(&(*remove)->rightChild);
        
        (*remove)->event = (*substitute)->event;
        (*remove)->nameHash = (*substitute)->nameHash;
        
        removeEventBinarySearchTree(substitute);
        
        *remove = balanceEventBinarySearchTree(*remove);
        
        return;
    }
    
}

EventBinarySearchTree** eventBinarySearchTreeLeftMostChild (EventBinarySearchTree **root)
{
    if ((*root)->leftChild == NULL)
    {
        return root;
    }
    else
    {
        return  eventBinarySearchTreeLeftMostChild(&(*root)->leftChild);
    }
}

EventBinarySearchTree** eventBinarySearchTreeRightMostChild (EventBinarySearchTree **root)
{
    if ((*root)->rightChild == NULL)
    {
        return root;
    }
    else
    {
        return eventBinarySearchTreeRightMostChild(&(*root)->rightChild);
    }
}

EventBinarySearchTree* eventBinarySearchTreeLLCase (EventBinarySearchTree *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    
    EventBinarySearchTree *leftRight = root->leftChild->rightChild;
    
    root->leftChild->rightChild = root;
    root = root->leftChild;
    root->rightChild->leftChild = leftRight;
    
    return root;
}

EventBinarySearchTree* eventBinarySearchTreeRRCase (EventBinarySearchTree *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    
    EventBinarySearchTree *rightLeft = root->rightChild->leftChild;
    
    root->rightChild->leftChild = root;
    root = root->rightChild;
    root->leftChild->rightChild = rightLeft;
    
    return root;
}

EventBinarySearchTree* eventBinarySearchTreeLRCase (EventBinarySearchTree *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    
    EventBinarySearchTree *leftRightLeft = root->leftChild->rightChild->leftChild;
    
    root->leftChild->rightChild->leftChild = root->leftChild;
    root->leftChild = root->leftChild->rightChild;
    root->leftChild->leftChild->rightChild = leftRightLeft;
    
    return balanceEventBinarySearchTree(root);
}

EventBinarySearchTree* eventBinarySearchTreeRLCase (EventBinarySearchTree *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    
    EventBinarySearchTree *rightLeftRight = root->rightChild->leftChild->rightChild;
    
    root->rightChild->leftChild->rightChild = root->rightChild;
    root->rightChild = root->rightChild->leftChild;
    root->rightChild->rightChild->leftChild = rightLeftRight;
    
    return balanceEventBinarySearchTree(root);
}

int eventBinarySearchTreeBalanceFactor (EventBinarySearchTree *root)
{
    int left;
    int right;
    
    left = eventBinarySearchThreeHeigth(root->leftChild);
    right = eventBinarySearchThreeHeigth(root->rightChild);
    
    return left-right;
}

EventBinarySearchTree* balanceEventBinarySearchTree (EventBinarySearchTree *root)
{
    int factor = eventBinarySearchTreeBalanceFactor(root);
    
    if (factor > 1)//left case
    {
        if (eventBinarySearchTreeBalanceFactor(root->leftChild) < 0)//left right case
        {
            root = eventBinarySearchTreeLRCase(root);
        }
        else//left left case
        {
            root = eventBinarySearchTreeLLCase(root);
        }
    }
    else if (factor < -1)//right case
    {
        if (eventBinarySearchTreeBalanceFactor(root->rightChild) > 0)//right left case
        {
            root = eventBinarySearchTreeRLCase(root);
        }
        else//right right case
        {
            root = eventBinarySearchTreeRRCase(root);
        }
    }
    else//balanced
    {
        return root;
    }
    
    return root;
}

TWC* EventBinarySearchTreeToList (EventBinarySearchTree *root, TWC *list)
{
    if (root == NULL)
    {
        return list;
    }
    
    list = insertTWC(list, createTWC(root->event));
    
    list = EventBinarySearchTreeToList(root->leftChild, list);
    list = EventBinarySearchTreeToList(root->rightChild, list);
    
    return list;
}

void freeAllEventBinarySearchTree (EventBinarySearchTree **root)
{
    if (root == NULL)
    {
        return;
    }
    else if (*root == NULL)
    {
        return;
    }
    
    removeEventBinarySearchTree(root);
    
    return freeAllEventBinarySearchTree(root);
}
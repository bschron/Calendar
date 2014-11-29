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
    EventBinarySearchTree *new = (EventBinarySearchTree*) malloc(sizeof(EventBinarySearchTree));
    
    new->leftChild = NULL;
    new->rightChild = NULL;
    new->event = event;
    new->nameHash = hashWord(peekEventTitle(event))+hashWord(peekEventDesc(event));
    new->parent = (EventBinarySearchTree**) malloc(sizeof(EventBinarySearchTree*));
    *(new->parent) = NULL;
    
    return new;
}

void insertEventBinarySearchTree (EventBinarySearchTree **root, EventBinarySearchTree *new, EventBinarySearchTree *parent)
{
    if (new == NULL)
    {
        return;
    }
    else if (*root == NULL)
    {
        *new->parent = parent;
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
    
    insertEventBinarySearchTree(next, new, *root);
    
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
        freeEventBinarySearchTree(&wantedStaple);
        return root;
    }
    else if ((*root)->event < wantedStaple->event)
    {
        freeEventBinarySearchTree(&wantedStaple);
        return searchEventBinarySearchTree(&(*root)->rightChild, wanted);
    }
    else
    {
        freeEventBinarySearchTree(&wantedStaple);
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

EventBinarySearchTree* removeEventBinarySearchTree (EventBinarySearchTree *root, EventBinarySearchTree **remove)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (remove == NULL)
    {
        return root;
    }
    else if (*remove == NULL)
    {
        return root;
    }
    
    if ((*remove)->leftChild == NULL && (*remove)->rightChild == NULL)
    {
        EventBinarySearchTree *removeParent = *(*remove)->parent;
        
        if (root == *remove)
        {
            root = NULL;
        }
        
        //free(*remove);
        freeEventBinarySearchTree(remove);
        
        *remove = NULL;
        
        if (root != NULL)
        {
            root = balanceTillRoot(removeParent, root);
        }
        
    }
    else if ((*remove)->leftChild == NULL)
    {
        EventBinarySearchTree *rmv = *remove;
        
        *(*remove)->rightChild->parent = *(*remove)->parent;
        *remove = (*remove)->rightChild;
        
        //free(rmv);
        freeEventBinarySearchTree(&rmv);
        
        if (*(*remove)->parent == NULL)
        {
            root = *remove;
        }
        
        root = balanceTillRoot(*remove, root);
    }
    else if ((*remove)->rightChild == NULL)
    {
        EventBinarySearchTree *rmv = *remove;
        
        *(*remove)->leftChild->parent = *(*remove)->parent;
        *remove = (*remove)->leftChild;
        
        //free(rmv);
        freeEventBinarySearchTree(&rmv);
        
        if (*(*remove)->parent == NULL)
        {
            root = *remove;
        }
        
        root = balanceTillRoot(*remove, root);
    }
    else if (eventBinarySearchThreeHeigth((*remove)->leftChild) > eventBinarySearchThreeHeigth((*remove)->rightChild))
    {
        EventBinarySearchTree **substitute = eventBinarySearchTreeRightMostChild(&(*remove)->leftChild);
        
        (*remove)->event = (*substitute)->event;
        (*remove)->nameHash = (*substitute)->nameHash;
        
        root = removeEventBinarySearchTree(root, substitute);
    }
    else
    {
        EventBinarySearchTree **substitute = eventBinarySearchTreeLeftMostChild(&(*remove)->rightChild);
        
        (*remove)->event = (*substitute)->event;
        (*remove)->nameHash = (*substitute)->nameHash;
        
        root = removeEventBinarySearchTree(root, substitute);
    }
    
    return root;
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
    EventBinarySearchTree *rootParent = *root->parent;
    
    //parent attribution, then switching
    if (root != NULL)
    {
        *root->parent = root->leftChild;
    }
    root->leftChild->rightChild = root;
    //parent attribution, then switching
    if (root->leftChild != NULL)
    {
        *root->leftChild->parent = rootParent;
    }
    root = root->leftChild;
    //parent attribution, then switching
    if (leftRight != NULL)
    {
        *leftRight->parent = root->rightChild;
    }
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
    EventBinarySearchTree *rootParent = *root->parent;
    
    //parent attribution, then switching
    if (root != NULL)
    {
        *root->parent = root->rightChild;
    }
    root->rightChild->leftChild = root;
    //parent attribution, then switching
    if (root->rightChild != NULL)
    {
        *root->rightChild->parent = rootParent;
    }
    root = root->rightChild;
    //parent attribution, then switching
    if (rightLeft != NULL)
    {
        *rightLeft->parent = root->leftChild;
    }
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
    
    //parent attribution, then switching
    if (root->leftChild != NULL)
    {
        *root->leftChild->parent = root->leftChild->rightChild;
    }
    root->leftChild->rightChild->leftChild = root->leftChild;
    //parent attribution, then switching
    if (root->leftChild->rightChild != NULL)
    {
        *root->leftChild->rightChild->parent = root;
    }
    root->leftChild = root->leftChild->rightChild;
    //parent attribution, then switching
    if (leftRightLeft != NULL)
    {
        *leftRightLeft->parent = root->leftChild->leftChild;
    }
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
    
    //parent attribution, then switching
    if (root->rightChild != NULL)
    {
        *root->rightChild->parent = root->rightChild->leftChild;
    }
    root->rightChild->leftChild->rightChild = root->rightChild;
    //parent attribution, then switching
    if (root->rightChild->leftChild != NULL)
    {
        *root->rightChild->leftChild->parent = root;
    }
    root->rightChild = root->rightChild->leftChild;
    //parent attribution, then switching
    if (rightLeftRight != NULL)
    {
        *rightLeftRight->parent = root->rightChild->rightChild;
    }
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
    if (root == NULL)
    {
        return root;
    }
    
    int factor = eventBinarySearchTreeBalanceFactor(root);
    
    if (factor > 1)//left case
    {
        /*if (eventBinarySearchTreeBalanceFactor(root->leftChild) > 1 || eventBinarySearchTreeBalanceFactor(root->leftChild) < -1)
        {
            root = eventBinarySearchTreeLLCase(root);
        }
        else */if (eventBinarySearchTreeBalanceFactor(root->leftChild) < 0)//left right case
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
        /*if (eventBinarySearchTreeBalanceFactor(root->rightChild) > 1 || eventBinarySearchTreeBalanceFactor(root->rightChild) < -1)
        {
            root = eventBinarySearchTreeRRCase(root);
        }
        else */if (eventBinarySearchTreeBalanceFactor(root->rightChild) > 0)//right left case
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
    
     *root = removeEventBinarySearchTree(*root, root);
    
    return freeAllEventBinarySearchTree(root);
}

EventBinarySearchTree* balanceTillRoot (EventBinarySearchTree *start, EventBinarySearchTree *root)
{
    if (start == NULL || root == NULL)
    {
        return root;
    }
    
    int end = 0;
    int side = 0;
    EventBinarySearchTree *parent = *start->parent;
    
    if (start == root || *start->parent == NULL)
    {
        end = 1;
    }
    else if (start == parent->rightChild)
    {
        side = -1;
    }
    else
    {
        side = 1;
    }
    
    start = balanceEventBinarySearchTree(start);
    
    if (side == -1)
    {
        parent->rightChild = start;
    }
    else if (side == 1)
    {
        parent->leftChild = start;
    }
    
    if (!end)
    {
        return balanceTillRoot(*start->parent, root);
    }
    
    return start;
}

void freeEventBinarySearchTree (EventBinarySearchTree **tree)
{
    if (tree == NULL)
    {
        return;
    }
    else if (*tree == NULL)
    {
        return;
    }

    free((*tree)->parent);
    
    (*tree)->parent = NULL;
    
    free(*tree);
    
    *tree = NULL;
    
    return;
}
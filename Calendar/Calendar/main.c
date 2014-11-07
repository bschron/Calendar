//
//  main.c
//  calendar
//
//  Created by Bruno Chroniaris on 11/5/14.
//  Copyright (c) 2014 UNIUM automação. All rights reserved.
//

#include "Headers.h"

int main(void)
{
    titleSearchTable = createEmptySearchTable();
    
    Event *um = createEvent(10, 12, 2012, "teste", "teste01");
    Event *um2 = createEvent(10, 12, 2012, "teste", "teste01");
    Event *dois = createEvent(10, 12, 2012, "teste", "teste02");
    Event *tres = createEvent(10, 12, 2012, "teste", "teste03");
    Event *quatro = createEvent(10, 12, 2012, "teste", "teste04");
    Event *cinco = createEvent(10, 12, 2012, "teste", "teste05");
    Event *seis = createEvent(10, 12, 2012, "teste", "teste06");
    
    
    EventBinarySearchTree *tree = NULL;
    
    EventBinarySearchTree *teste01 = createEventBinarySearchTree(um);
    EventBinarySearchTree *teste01_2 = createEventBinarySearchTree(um2);
    EventBinarySearchTree *teste02 = createEventBinarySearchTree(dois);
    EventBinarySearchTree *teste03 = createEventBinarySearchTree(tres);
    EventBinarySearchTree *teste04 = createEventBinarySearchTree(quatro);
    EventBinarySearchTree *teste05 = createEventBinarySearchTree(cinco);
    EventBinarySearchTree *teste06 = createEventBinarySearchTree(seis);
    
    insertEventBinarySearchTree(&tree, teste01);
    insertEventBinarySearchTree(&tree, teste01_2);
    insertEventBinarySearchTree(&tree, teste02);
    insertEventBinarySearchTree(&tree, teste03);
    insertEventBinarySearchTree(&tree, teste04);
    insertEventBinarySearchTree(&tree, teste05);
    insertEventBinarySearchTree(&tree, teste06);
    
    EventBinarySearchTree **wanted = searchEventBinarySearchTree(&tree, um2);
    
    removeEventBinarySearchTree(wanted);
    
    SearchingHeap *heap = NULL;
    heap =
    
    getchar();
    
}
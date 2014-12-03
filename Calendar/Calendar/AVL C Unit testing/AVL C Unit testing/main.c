//
//  main.c
//  AVL C Unit testing
//
//  Created by Bruno Chroniaris on 12/2/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Headers.h"

int main(void)
{
    //create Search Tables for testing
    titleSearchTable = createEmptySearchTable();
    descriptionSearchTable = createEmptySearchTable();
    dateSearchTable = createEmptySearchTable();
    //run tests
    avlTestCases();
    //confirm
    confirmSucess();
    return 0;
}

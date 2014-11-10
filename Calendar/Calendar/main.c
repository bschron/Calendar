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
    descriptionSearchTable = createEmptySearchTable();
    dateSearchTable = createEmptySearchTable();
    
    Calendar *calendar = NULL;
    calendar = insertEvent(calendar, 16, 11, 2014, "marcado as 15h", "reuniao com higor da neocontrol");
    calendar = insertEvent(calendar, 1, 11, 2014, "vai ter cuscuz paulista", "jantar na casa da fran");
    calendar = insertEvent(calendar, 30, 11, 2014, "em caruaru", "aniversario do tio de fran");
    calendar = insertEvent(calendar, 12, 11, 2014, "no san nicolas", "reuniao dos manos");
    calendar = insertEvent(calendar, 11, 11, 2014, "estudar avl", "prova de p2");
    calendar = insertEvent(calendar, 1, 12, 2014, "estudar todas estruturas", "reavaliacao de p2");
    
    SearchingHp *hp = enqueueEventsForThisMonth(NULL, NULL);
    
    printHeapOfEvents(stdout, hp);
    
    getchar();
    
}
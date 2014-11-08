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
    
    Event *um = createEvent(10, 12, 2012, "teste", "teste01");
    Event *um2 = createEvent(10, 12, 2012, "teste", "teste01");
    Event *dois = createEvent(10, 12, 2012, "teste", "teste02");
    Event *tres = createEvent(10, 12, 2012, "teste", "teste03");
    Event *quatro = createEvent(10, 12, 2012, "teste", "teste04");
    Event *cinco = createEvent(10, 12, 2012, "teste", "teste05");
    Event *seis = createEvent(10, 12, 2012, "teste", "teste06");
    
    Calendar *calendar = NULL;
    calendar = insertEvent(calendar, 10, 12, 2012, "marcado as 15h", "reuniao com higor da neocontrol");
    calendar = insertEvent(calendar, 10, 12, 2012, "vai ter cuscuz paulista", "jantar na casa da fran");
    calendar = insertEvent(calendar, 10, 12, 2012, "em caruaru", "aniversario do tio de fran");
    calendar = insertEvent(calendar, 10, 12, 2012, "no san nicolas", "reuniao dos manos");
    calendar = insertEvent(calendar, 10, 12, 2012, "estudar avl", "prova de p2");
    calendar = insertEvent(calendar, 10, 12, 2012, "estudar todas estruturas", "reavaliacao de p2");
    
    SearchingHp *hp = NULL;
    
    hp = enqueueEventsWithSimilarText(hp, descriptionSearchTable, "marcado estudar 15h");
    
    getchar();
    
}
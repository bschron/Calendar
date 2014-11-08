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
    
    Calendar *calendar = NULL;
    calendar = insertEvent(calendar, 10, 12, 2012, "01", "reuniao com higor da neocontrol");
    calendar = insertEvent(calendar, 10, 12, 2012, "02", "jantar na casa da fran");
    calendar = insertEvent(calendar, 10, 12, 2012, "03", "aniversario do tio de fran");
    calendar = insertEvent(calendar, 10, 12, 2012, "04", "reuniao dos manos");
    calendar = insertEvent(calendar, 10, 12, 2012, "05", "prova de p2");
    calendar = insertEvent(calendar, 10, 12, 2012, "06", "reavaliacao de p2");
    
    SearchingHp *hp = NULL;
    
    hp = enqueueEventsWithSimilarTitle(hp, titleSearchTable, "reuniao nada neocontrol p2 manos");
    
    getchar();
    
}
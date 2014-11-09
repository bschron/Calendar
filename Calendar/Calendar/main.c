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
    calendar = insertEvent(calendar, 10, 12, 2012, "marcado as 15h", "reuniao com higor da neocontrol");
    calendar = insertEvent(calendar, 1, 12, 2012, "vai ter cuscuz paulista", "jantar na casa da fran");
    calendar = insertEvent(calendar, 10, 10, 2012, "em caruaru", "aniversario do tio de fran");
    calendar = insertEvent(calendar, 10, 12, 2012, "no san nicolas", "reuniao dos manos");
    calendar = insertEvent(calendar, 10, 10, 2012, "estudar avl", "prova de p2");
    calendar = insertEvent(calendar, 10, 1, 2014, "estudar todas estruturas", "reavaliacao de p2");
    
    SearchingHp *hp = NULL;
    
    exportEvents(calendar);
    
    Calendar *imported = importCalendarFromMainDirectory(NULL);
    
    struct timeval now;
    struct tm *tmp;
    char timestr[100];
    int rc;
    
    rc = gettimeofday(&now, 0);
    
    tmp = localtime(&now.tv_sec);
    
    rc = strftime(timestr, sizeof(timestr), "%D", tmp);
    
    int day, month, year;
    
    getDate(&day, &month, &year);
    
    getchar();
    
}
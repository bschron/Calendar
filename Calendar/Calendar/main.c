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
    
    Calendar *main = importCalendarFromMainDirectory(NULL);
    
    //
    int *f = (int*) malloc(sizeof(int)*7);
    f[0] = 1;
    f[1] = 0;
    f[2] = 0;
    f[3] = 0;
    f[4] = 0;
    f[5] = 1;
    f[6] = 0;
    Event *new = createEvent(16, 11, 2014, "teste", "teste01", 1, f);
    //
    
    do
    {
        resetScreen();
        
        printMainMenu();
        
        printf("\n\nEventos Agendados para esta Semana:\n");
        printEventQueueTitles(eventQueueEnqueueEventsForThisWeek(NULL));
        
        exportEvents(main);
    } while (getMainMenuOptions(main));
    
    exportEvents(main);
    
    getchar();
    
}

void printMainMenu (void)
{
    int optionNumber = 1;
    
    printf("\nOpcoes:\n");
    printOption(&optionNumber, "Adicionar evento");
    printOption(&optionNumber, "Editar evento");
    printOption(&optionNumber, "Ver eventos agendados para este mes");
    printOption(&optionNumber, "Procurar por evento agendado");
}

int getMainMenuOptions (Calendar *calendar)
{
    int option = getNumber();
    
    switch (option)
    {
        case 0://exit Program
            return 0;
            break;
        case 1:
            userAddEvent(calendar);
            break;
        case 2:
            userEditEvent(calendar);
            break;
        case 3:
            printEventQueue(eventQueueEnqueueEventsForThisMonth(NULL));
            break;
        case 4:
            printEvent(stdout, userSearchEvent(calendar));
            break;
            
        default:
            wrongInput();
            return getMainMenuOptions(calendar);
            break;
    }
    
    return 1;
}
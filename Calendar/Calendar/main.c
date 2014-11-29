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
    
    //testing();
    
    Calendar *main = importCalendarFromMainDirectory(NULL);
    main = updateCalendar(main);
 
    do
    {
        resetScreen();
        
        printMainMenu();
        
        printf("\n\nEventos Agendados para esta Semana:\n");
        PriorityQueue *queue = enqueuePriorityQueueEventsForThisWeek(NULL);
        printEventsTitleOfObjectPriorityQueue(&queue);
        
        exportEvents(main);
    } while (getMainMenuOptions(main));
    
    exportEvents(main);
    
    return 0;
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
            resetScreen();
            printEventQueue(eventQueueEnqueueEventsForThisMonth(NULL));
            enterToContinue();
            break;
        case 4:
            printEvent(stdout, userSearchEvent(calendar));
            enterToContinue();
            break;
            
        default:
            wrongInput();
            return getMainMenuOptions(calendar);
            break;
    }
    
    return 1;
}
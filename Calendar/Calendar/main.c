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
    
    userEditEvent(main);
    
    do
    {
        resetScreen();
        
        printMainMenu();
        
        printf("\n\nEventos Agendados para esta Semana:\n");
        printEventTitlesOfHeapOfEvents(stdout, enqueueEventsForThisWeek(NULL, NULL));
        
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
        case 4:
            //ver eventos agendados para este mes
            break;
            
        default:
            wrongInput();
            return getMainMenuOptions(calendar);
            break;
    }
    
    return 1;
}
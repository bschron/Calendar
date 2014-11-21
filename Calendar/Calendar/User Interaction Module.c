//
//  User Interaction Module.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/10/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "User Interaction Module.h"

void userAddEvent (Calendar *calendar)
{
    if (calendar == NULL)
    {
        return;
    }
    
    Event *new = createEmptyEvent();
    
    resetScreen();
    
    do
    {
        printf("Insira um titulo para o Evento:\n");
        nbgets(new->title, sizeof(new->title)/sizeof(char), stdin);
    } while (sizeOfStr(new->title) == 0);
    
    if (strcmp(new->title, "0") == 0)
    {
        freeEvent(&new);
        return;
    }
    
    do
    {
        printf("Insira uma descricao para o Evento:\n");
        nbgets(new->desc, sizeof(new->desc)/sizeof(char), stdin);
    } while (sizeOfStr(new->desc) == 0);
    
    if (strcmp(new->desc, "0") == 0)
    {
        freeEvent(&new);
        return;
    }
    
    do
    {
        printf("Insira a data formatada para o Evento: (dd/mm/yyyy)\n");
        new->date->day = getNumber();
        new->date->month = getNumber();
        new->date->year = getNumber();
    } while (!validDate(new->date));
    
    printf("Voce deseja tornar este evento recorrente?\n");
    if (get1or0())
    {
        userSetupRecorrentEvent(new);
    }
    
    calendar = insertEvent(calendar, new);
    
    return;
}

void userEditEvent (Calendar *calendar)
{
    if (calendar == NULL)
    {
        return;
    }
    
    int optionNumber = 1;
    int option = 1;
    Event *edit = userSearchEvent(calendar);
    Date *date = createEmptyDate();
    char input[Max*5];

    if (edit == NULL)
    {
        free(date);
        return;
    }
    
    for (optionNumber = 1; option != 0; optionNumber = 1)
    {
        resetScreen();
        printf("Qual das informacoes abaixo voce deseja editar?\n");
        printOption(&optionNumber, "Titulo");
        printOption(&optionNumber, "Descricao");
        printOption(&optionNumber, "Data");
        printOption(&optionNumber, "Remover");
        option = getNumber();
        
        if (option == 0)
        {
            free(date);
            return;
        }
        else if (option>optionNumber)
        {
            wrongInput();
            enterToContinue();
        }
        else
        {
            userEditEventGetInput(option, date, input, sizeof(input)/sizeof(char));
            userEditEventEditEvent(option, date, input, sizeof(input)/sizeof(char), edit, calendar);
        }
    }
    
    free(date);
}

void userEditEventGetInput (int option, Date *date, char *dest, int destLength)
{
    switch (option)
    {
        case 1:
            printf("Novo titulo:");
            nbgets(dest, destLength, stdin);
            break;
        case 2:
            printf("Nova descricao:");
            nbgets(dest, destLength, stdin);
            break;
        case 3:
            printf("Nova data: (dd/mm/yyyy):\n");
            date->day = getNumber();
            date->month = getNumber();
            date->year = getNumber();
            break;
        case 4:
            break;
            
        default:
            break;
    }
    
    if ((option == 1 || option == 2))
    {
        if (sizeOfStr(dest) == 0)
        {
            wrongInput();
            enterToContinue();
            return userEditEventGetInput(option, date, dest, destLength);
        }
    }
    else if (option == 3)
    {
        if (!validDate(date))
        {
            wrongInput();
            enterToContinue();
            return userEditEventGetInput(option, date, dest, destLength);
        }
    }
    
    return;
}

void userEditEventEditEvent (int option, Date *date, char *str, int destLength, Event *event, Calendar *calendar)
{
    switch (option)
    {
        case 1:
            editEvent(event, event->date, str, event->desc);
            break;
        case 2:
            editEvent(event, event->date, event->title, str);
            break;
        case 3:
            editEvent(event, date, event->title, event->desc);
            break;
        case 4:
            calendar = removeEvent(calendar, event);
            confirmSucess();
            break;
            
        default:
            break;
    }
}

Event* userSearchEvent (Calendar *calendar)
{
    if (calendar == NULL)
    {
        return NULL;
    }
    
    int optionNumber = 1;
    SearchingHp *results = NULL;
    
    resetScreen();
    
    printf("Como deseja procurar o evento?\n");
    printOption(&optionNumber, "Por titulo\n");
    printOption(&optionNumber, "Por descricao\n");
    printOption(&optionNumber, "Por data\n");
    printOption(&optionNumber, "Por palavras chaves\n");
    
    int option = getNumber();
    
    switch (option)
    {
        case 0:
            return NULL;
            break;
        case 1:
            results = userSearchEventByTitle(calendar);
            break;
        case 2:
            results = userSearchEventByDesc(calendar);
            break;
        case 3:
            results = userSearchEventByDate(calendar);
            break;
        case 4:
            results = userSearchEventByKeywords(calendar);
            break;
            
        default:
            wrongInput();
            enterToContinue();
            return userSearchEvent(calendar);
            break;
    }
    
    if (results == NULL)
    {
        printf("Nenhum resultado encontrado\n");
        enterToContinue();
        return NULL;
    }
    
    PriorityQueue *orderedResults = createPriorityQueue();
    orderedResults = searchingHpToPriorityQueueOrderedByDate(orderedResults, results);
    free(results);
    PriorityQueue *copy = copyPriorityQueue(NULL, orderedResults);
    int i;
    Event *dequeued = NULL;
    char *output = (char*) malloc(sizeof(char)*Max*2);
    char *weekd = (char*) malloc(sizeof(char)*10);
    
    printf("Qual dos eventos abaixo voce procura?\n");
    
    for (i=0, optionNumber = 1; i<SearchingLimit && orderedResults->length > 0; i++)
    {
        dequeued = dequeuePriorityQueue(orderedResults);
        dayOfWeek(weekd, dequeued->date);
        sprintf(output, "%s  %s-%d/%d/%d", dequeued->title, weekd, dequeued->date->day, dequeued->date->month, dequeued->date->year);
        printOption(&optionNumber, output);
    }
    freePriorityQueue(&orderedResults);
    free(output);
    free(weekd);
    
    printOption(&optionNumber, "Nenhuma das opções");
    
    option = getNumber();
    
    if (option >=optionNumber-1 || option < 0)
    {
        printf("Nao foi possivel achar seu evento, tente outro tipo de busca.");
        enterToContinue();
        freePriorityQueue(&copy);
        return userSearchEvent(calendar);
    }
    
    for (i=0; i!=option; i++)
    {
        dequeued = dequeuePriorityQueue(copy);
    }
    
    freePriorityQueue(&copy);
    return dequeued;
}

SearchingHp* userSearchEventByTitle (Calendar *calendar)
{
    char search[Max];
    printf("pesquisar:\n");
    nbgets(search, sizeof(search)/sizeof(char), stdin);
    
    return enqueueEventsWithSimilarText(NULL, titleSearchTable, search);
}

SearchingHp* userSearchEventByDesc (Calendar *calendar)
{
    char search[Max*5];
    printf("pesquisar:\n");
    nbgets(search, sizeof(search)/sizeof(char), stdin);
    
    return enqueueEventsWithSimilarText(NULL, descriptionSearchTable, search);
}

SearchingHp* userSearchEventByDate (Calendar *calendar)
{
    Date *date = createEmptyDate();
    printf("pesquisar: (dd/mm/yyy)\n");
    date->day = getNumber();
    date->month = getNumber();
    date->year = getNumber();
    SearchingHp *hp = NULL;
    
    if (!validDate(date))
    {
        wrongInput();
        enterToContinue();
        free(date);
        return userSearchEventByDate(calendar);
    }
    
    hp = enqueueEventsWithProvidedDate(NULL, dateSearchTable, date->day, date->month, date->year);
    free(date);
    return hp;
}

SearchingHp* userSearchEventByKeywords (Calendar *calendar)
{
    char search[Max*3];
    printf("pesquisar:\n");
    nbgets(search, sizeof(search)/sizeof(char), stdin);
    
    SearchingHp *result = enqueueEventsWithSimilarText(NULL, titleSearchTable, search);
    result = enqueueEventsWithSimilarText(result, descriptionSearchTable, search);
    
    return result;
}

void userSetupRecorrentEvent (Event *event)
{
    int optionNumber = 1;
    
    resetScreen();
    
    printf("Qual tipo de recorrência você deseja para seu evento?\n");
    printOption(&optionNumber, "Semanal");
    printOption(&optionNumber, "Mensal");
    printOption(&optionNumber, "Anual");
    
    
    switch (getNumber())
    {
        case 0:
            return;
            break;
        case 1:
            userSetupRecorrentEventWeeklyEvent(event);
            break;
        case 2:
            userSetupRecorrentEventMonthlyEvent(event);
            break;
        case 3:
            userSetupRecorrentEventYearlyEvent(event);
            break;
            
        default:
            wrongInput();
            enterToContinue();
            return userSetupRecorrentEvent(event);
            break;
    }
}

void userSetupRecorrentEventWeeklyEvent (Event *event)
{
    int i;
    char output[Max];
    char weekDay[10];
    
    event->frequency = (int*) malloc(sizeof(int)*7);
    
    for (i = 0; i<7; i++)
    {
        event->frequency[i] = 0;
    }
    //get information from user
    do
    {
        resetScreen();
        
        printf("Marque com 1 os dias da semana que voce deseja repetir %s:\n", event->title);
        printf("Selecione 0 para finalizar.\n");
        for (i = 1; i<=7;)
        {
            weekDayIntToStr(weekDay, i-1);
            snprintf(output, sizeof(output)/sizeof(char), "%s-%d", weekDay, event->frequency[i-1]);
            printOption(&i, output);
        }
        
        i = getNumber();
        //finish
        if (i == 0)
        {
            break;
        }
        
        event->frequency[i-1] = !event->frequency[i-1];
    } while (1);
    //apply informations
    event->recurrency = 1;
    
    return;
}

void userSetupRecorrentEventMonthlyEvent (Event *event)
{
    int i;
    char output[3];
    
    event->frequency = (int*) malloc(sizeof(int)*31);
    
    for (i = 0; i<31; i++)
    {
        event->frequency[i] = 0;
    }
    
    while (1)
    {
        resetScreen();
        
        for (i = 1; i<=31;)
        {
            printf("Marque com 1 os dias do mes que voce deseja repetir %s:\n", event->title);
            printf("Alerta: Dependendo do mes, o agendamento dos dias 29 a 31 poderao não ocorrer.\n");
            snprintf(output, sizeof(output)/sizeof(char), "%d", event->frequency[i-1]);
            printOption(&i, output);
        }
        
        i = getNumber();
        //finish
        if (i == 0)
        {
            break;
        }
        
        event->frequency[i-1] = !event->frequency[i-1];
    }
    //apply informations
    event->recurrency = 2;
    
    return;
}

void userSetupRecorrentEventYearlyEvent (Event *event)
{
    event->frequency = (int*) malloc(sizeof(int)*2);
    
    do
    {
        resetScreen();
        printf("Insira a data do ano na qual voce deseja repetir %s: (dd/mm)\n", event->title);
        event->frequency[0] = getNumber();
        event->frequency[1] = getNumber();
    } while (event->frequency[0] < 1 || event->frequency[0] > daysInMonth(event->frequency[1]) || event->frequency[1] < 1 || event->frequency[1] > 12);
    
    //apply informations
    event->recurrency = 3;
    return;
}
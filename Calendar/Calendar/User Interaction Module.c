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
    Event *new = createEmptyEvent();
    
    resetScreen();
    
    do
    {
        printf("Insira um titulo para o Evento:\n");
        nbgets(new->title, sizeof(new->title)/sizeof(char), stdin);
    } while (sizeOfStr(new->title) == 0);
    
    do
    {
        printf("Insira uma descricao para o Evento:\n");
        nbgets(new->desc, sizeof(new->desc)/sizeof(char), stdin);
    } while (sizeOfStr(new->desc) == 0);
    
    do
    {
        printf("Insira a data formatada para o Evento: (dd/mm/yyyy)\n");
        new->date->day = getNumber();
        new->date->month = getNumber();
        new->date->year = getNumber();
    } while (!validDate(new->date));
    
    calendar = insertEvent(calendar, new->date->day, new->date->month, new->date->year, new->desc, new->title);
    
    freeEvent(&new);
    return;
}

void userEditEvent (Calendar *calendar)
{
    int optionNumber = 1;
    Event *edit = createEmptyEvent();
    
    resetScreen();
    
    //search event
}

Event* userSearchEvent (Calendar *calendar)
{
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
    
    SearchingHp *copy = duplicateSearchingHp(results);
    int i;
    Event *dequeued = NULL;
    char output[Max*2];
    
    printf("Qual dos eventos abaixo voce procura?\n");
    
    for (i=0, optionNumber = 1; i<SearchingLimit && results->hpLength > 0; i++)
    {
        dequeued = dequeueSearchingHp(results);
        dayOfWeek(output, dequeued->date);
        sprintf(output, "%s  %s-%d%d%d", dequeued->title, output, dequeued->date->day, dequeued->date->month, dequeued->date->year);
        printOption(&optionNumber, output);
    }
    free(results);
    results = copy;
    
    printOption(&optionNumber, "Nenhuma das opções");
    
    option = getNumber();
    
    if (option >=optionNumber || option < 0)
    {
        printf("Nao foi possivel achar seu evento, tente outro tipo de busca.");
        enterToContinue();
        free(results);
        return userSearchEvent(calendar);
    }
    
    for (i=0; i!=option; i++)
    {
        dequeued = dequeueSearchingHp(results);
    }
    
    free(results);
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
    
    if (!validDate(date))
    {
        wrongInput();
        enterToContinue();
        free(date);
        return userSearchEventByDate(calendar);
    }
    
    return enqueueEventsWithProvidedDate(NULL, dateSearchTable, date->day, date->month, date->year);
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
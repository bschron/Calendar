//
//  Output.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/10/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Output.h"

void printBulletedListLine (FILE *stream, char *str)
{
    if (stream == NULL || str == NULL)
    {
        return;
    }
    
    fprintf(stream, "*%s\n", str);
}

void printEvent (FILE *stream, Event *event)
{
    if (event == NULL)
    {
        return;
    }
    else if (stream == NULL)
    {
        return;
    }
    
    char weekDay[10];
    dayOfWeek(weekDay, event->date);
    
    fprintf(stream, "*%s\n", event->title);
    fprintf(stream, "%s - %d/%d/%d\n", weekDay, event->date->day, event->date->month, event->date->year);
    fprintf(stream, "%s\n\n", event->desc);
    
    return;
}

void printEventTitle (FILE *stream, Event *event)
{
    if (event == NULL)
    {
        return;
    }
    else if (stream == NULL)
    {
        return;
    }
    
    char weekDay[10];
    dayOfWeek(weekDay, event->date);
    
    fprintf(stream, "*%s   -%s\n", event->title, weekDay);
    
    return;
}

void printHeapOfEvents (FILE *stream, SearchingHp *events)
{
    if (stream == NULL || events == NULL)
    {
        return;
    }
    else if (events->hpLength == 0)
    {
        free(events);
        return;
    }
    
    Event *dequeued = dequeueSearchingHp(events);
    
    if (dequeued == NULL)
    {
        return;
    }
    
    printEvent(stream, dequeued);
    
    return printHeapOfEvents(stream, events);
}

void printEventTitlesOfHeapOfEvents (FILE *stream, SearchingHp *events)
{
    if (stream == NULL || events == NULL)
    {
        return;
    }
    else if (events->hpLength == 0)
    {
        free(events);
        return;
    }
    
    Event *dequeued = dequeueSearchingHp(events);
    
    if (dequeued == NULL)
    {
        return;
    }
    
    printEventTitle(stream, dequeued);
    
    return printEventTitlesOfHeapOfEvents(stream, events);
}

void resetScreen (void)
{
    system("clear");
    char day[10];
    Date *date = getDate(NULL);
    dayOfWeek(day, date);
    
    fprintf(stdout, "Calendario Spyridon          %s-%d/%d/%d\n", day, date->day, date->month, date->year);
    fprintf(stdout, "0-Voltar/Cancelar\n");
    
    free(date);
}

void printOption (int *optionNumber, char *str)
{
    printf("%d-%s\n", *optionNumber, str);
    (*optionNumber)++;
}

void enterToContinue (void)
{
    printf("Aperte Enter para continuar:");
    getchar();
}

void wrongInput (void)
{
    printf("\nVoce forneceu uma entrada errada, por favor, tente novamente:\n");
    //enterToContinue();
}

void confirmSucess (void)
{
    printf("Operacao efetuada com sucesso.\n");
    enterToContinue();
}
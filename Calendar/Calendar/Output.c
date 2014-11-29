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
    
    fprintf(stream, "%s*%s%s\n", KBLU, RESET, str);
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
    
    fprintf(stream, "%s*%s%s\n", KBLU, RESET, event->title);
    fprintf(stream, "%s%s%s - %d/%d/%d\n", KBLU, RESET, weekDay, event->date->day, event->date->month, event->date->year);
    fprintf(stream, "%s\n", event->desc);
    
    if (event->recurrency == 1 || event->recurrency == -1)
    {
        fprintf(stream, "Ocorrencias: ");
        if (event->frequency[0] == 1)
        {
            fprintf(stream, "%sD%s-", KBLU, RESET);
        }
        else
        {
            fprintf(stream, "d-");
        }
        if (event->frequency[1] == 1)
        {
            fprintf(stream, "%sS%s-", KBLU, RESET);
        }
        else
        {
            fprintf(stream, "s-");
        }
        if (event->frequency[2] == 1)
        {
            fprintf(stream, "%sT%s-", KBLU, RESET);
        }
        else
        {
            fprintf(stream, "t-");
        }
        if (event->frequency[3] == 1)
        {
            fprintf(stream, "%sQ%s-", KBLU, RESET);
        }
        else
        {
            fprintf(stream, "q-");
        }
        if (event->frequency[4] == 1)
        {
            fprintf(stream, "%sQ%s-", KBLU, RESET);
        }
        else
        {
            fprintf(stream, "q-");
        }
        if (event->frequency[5] == 1)
        {
            fprintf(stream, "%sS%s-", KBLU, RESET);
        }
        else
        {
            fprintf(stream, "s-");
        }
        if (event->frequency[6] == 1)
        {
            fprintf(stream, "%sS%s", KBLU, RESET);
        }
        else
        {
            fprintf(stream, "s");
        }
        fprintf(stream, "\n");
    }
    else if (event->recurrency == 2 || event->recurrency == -2)
    {
        fprintf(stream, "Ocorrencias: ");
        int i;
        int *frequency = event->frequency;
        if (event->recurrency == -2)
        {
            frequency = event->recurrences->frequency;
        }
        
        for (i = 0; i<31; i++)
        {
            if (frequency[i] == 1)
            {
                fprintf(stream, "%s%d%s ", KBLU, i+1, RESET);
            }
        }
        fprintf(stream, "\n");
    }
    
    fprintf(stream, "\n");
    
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
    
    fprintf(stream, "%s*%s%s   -%s%s%s\n", KBLU, RESET, event->title, KMAG, weekDay, RESET);
    
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
        freeSearchingHp(&events);
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
        freeSearchingHp(&events);
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
    
    fprintf(stdout, "%sCalendario Spyridon%s          %s-%d/%d/%d\n%s", KBLU, KCYN, day, date->day, date->month, date->year, RESET);
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
    printf("%sAperte %sEnter%s para continuar:%s", KBLU, KCYN, KBLU, RESET);
    getchar();
}

void wrongInput (void)
{
    printf("\n%sVoce forneceu uma entrada errada, por favor, tente novamente:%s\n", KRED, RESET);
    //enterToContinue();
}

void confirmSucess (void)
{
    printf("%sOperacao efetuada com sucesso.%s\n", KGRN, RESET);
    enterToContinue();
}

void printEventQueue (EventQueue *queue)
{
    if (queue == NULL)
    {
        return;
    }
    else if (queue->queueLength == 0)
    {
        free(queue);
        return;
    }
    
    Event *dequeued = dequeueEventQueue(queue);
    
    if (dequeued == NULL)
    {
        free(queue);
        return;
    }
    
    printEvent(stdout, dequeued);
    
    return printEventQueue(queue);
}

void printEventQueueTitles (EventQueue *queue)
{
    if (queue == NULL)
    {
        return;
    }
    else if (queue->queueLength == 0)
    {
        free(queue);
        return;
    }
    
    Event *dequeued = dequeueEventQueue(queue);
    
    if (dequeued == NULL)
    {
        free(queue);
        return;
    }
    
    printEventTitle(stdout, dequeued);
    
    return printEventQueueTitles(queue);
}

void printEventsTitleOfObjectPriorityQueue (PriorityQueue **queue)
{
    if (queue == NULL)
    {
        return;
    }
    else if (*queue == NULL)
    {
        return;
    }
    else if ((*queue)->length == 0)
    {
        freePriorityQueue(queue);
        return;
    }
    
    Event *current = dequeuePriorityQueue(*queue);
    
    printEventTitle(stdout, current);
    
    return printEventsTitleOfObjectPriorityQueue(queue);
}
//
//  Searching Heap.c
//  Calendar
//
//  Created by Bruno Chroniaris on 11/6/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#include "Searching Heap.h"

int heapParent (int child)
{
    if (child == 0)
    {
        return -1;
    }
    else if (child%2 == 0)
    {
        return (child>>1)-1;
    }
    else
    {
        return child>>1;
    }
}

int heapLeftChild (int parent)
{
    return (parent<<1) +1;
}

int heapRightChild (int parent)
{
    return (parent<<1) +2;
}

SearchingHeap* createEmptyHeap (void)
{
    SearchingHeap *new = (SearchingHeap*) malloc(sizeof(SearchingHeap));
    
    initializeSearchingHeap(new);
    
    return new;
}

void heapfySearchingHeap (SearchingHeap *heap, int parent)
{
    if (parent < 0 || heap == NULL || parent > SearchHeapSize-1)
    {
        return;
    }
    else if (parent != 0)
    {
        int parentParent = heapParent(parent);
        
        if (heap->priority[parent] > heap->priority[parentParent])
        {
            heapfySearchingHeap(heap, parentParent);
        }
    }
    
    int leftChild = heapLeftChild(parent);
    int rightChild = heapRightChild(parent);
    if (heap->heap[leftChild] == NULL)
    {
        leftChild = -1;
    }
    if (heap->heap[rightChild] == NULL)
    {
        rightChild = -1;
    }
    int biggestChild = max(leftChild, rightChild);
    
    if (heap->heap[biggestChild] != NULL && heap->priority[parent] < heap->priority[biggestChild])
    {
        switchSearchingHeapItems(heap, parent, biggestChild);
        heapfySearchingHeap(heap, biggestChild);
        heapfySearchingHeap(heap, parent);
    }
    
    return;
}

void switchSearchingHeapItems (SearchingHeap *heap, int item1, int item2)
{
    int transitionInt;
    Event *transitionEvent;
    
    transitionEvent = heap->heap[item1];
    transitionInt = heap->priority[item1];
    
    heap->heap[item1] = heap->heap[item2];
    heap->priority[item1] = heap->priority[item2];
    
    heap->heap[item2] = transitionEvent;
    heap->priority[item2] = transitionInt;
}

SearchingHeap* enqueueSearchingHeap (SearchingHeap *heap, Event *item)
{
    if (item == NULL)
    {
        return heap;
    }
    else if (heap == NULL)
    {
        return enqueueSearchingHeap(createEmptyHeap(), item);
    }
    
    int i;
    
    for (i = 0; i<SearchHeapSize && item != heap->heap[i] && heap->heap[i] != NULL; i++);
    
    if (item == heap->heap[i])
    {
        (heap->priority[i])++;
        heapfySearchingHeap(heap, i);
    }
    else if (heap->heapLength < SearchHeapSize)
    {
        heap->heap[heap->heapLength-1] = item;
        heap->priority[heap->heapLength-1] = 1;
        heapfySearchingHeap(heap, heap->heapLength-1);
        (heap->heapLength)++;
    }
    
    return heap;
}

void initializeSearchingHeap (SearchingHeap *heap)

{
    int i;
    
    for (i=0; i<SearchHeapSize; i++)
    {
        heap->heap[i] = NULL;
        heap->priority[i] = -1;
    }
    
    heap->heapLength = 0;
}

Event* dequeueSearchingHeap (SearchingHeap *heap)
{
    if (heap == NULL)
    {
        return NULL;
    }
    else if (heap->heapLength <= 0)
    {
        return NULL;
    }
    
    //get first
    Event *dequeued = heap->heap[0];
    
    //replace first with last
    heap->heap[0] = heap->heap[heap->heapLength-1];
    heap->priority[0] = heap->priority[heap->heapLength-1];
    //remove last
    heap->heap[heap->heapLength-1] = NULL;
    heap->priority[heap->heapLength-1] = -1;
    //decrease heap length
    (heap->heapLength)--;
    
    //heapfy
    heapfySearchingHeap(heap, 0);
    
    //return dequeued
    return dequeued;
}
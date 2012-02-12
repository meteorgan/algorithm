#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include"heap.h"
#include<stdio.h>

// maintain the atrributes of heap, if the element at i violates the atrributes.
void max_heapify(Heap* heap, int i);
void iter_max_heapfiy(Heap* heap, int i);

void build_max_heap(Heap*);
void heap_sort(Heap*);

// insert i in heap
void max_heap_insert(Heap* heap, int i);
int max_extract_max(Heap*);

// increase the value at position i
void heap_increase_key(Heap*, int i, int key);

// get the max value of heap
int heap_maximum(Heap*);

#endif

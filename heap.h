/*
 * all the elements store in heap.array. first element at heap.array[0] 
 * for simplicity, all the elements are type of int.  
 */
#ifndef HEAP_H
#define HEAP_H

#define Neg_MAX -1000000
typedef struct
{
	int* array;    // store elements
	int length;    // the number of elements in array
	int heap_size; // the number of elements in heap
}Heap;

// the position of parent of i.
inline int PARENT(int i); 
inline int LEFT(int i); 
inline int RIGHT(int i); 

#endif

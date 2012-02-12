#include"max_heap.h"

// O(lgn)
void max_heapify(Heap* heap, int i)
{
	int largest = i;
	int l = LEFT(i);
	int r = RIGHT(i);
	
	if ((heap->heap_size > l) && (heap->array[l] > heap->array[i]))
		largest = l;
	if ((heap->heap_size > r) && (heap->array[r] > heap->array[largest]))
		largest = r;

	if (largest != i)
	{
		int temp = heap->array[i];
		heap->array[i] = heap->array[largest];
		heap->array[largest] = temp;

		max_heapify(heap, largest);
	}
}

void iter_max_heapify(Heap* heap, int i)
{
	int largest = i;
	int l, r;
	while(1)
	{
		l = LEFT(i);
		r = RIGHT(i);
		if (l >= heap->heap_size)
			break;
		else if (heap->array[l] > heap->array[largest])
			largest = l;
		if (r >= heap->heap_size)
			break;
		else if (heap->array[r] > heap->array[largest])
			largest = r;
		
		if (largest == i)
			break;
		else 
		{
			int temp = heap->array[i];
			heap->array[i] = heap->array[largest];
			heap->array[largest] = temp;

			i = largest;
		}
	}
}

// from heap_size/2 to 0, adjust the heap. O(n)
void build_max_heap(Heap* heap)
{
	int i;
	for (i = heap->heap_size/2; i >= 0; i--)
		max_heapify(heap, i);
}

int heap_maximum(Heap* heap)
{
	return heap->array[0];
}

// use the last element to substitute the max element. O(lgn)
int heap_extract_max(Heap* heap)
{
	if (heap->heap_size < 1)
	{
		printf("heap underflow\n");
		return Neg_MAX;
	}

	int max = heap->array[0];
	heap->heap_size -= 1;
	heap->array[0] = heap->array[heap->heap_size];
	max_heapify(heap, 0);

	return max;
}

// if key > parent(i), exchange their values. O(lgn)
void heap_increase_key(Heap* heap, int i, int key)
{
	if (key < heap->array[i])
	{
		printf("new key is smaller than current key\n");
		return;
	}

	heap->array[i] = key;
	int j = PARENT(i);
	while ((i >= 1) && (heap->array[i] > heap->array[j]))
	{
		int temp = heap->array[i];
		heap->array[i] = heap->array[j];
		heap->array[j] = temp;

		i = j;
		j = PARENT(i);
	}
}

// insert a Neg_MAX at the last position, then increase its value. O(lgn)
void max_heap_insert(Heap* heap, int i)
{
	heap->heap_size += 1;
    int end = heap->heap_size - 1;
	heap->array[end] = Neg_MAX;
	
	heap_increase_key(heap, end, i);
}

// O(nlgn)
void heap_sort(Heap* heap)
{
	build_max_heap(heap);
	int i;
	int size = heap->heap_size;
	for (i = heap->heap_size-1; i >= 1; i--)
	{
		int temp = heap->array[i];
		heap->array[i] = heap->array[0];
		heap->array[0] = temp;

		heap->heap_size -= 1;
		//max_heapify(heap, 0);
		iter_max_heapify(heap, 0);
	}
	heap->heap_size = size;
}

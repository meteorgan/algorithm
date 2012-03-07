#ifndef MSORT_H
#define MSORT_H

void insert_sort(int *arr, int size);

// all the elements in input are between 0 and k. counting sort is stable sort, but in place sort.
// time complexisy, O(n). Obviously, this method only can be used when k is not large.
void counting_sort(int *input, int *output, int size, int k);
// in place counting sort, but not stable
void inplace_counting_sort(int *arr, int size, int k);

// assuming all the elements are d bits, this may contrain its range of application.
// time complexity O(d(n+k)), k is the possible values in one bit.
void radix_sort(int *arr, int size, int d);

typedef struct node 
{
	int value;
	struct node *next;
}List;
void list_insert(List *head, List *node);
void list_join(List *list1, List *list2);
// if the input is i.i.d, the time complexity is O(n). all the elements are betwwen min and max.
void bucket_sort(int *arr, int size, int max, int min);

void exchange(int*, int*);
// this partition scans the elements from one side, when all the elements are equal, the partition is not good.
int partition(int *arr, int start, int end);
// scans the elements from both sides, even all the elements are equal, it can get a good partition.
int partition1(int *arr, int start, int end);
void quick_sort(int *arr, int start, int end);

// randomized_quicksort. on average, this method is better than quick_sort.because it chooses the pivot randomly.
int randomized_partition(int *arr, int start, int end);
void randomized_quicksort(int *arr, int start, int end);

void shell_sort(int *arr, int size);

void merge_sort(int *arr, int start, int end);
#endif

#include"msort.h"
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<limits.h>

void insert_sort(int *array, int size)
{
	int i, j;
	for (i = 1; i < size; i++)
	{
		int temp = array[i];
		for(j = i-1; j >= 0; j--)
		{
			if (array[j] > temp)
				array[j+1] = array[j];
			else
				break;
		}
		array[j+1] = temp;
	}
}

void counting_sort(int *input, int *output, int size, int k)
{
	int *temp = (int*)malloc(sizeof(int)*k);
	int i;

	// calculate how many elements less than or equal to i
	for (i = 0; i < k; i++)
		temp[i] = 0;
	for (i = 0; i < size; i++)
		temp[input[i]] += 1;
	for (i = 1; i < k; i++)
		temp[i] += temp[i-1];
	
	// note: i iters from size-1 to 0, this ensure the sorting is stable.and as there may be equal elements, we shoulddecrease the value of temp
	for (i = size-1; i >= 0; i--)
	{
		int pos = temp[input[i]] - 1;
		output[pos] = input[i];
		temp[input[i]]--;
	}

	free(temp);
}

void inplace_counting_sort(int *arr, int size, int k)
{
	int *temp = (int*)malloc(sizeof(int)*k);
	int *temp1 = (int*)malloc(sizeof(int)*k);
	int *temp2 = (int*)malloc(sizeof(int)*k);
	int i;
	for(i = 0; i < k; i++)
	{
		temp[i] = 0;
		temp1[i] = 0;
		temp2[i] = 0;
	}
	for(i = 0; i < size; i++)
	{
		temp[arr[i]] += 1;
		temp1[arr[i]] += 1;
		temp2[arr[i]] += 1;
	}
	for(i = 1; i < k; i++)
	{
		temp[i] += temp[i-1];
		temp1[i] += temp1[i-1];
	}
	
	// from size-1 to 0, make sure every element is in its right postion.
	int j = size - 1;
	while(j >= 0)
	{
		int value = arr[j];
		// if value in its rightpostion,skip this position; otherwise swap the values in 
		// arr[j] and arr[temp[value]]
		if((j >= temp1[value]-temp2[value])&&(j <= temp1[value]-1))
		{
			if(temp[value] == j+1)
				temp[value]--;
			j--;
		}
		else
		{
			arr[j] = arr[temp[value]-1];
			arr[temp[value]-1] = value;
			temp[value]--;
		}
	}

	free(temp);
	free(temp1);
	free(temp2);
}

void radix_sort(int *arr, int size, int d)
{
	int i, j;
	void stable_sort(int*, int*, int, int);
	int *output = (int*)malloc(sizeof(int)*size);

	for(i = 0; i < d; i++)
	{
		stable_sort(arr, output, size, i);
		for(j = 0; j < size; j++)
			arr[j] = output[j];
	}

	free(output);
}

// modify couting_sort to make it sort by ith bit
void stable_sort(int *input, int *output, int size, int d)
{
	int temp[10] = {0};
	int *ith = (int*)malloc(sizeof(int)*size);
	int i;
	for(i = 0; i < size; i++)
	{
		int j = input[i]/((int)pow(10, d));
		int k = j % 10;
		ith[i] = k;
		temp[k] += 1;
	}
	for(i = 1; i < 10; i++)
		temp[i] += temp[i-1];

	for(i = size-1; i >= 0; i--)
	{
		output[temp[ith[i]]-1] = input[i];
		temp[ith[i]]--;
	}

	free(ith);
}

void bucket_sort(int *arr, int size, int max, int min)
{
	int i;
	int interval = (max - min)/size;
	List *list = (List*)malloc(sizeof(List)*size);
	List *array = (List*)malloc(sizeof(List)*size);
	for(i = 0; i < size; i++)
	{
		list[i].next = NULL;
		array[i].value = arr[i];
		array[i].next = NULL;
	}

	for(i = 0; i < size; i++)
	{
		int k = (array[i].value - min)/interval;
		list_insert(&(list[k]), &(array[i]));		
	}
	for(i = 1; i < size; i++)
	{
		list_join(&(list[0]), &(list[i]));
	}
	List *head = list[0].next;
	for(i = 0; i < size; i++)
	{
		arr[i] = head->value;
		head = head->next;
	}

	free(list);
	free(array);
}

void list_insert(List *head, List *node)
{
	List *p = head->next;
	List *pre_p = head;
	while(p != NULL)
	{
		if(p->value < node->value)
		{
			pre_p = p;
			p = p->next;
		}
		else
			break;
	}
	pre_p->next = node;
	node->next = p;
}

void list_join(List *list1, List *list2)
{
	if(list2 == NULL)
		return;

	List *q = list1;
	if (q != NULL)
	{
		while(q->next != NULL)
			q = q->next;
		q->next = list2->next;
	}
}

void quick_sort(int *arr, int start, int end)
{
	if (start >= end)
		return;
	int middle = partition1(arr, start, end);
	quick_sort(arr, start, middle-1);
	quick_sort(arr, middle+1, end);
}

int partition(int *arr, int start, int end)
{
	int pivot = arr[end];
	int i = start - 1;
	int j = 0;
	for(j = start; j < end; j++)
	{
		if(arr[j] < pivot)
		{
			i++;
			exchange(&arr[i], &arr[j]);
		}
	}
	exchange(&arr[i+1], &arr[end]);
	return i+1;
}

int partition1(int *arr, int start, int end)
{
	int pivot = arr[end];
	int i = start;
	int j = end - 1;
	while(1)
	{
		while((i <= end)&&(arr[i] < pivot))
			i++;
		while((j >= start)&&(arr[j] > pivot))
			j--;
		if(i < j)
			exchange(&arr[i], &arr[j]);
		else
			break;
	}
	exchange(&arr[i], &arr[end]);
	return i;
}

void exchange(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void randomized_quicksort(int *arr, int start, int end)
{
	if(start >= end)
		return;
	int middle = randomized_partition(arr, start, end);
	randomized_quicksort(arr, start, middle-1);
	randomized_quicksort(arr, middle+1, end);
}

int randomized_partition(int *arr, int start, int end)
{
	int pivot = random()/RAND_MAX *(end - start) + start;
	exchange(&arr[pivot], &arr[end]);
	return partition1(arr, start, end);
}

void shell_sort(int *arr, int size)
{
	// generates from Tokuda's sequence.
	int gaps[]= {1187, 525, 233, 103, 46, 20, 9, 4, 1};
	int n = sizeof(gaps)/sizeof(int);
	int i, j, k;
	for(i = 0; i < n; i++)
	{
		int gap = gaps[i];
		for(j = gap; j < size; j+=gap)
		{
			int temp = arr[j];
			for(k = j; k >= gap && arr[k-gap]>temp;k-=gap)
				arr[k] = arr[k-gap];
			arr[k] = temp;
		}
	}
}

void merge_sort(int *arr, int start, int end)
{
	void merge(int*, int, int, int);
	if(start >= end)
		return;

	int middle = (start + end)/2;
	merge_sort(arr, start, middle);
	merge_sort(arr, middle+1, end);
	merge(arr, start, middle, end);
}

void merge(int *arr, int start, int middle, int end)
{
	int size1 = middle - start + 2;
	int size2 = end - middle + 1;
	int *list1 = (int*)malloc(sizeof(int)*size1);
	int *list2 = (int*)malloc(sizeof(int)*size2);
	int i;
	int sentinel = INT_MAX;

	for(i = start; i <= middle; i++)
		list1[i-start] = arr[i];
	list1[i-start] = sentinel;
	for(i = middle+1; i <= end; i++)
		list2[i-middle-1] = arr[i];
	list2[i-middle-1] = sentinel;

	int j = 0, k = 0;
	for(i = start; i <= end; i++)
	{
		if(list1[j] <= list2[k])
		{
			arr[i] = list1[j];
			j++;
		}
		else
		{
			arr[i] = list2[k];
			k++;
		}
	}

	free(list1);
	free(list2);
}



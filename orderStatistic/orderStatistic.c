#include"orderStatistic.h"
#include<stdlib.h>
#include<stdio.h>

void getMaxMin(int *arr, int *a, int size)
{
	int max, min;
	if(size == 1)
		a[0] = a[1] = arr[0];
	if(arr[1] >= arr[0])
	{
		max = arr[1];
		min = arr[0];
	}
	else
	{
		max = arr[0];
		min = arr[1];
	}
	int i = 2, j = 3;
	while(1)
	{
		if(size < i+1)
			break;
		if(size < j+1)
		{
			if(arr[i] < min)
				min = arr[i];
			else if(arr[i] > max)
				max = arr[i];
			break;
		}
		int min1, max1;
		if(arr[i] > arr[j])
		{
			max1 = arr[i];
			min1 = arr[j];
		}
		else
		{
			max1 = arr[j];
			min1 = arr[i];
		}
		if(min1 < min)
			min = min1;
		if(max1 > max)
			max = max1;
		i++;
		j++;
	}	
	a[0] = max;
	a[1] = min;
}


int randomized_select(int *arr, int start, int end, int i)
{
	int randomized_partition(int*, int, int);

	int partition = randomized_partition(arr, start, end);
	int k = partition - start + 1;
	if(k == i)
		return arr[partition];
	else 
	{	
		if(k < i)
			return randomized_select(arr, partition+1, end, i-k);
		else
			return randomized_select(arr, start, partition-1, i);
	}
}

int randomized_partition(int *arr, int start, int end)
{
	void exchange(int*, int*);
	int r = rand()/RAND_MAX *(end - start) + start;
	exchange(&arr[r], &arr[end]);
	int pivot = arr[end];

	int i = start;
	int j = end - 1;
	while(1)
	{
		while((i<end)&&(arr[i]<pivot))
			i++;
		while((j>=start)&&(arr[j]>pivot))
			j--;
		if(i >= j)
			break;
		else
			exchange(&arr[i], &arr[j]);
	}
	exchange(&arr[end], &arr[i]);
	return i;
}

void exchange(int *x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

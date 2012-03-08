#ifndef ORDERSTATISTIC_H
#define ORDERSTATISTIC_H

// get the max and min value from array arr, store the values in a[0], a[1]. 
void getMaxMin(int *arr, int *a, int size);

// use to randomized_parition to get the ith element in arr
int randomized_select(int *arr, int start, int end, int i);

// get the median element in arr in O(n)
int get_median(int *arr);
#endif

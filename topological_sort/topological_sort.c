#include<stdio.h>
#include<stdlib.h>
#include"topological_sort.h"
#include"queue.h"

void topological_sort(headNode *listHead)
{
	int size = graphSize(listHead) + 1;
	int *degree  = (int*)malloc(sizeof(int)*size);
	
	getInDegrees(listHead, degree, size);
	queue *q = init_queue(size);
	int i = 0;
	for(i = 1; i < size; i++)
	{
		if(degree[i] == 0)
			enqueue(q, i);
	}

	while(!isempty(q))
	{
		int current = dequeue(q);
		printf("%d ", current);

		int numbers = outDegree(listHead, current);
		printf("numbers: %d\n", numbers);
		int *neighbours = getAllNeighbours(listHead, current);	
		int j = 0;
		for(j = 0; j < numbers; j++)
		{
			int key = neighbours[j];
			degree[key]--;
			if(degree[key] == 0)
				enqueue(q, key);
		}

		free(neighbours);
	}
	printf("\n");
}


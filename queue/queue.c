#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

static int isfull(queue*);

queue* init_queue(int len)
{
	queue *q = (queue*)malloc(sizeof(queue));
	q->length = len;
	q->head = q->tail = 0;
	q->array = (int*)malloc(sizeof(int)*len);

	return q;
}

int enqueue(queue *q, int x)
{
	if(isfull(q))
	{
		printf("the queue is full, can't enqueue!\n");
		return -1;
	}
	q->array[q->tail] = x;

	q->tail++;
	if(q->tail == q->length)
		q->tail = 0;

	return 0;

}

static int isfull(queue *q)
{
	if(q->head == (q->tail+1)%q->length)
		return 1;
	return 0;
}

int dequeue(queue *q)
{
	if(isempty(q))
	{
		printf("the queue is empty, can't dequeue\n");
		return -1;
	}

	int pos = q->head;
	if(q->head == q->length-1)
		q->head = 0;
	else
		q->head++;

	return q->array[pos];
}

int isempty(queue *q)
{
	if(q->head == q->tail)
		return 1;
	return 0;
}

void printelements(queue *q)
{
	if(isempty(q))
		printf("the queue is empty!");
	else
	{
		int i;
		if(q->tail < q->head)
		{
			for(i = q->head; i < q->length; i++)
				printf("%d ", q->array[i]);
			for(i = 0; i < q->tail; i++)
				printf("%d ", q->array[i]);
			printf("\n");
		}
		else
		{
			for(i = q->head; i < q->tail; i++)
				printf("%d ", q->array[i]);
			printf("\n");
		}
	}
}


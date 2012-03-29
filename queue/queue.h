#ifndef QUEUE
#define QUEUE

typedef struct node
{
	int length;
	int head;
	int tail;
	int *array;
}queue;

//using the length of queue to init queue
queue* init_queue(int length);

//insert one element to the queue, if false, return -1; else, return 0;
int enqueue(queue*, int);

int dequeue(queue*);

int isempty(queue*);

void printelements(queue*);

#endif

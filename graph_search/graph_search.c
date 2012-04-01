#include<stdio.h>
#include<stdlib.h>
#include"graph_search.h"
#include"queue.h"

static void DFS_visit(headNode *listHead, headNode *head, int *visited);

void DFS(headNode *listHead)
{
	int size = graphSize(listHead) + 1;

	int *visited = (int*)malloc(sizeof(int)*(size));
	int i = 0;
	for(i = 0; i < size; i++)
		visited[i] = 0;

	headNode *head = listHead;
	while(head!= NULL)
	{
		if(!visited[head->key])
			DFS_visit(listHead, head, visited);
		head= head->next;
	}
	printf("\n");
}

static void DFS_visit(headNode *listHead, headNode *head, int *visited)
{
	visited[head->key] = 1;
	adjNode *node = head->neighbor;
	while(node != NULL)
	{
		if(!visited[node->key])
		{
			printf("%d -> %d ", head->key, node->key);
				
			headNode *temp = findNode(listHead, node->key);
			if(temp != NULL)
				DFS_visit(listHead, temp, visited);
		}
		node = node->next;
	}
}

void BFS(headNode *listHead)
{
	int size = graphSize(listHead) + 1;
	queue *q  = init_queue(size);
	int *visited = (int*)malloc(sizeof(int)*size);
	int i = 0;
	for(i = 0; i < size; i++)
		visited[i] = 0;

	enqueue(q, listHead->key);
	visited[listHead->key] = 1;
	while(!isempty(q))
	{
		int current = dequeue(q);
		printf("%d ", current);

		headNode *node = findNode(listHead, current);
		adjNode *adj = node->neighbor;
		while(adj != NULL)
		{
			if(!visited[adj->key])
			{
				enqueue(q, adj->key);
				visited[adj->key] = 1;
			}
			adj = adj->next;
		}
	}
}

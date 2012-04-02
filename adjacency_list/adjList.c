#include<stdio.h>
#include<stdlib.h>
#include"adjList.h"

static adjNode *makeAdjNode(int);
static headNode *makeHeadNode(int);

static adjNode* makeAdjNode(int u)
{
	adjNode *unode = (adjNode*)malloc(sizeof(adjNode));
	unode->key = u;
	unode->next = NULL;

	return unode;
}

static headNode* makeHeadNode(int v)
{
	headNode *vnode = (headNode*)malloc(sizeof(headNode));
	vnode->key = v;
	vnode->neighbor = NULL;
	vnode->next = NULL;

	return vnode;
}

headNode* addEdge(headNode *listHead, int v, int u)
{
	adjNode *unode = makeAdjNode(u);
	headNode *head = listHead;

	int hasInsert = 0;
	headNode *last = head;
	while(head != NULL)
	{
		if(head->key == v)
		{
			unode->next = head->neighbor;
			head->neighbor= unode;

			hasInsert = 1;
			break;
		}
		last = head;
		head = head->next;
	}
	if(!hasInsert)
	{
		headNode *vnode = makeHeadNode(v);
	    if(last == NULL)
			listHead = vnode;	
		else
			last->next = vnode;
		vnode->neighbor = unode;
	}

	// if key u not in the list, insert it.
	int isexisted = 0;
	head = listHead;
	last = head;
	while(head != NULL)
	{
		if(head->key == u)
		{
			isexisted = 1;
			break;
		}
		last = head;
		head = head->next;
	}
	if(!isexisted)
	{
		headNode *newNode= makeHeadNode(u);
	    last->next = newNode;	
	}

	return listHead;
}

void removeEdge(headNode *listHead, int v, int u)
{
	while(listHead != NULL)
	{
		if(listHead->key == v)
		{
			adjNode *node = listHead->neighbor;
			
			if(node == NULL)
			{
				printf("error: no edge(v, u)!\n");
				return;
			}

			if(node->key == u)
			{
				listHead->neighbor = node->next;
				free(node);
				return;
			}

			adjNode *last = node;
			while(node != NULL)
			{
				if(node->key == u)
				{
					last->next = node->next;
					free(node);

					return;
				}
				last = node;
				node = node->next;
			}
			printf("error: no edge(v, u)!\n");
		}

		listHead = listHead->next;
	}	
}

int outDegree(headNode *listHead, int v)
{
	int degree= 0;
	while(listHead != NULL)
	{
		if(listHead->key ==  v)
		{
			adjNode *node = listHead->neighbor;
			while(node != NULL)
			{
				degree++;
				node = node->next;
			}
			break;
		}

		listHead = listHead->next;
	}

	return degree;
}

int inDegree(headNode *listHead, int v)
{
	int degree = 0;
	while(listHead != NULL)
	{
		adjNode *node = listHead->neighbor;
		while(node != NULL)
		{
			if(node->key == v)
			{
				degree++;
				break;
			}
			node = node->next;
		}
		listHead = listHead->next;
	}

	return degree;
}

int graphSize(headNode *listHead)
{
	int size = 0;
	for(;listHead != NULL; listHead=listHead->next)
		size++;

	return size;
}

headNode* findNode(headNode *listHead, int key)
{
	while(listHead != NULL)
	{
		if(listHead->key == key)
			return listHead;
		listHead = listHead->next;
	}

	return listHead;
}


int* getAllNeighbours(headNode *list, int key)
{
	headNode *node = findNode(list, key);
	adjNode *adj = node->neighbor;
	int size = outDegree(list, key);
	
	int *neighbours = (int*)malloc(sizeof(int)*size);
	int i = 0;
	while(adj != NULL)
	{
		neighbours[i] = adj->key;
		i++;
		adj = adj->next;
	}	

	return neighbours;
}

void getInDegrees(headNode *list, int *degree, int size)
{
	int i = 0;
	for(i = 0; i < size; i++)
		degree[i] = 0;

	while(list != NULL)
	{
		adjNode *node = list->neighbor;
		while(node != NULL)
		{
			degree[node->key]++;
			node = node->next;
		}
		list = list->next;
	}
}

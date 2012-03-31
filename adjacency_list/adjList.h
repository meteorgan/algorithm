#ifndef ADJLIST_H
#define ADJLIST_H

typedef struct node 
{
	int key;
	struct node *next;
}adjNode;

typedef struct headnode
{
	int key;
	adjNode *neighbor;
	struct headnode *next;
}headNode;

int inDegree(headNode *listHead, int v);

int outDegree(headNode *listHead, int v);

int graphSize(headNode *list);

headNode *findNode(headNode *listHead, int key);

headNode* addEdge(headNode *listHead, int v, int u);

void removeEdge(headNode *listHead, int v, int u);

#endif

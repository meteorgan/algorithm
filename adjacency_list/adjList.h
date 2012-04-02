#ifndef ADJLIST_H
#define ADJLIST_H

typedef struct adjnode 
{
	int key;
	struct adjnode *next;
}adjNode;

typedef struct headnode
{
	int key;
	adjNode *neighbor;
	struct headnode *next;
}headNode;

int graphSize(headNode *list);

int inDegree(headNode *listHead, int v);

int outDegree(headNode *listHead, int v);

// get all the in-degree of the nodes in list, store the results in degree.
// assume that all the kesy are integers.
void getInDegrees(headNode *list, int *degree, int size);

// get all the neighbours of node key.
int* getAllNeighbours(headNode *list, int key);

headNode *findNode(headNode *listHead, int key);

headNode* addEdge(headNode *listHead, int v, int u);

void removeEdge(headNode *listHead, int v, int u);

#endif

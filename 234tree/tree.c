#include<stdio.h>
#include<stdlib.h>
#include"tree.h"

tree_node* make_node(void)
{
	tree_node* node = (tree_node*)malloc(sizeof(tree_node));
	node->keynum = 0;
	node->key[0] = node->key[1] = node->key[2] = 0;
	node->children[0] = node->children[1] = NULL;
	node->children[2] = node->children[3] = NULL;
	node->leaf = 1;

	return node;
}

tree_node* tree_search(tree_node *root, int key)
{
	while(root != NULL)
	{
		int i = 0;
		while((i < root->keynum)&&(root->key[i] < key))
			i++;
		if((i < root->keynum)&&(key == root->key[i]))
			break;
		else
			root = root->children[i];
	}
	return root;
}

void inorder_walk(tree_node *root)
{
	void inorder_walk_r(tree_node*, int);
	int i = 0;
	inorder_walk_r(root, i);
}

void inorder_walk_r(tree_node *root, int i)
{
	if(root != NULL)
	{
		int j = -1; 
		while(++j < root->keynum)
		{
			inorder_walk_r(root->children[j], i+1);
			printf("%d:%d ", i, root->key[j]);
		}
		inorder_walk_r(root->children[j], i+1);
	}
}

//if the ith child of p is full. then split child.
static void split_node(tree_node *p, int i, tree_node *child);

/*
 * insert the key in the leaf of the tree, 
 * in the process of going down, if one node is full
 * then split it.
 */
tree_node* tree_insert(tree_node *root, int key)
{
	void tree_insert_nofull(tree_node*, int);

	if(root->keynum == 3)
	{
		tree_node *p = make_node();
		p->leaf = 0;
		split_node(p, 0, root);
		root = p;
		tree_insert_nofull(p, key);
	}
	else
		tree_insert_nofull(root, key);

	return root;
}


// if the root is leaf, insert key into root directly.
// otherwise, find the proper child to insert the key.
void tree_insert_nofull(tree_node *root, int key)
{
	int i = 0;
	while((i < root->keynum)&&(key > root->key[i]))
		i++;

	if(root->leaf == 1)
	{
		int j;
		for(j = root->keynum; j > i; j--)
			root->key[j] = root->key[j-1];
		root->key[i] = key;	
		root->keynum++;
	}
	else
	{
		if(root->children[i]->keynum == 3)
		{
			split_node(root, i, root->children[i]);
			if(key > root->key[i])
				i++;
		}
		tree_insert_nofull(root->children[i], key);	
	}
}

static void split_node(tree_node *p, int i, tree_node *child)
{
	tree_node *child2 = make_node();
	child2->leaf = child->leaf;
	child2->keynum = 1;
	child2->key[0] = child->key[2];
	child2->children[0] = child->children[2];
	child2->children[1] = child->children[3];
	child2->parent = p;

	child->keynum = 1;
	child->children[2] = child->children[3] = NULL;

	//important: you not only need move the key, but also
	// should move the children associated with the key.
	int j = p->keynum;
	while(j > i)
	{
		p->key[j] = p->key[j-1];
		p->children[j+1] = p->children[j];
		j--;
	}	
	p->key[i] = child->key[1];
	p->keynum++;
	p->children[i] = child;
	p->children[i+1] = child2;
}


static int predecessor(tree_node*, int);
static int successor(tree_node *node, int ith);

//delete key in leaf node. then return the node.
static tree_node* delete_from_leaf(tree_node *leaf, int key);
static tree_node* delete_with_brother(tree_node *node, tree_node *parent, int ith, int direction);
//merge the ith children(node) of parent with its lefe brother(direction=0) or right brother(direction=1)
// return the node after mering.
static tree_node* merge_node(tree_node *node, tree_node *parent, int ith, int direction);

tree_node* tree_delete(tree_node* root, int key)
{
	tree_node *newNode;
	// case a: the key is in a leaf, delete the key directly.
	if(root->leaf == 1)
		newNode = delete_from_leaf(root, key);
	else
	{
		int i = 0;
	    while((i < root->keynum)&&(root->key[i] < key))
			i++;

		//case b: when the key in an internal node, if its left child's or
		// right child's keynum > 1, delete the node's predecessor or successor.
		// otherwise, merge two children.
		if((i < root->keynum)&&(root->key[i] == key))
		{
			if(root->children[i]->keynum > 1)
			{
				int p = predecessor(root, i);
				root->key[i] = p;
				newNode = tree_delete(root->children[i], p);
			}
			else if(root->children[i+1]->keynum > 1)
			{
				int s = successor(root, i+1);
				root->key[i] = s;
				newNode = tree_delete(root->children[i+1], s);
			}
			else
			{
				root = merge_node(root->children[i], root, i, 1);
				newNode = tree_delete(root, key);
			}
		}
		else
		{
			//case c: the key in not in current internal node and the node which the 
			// key is in is the offspring of the ith children of the current node.
			//c1: the ith child has enough keys. call tree_delete() recursively with the child.
			//c2: find the left or right brother who has enough keys, move one key from the parent
			// to the child, and move one key from brother to the parent. if both brothers have no
			// enough keys, merge the child with its one brother.
			if(root->children[i]->keynum > 1)
			{
				newNode = tree_delete(root->children[i], key);
			}
			else
			{
				tree_node *temp;
				if(i == 0)
					temp = delete_with_brother(root->children[0], root, 0, 1);
				else if(i == root->keynum)
					temp = delete_with_brother(root->children[root->keynum], root, root->keynum, 0);
				else
				{
					if(root->children[i-1]->keynum > 1)
						temp  = delete_with_brother(root->children[i], root, i, 0);
					else 
						temp = delete_with_brother(root->children[i], root, i, 1);
				}
				newNode = tree_delete(temp, key);
			}
		}
	}
	
	if(newNode->parent == NULL)
		root = newNode;
	return root;
}

static tree_node* delete_from_leaf(tree_node *leaf, int key)
{
	int num = leaf->keynum;
	int i = 0;
	while((i < num)&&(leaf->key[i] < key))
		i++;
	for(; i < num-1; i++)
	{
		leaf->key[i] = leaf->key[i+1];
	}
	leaf->keynum--;

	return leaf;
}

static tree_node* delete_with_brother(tree_node *node, tree_node *parent, int ith, int direction)
{
	tree_node *brother;
	if(direction == 0)
		brother = parent->children[ith-1];
	else
		brother = parent->children[ith+1];
	if(brother->keynum > 1)
	{
		if(direction == 0)
		{
			int i = node->keynum;
			while(i > 0)
			{
				node->key[i] = node->key[i-1];
				node->children[i+1] = node->children[i];
				i--;	
			}
			node->children[i+1] = node->children[i];
			node->key[0] = parent->key[ith-1];
			node->keynum++;

			int n = brother->keynum - 1;
			parent->key[ith-1] = brother->key[n];
			node->children[0] = brother->children[n+1];
			brother->children[n+1] = NULL;
			brother->keynum--;
		}
		else
		{
			int n = node->keynum;
			node->key[n] = parent->key[ith];
			node->keynum++;
			node->children[n+1] = brother->children[0];

			parent->key[ith] = brother->key[0];
			int i = 0;
			while(i < brother->keynum - 1)
			{
				brother->key[i] = brother->key[i+1];
				brother->children[i] = brother->children[i+1];
				i++;
			}
			brother->children[i] = brother->children[i+1];
			brother->keynum--;
		}
	}
	else
	{
		node = merge_node(node, parent, ith, direction);
	}
	return node;
}

static tree_node* merge_node(tree_node *node, tree_node *parent, int ith, int direction)
{
	tree_node *brother;
	if(direction == 0)
		brother = parent->children[ith-1];
	else
		brother = parent->children[ith+1];

	int num1 = brother->keynum;
	int num2 = node->keynum;

	if(direction == 0)
	{
		brother->key[num1] = parent->key[ith-1];
		brother->keynum++;

		int j = 0;
		for(j = 0; j < num2; j++)
		{
			brother->key[num1+1+j] = node->key[j];
			brother->children[num1+j+1] = node->children[j];
		}		
		brother->children[num1+num2+1] = node->children[num2];
		brother->keynum += node->keynum;
		free(node);

		//notice: this only happens when parent is the root;
		if(parent->keynum == 1)
		{
			brother->parent = NULL;
			free(parent);
		}
		else
		{
			int k = ith - 1;
			for(; k < parent->keynum-1; k++)
			{
				parent->key[k] = parent->key[k+1];
				parent->children[k+1] = parent->children[k+2];
			}
			parent->keynum--;
		}
		return brother;
	}
	else
	{
		node->key[num2] = parent->key[ith];
		brother->keynum++;
		int j = 0;
		for(j = 0; j < num1; j++)
		{
			node->key[num2+1+j] = brother->key[j];
			node->children[num2+j+1] = brother->children[j];
		}
		node->children[num2+num1+1] = brother->children[num1];
		node->keynum += brother->keynum;
		free(brother);
		if(parent->keynum == 1)
		{
			node->parent = NULL;
			free(parent);
		}
		else
		{
			int k = ith;
			for(; k < parent->keynum-1; k++)
			{
				parent->key[k] = parent->key[k+1];
				parent->children[k+1] = parent->children[k+2];
			}
			parent->keynum--;
		}
		return node;
	}
}

static int predecessor(tree_node *node, int ith)
{
	int num = ith;
	while(node->children[num] != NULL)
	{
		node = node->children[num];
		num = node->keynum;
	}
	return node->key[node->keynum-1];
}

static int successor(tree_node *node, int ith)
{
	int num = ith;
	while(node->children[num] != NULL)
	{
		node = node->children[num];
		num = 0;
	}
	return node->key[0];
}

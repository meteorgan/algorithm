#include"bst.h"
#include<stdio.h>

//sort the node by key
void inorder_walk(bst_node *x)
{
	if (x == NULL)
		return;
	inorder_walk(x->left);
	printf(" %d", x->key);
	inorder_walk(x->right);
}

// use stack to do iterative inorder walk
void iterative_inorder_walk(bst_node *x)
{
	int MAX = 100;
	bst_node *stack[MAX];
	int top = -1;

	bst_node *current = x;
	while ((current != NULL)||(top != -1))
	{
		if (current != NULL)
		{
			stack[++top] = current;
			current = current->left;
		}	
		else
		{
			bst_node *top_node = stack[top--];
			printf(" %d", top_node->key);
			current = top_node->right;
		}
	}
}

void preorder_walk(bst_node *x)
{
	if (x == NULL)
		return;
	printf(" %d", x->key);
	preorder_walk(x->left);
	preorder_walk(x->right);
}

void postorder_walk(bst_node *x)
{
	if (x == NULL)
		return;
	postorder_walk(x->left);
	postorder_walk(x->right);
	printf(" %d", x->key);	
}

bst_node* tree_search(bst_node* x, int k)
{
	if ((x == NULL) || (x->key == k))
		return x;
	if (x->key > k)
		tree_search(x->left, k);
	else
		tree_search(x->right, k);
}

bst_node* iterative_tree_search(bst_node *x, int k)
{
	while(1)
	{
		if ((x == NULL)||(x->key == k))
			return x;
		if (x->key > k)
			x = x->left;
		else
			x = x->right;
	}
}

bst_node* tree_minimum(bst_node *x)
{
	if (x == NULL)
		return x;
	while(x->left != NULL)
		x = x->left;
	return x;
}

bst_node* tree_maximum(bst_node *x)
{
	if (x == NULL)
		return x;
	while(x->right != NULL)
		x = x->right;
	return x;
}

// find the predecessor of x. if x has left child, the tree minimum of 
// left child is the goal; or find the nearest parent of x whose righ
// child is x.
bst_node* tree_predecessor(bst_node *x)
{
	if (x->left != NULL)
		return tree_maximum(x->left);
	bst_node *p = x->parent;
	while((p != NULL)&&(x != p->right))
	{
		x = p;
		p = x->parent; 
	}
	return p;
}

// similar to tree_predecessor
bst_node* tree_successor(bst_node *x)
{
	if (x->right != NULL)
		return tree_minimum(x->right);
	bst_node *p = x->parent;
	while((p != NULL)&&(x != p->left))
	{
		x = p;
		p = x->parent;
	}
	return p;
}

bst_node* tree_insert(bst_node *T, bst_node *x)
{
	if (T == NULL)
		return x;
	if (T->key > x->key)
	{
		if (T->left != NULL)
			T->left = tree_insert(T->left, x);
		else
		{
			T->left = x;
			x->parent = T;
		}
	}
	else
	{
		if (T->right != NULL)
			T->right = tree_insert(T->right, x);
		else
		{
			T->right = x;
			x->parent = T;
		}
	}

	return T;
}

bst_node* iterative_tree_insert(bst_node *T, bst_node *x)
{
	bst_node *p = NULL; // parent of T
	bst_node *node = T;
	while(node != NULL)
	{
		p = node;
		if (node->key > x->key)
			node = node->left;
		else
			node = node->right;
	}

	x->parent = p;
	if (p == NULL)
		T = x;
	else
	{
		if (p->key > x->key)
			p->left = x;
		else
			p->right = x;
	}

	return T;
}

bst_node* tree_delete(bst_node **T, bst_node *x)
{
	// get the node to be deleted.if the node has two children, delete its successor, 
	// otherwise, delete the node directly.
	bst_node *delete_node = NULL;
	if ((x->left == NULL)||(x->right == NULL))
		delete_node = x;
	else
		delete_node = tree_successor(x);

	// get the child of delete_node
	bst_node *child = NULL;
	if (delete_node->left != NULL)
		child = delete_node->left;
	else
		child = delete_node->right;

	// delete the node, and link the child to parent of delete_node;
	// if the node is root of T, then make T = child
	if (child != NULL)
		child->parent = delete_node->parent;
	if (delete_node->parent == NULL)
		*T = child;
	else
	{
		if (delete_node->parent->left == delete_node)
			delete_node->parent->left = child;
		else
			delete_node->parent->right = child;
	}

	// if the delete_node is the successor of x,
	// after deleting the node, copy data of delete_node to x.
	if (delete_node != x)
		x->key = delete_node->key;

	return delete_node;
}

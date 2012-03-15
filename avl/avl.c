#include"avl.h"
#include<stdio.h>
#include<stdlib.h>

static avl_node* make_node(int data)
{
	avl_node *node = (avl_node*)malloc(sizeof(avl_node));
	node->key = data;
	node->balance= 0;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;

	return node;
}

void inorder_walk(avl_node *root)
{
	if(root == NULL)
		return;
	inorder_walk(root->left);
	printf("key: %d ", root->key);
	inorder_walk(root->right);
}

void preorder_walk(avl_node *root)
{
	if(root == NULL)
		return;
	printf("key: %d ", root->key);
	preorder_walk(root->left);
	preorder_walk(root->right);
}

avl_node* avl_search(avl_node * node, int key)
{
	while(node != NULL)
	{
		if(node->key == key)
			break;
		if(node->key < key)
			node = node->right;
		else
			node = node->left;
	}	
	return node;
}

avl_node* avl_insert(avl_node *root, int key)
{
	avl_node *t = make_node(key);
	if(root == NULL)
		root = t;
	else
	{
		avl_node *p = root;
		avl_node *child = root;
		// find the postion to insert the key
		while(child != NULL)
		{
			p = child;
			if(child->key > key)
				child = child->left;
			else
				child = child->right;
		}
		if(p->key > key)
			p->left = t; 
		else
			p->right = t;
		t->parent = p;
	}

	// adjust the balance of ancestor
	avl_node *p = t->parent;
	while(p != NULL)
	{
		if(p->left == t)
			p->balance -= 1;
		else
			p->balance += 1;
		if((p->balance > 1)||(p->balance < -1))
		{
			tree_insert_balance(p);
			if(root == p)
				root = root->parent;
			break;
		}
		// if a node is balanced, no need to go up further.
		if(p->balance == 0)
			break;
		t = p;
		p = p->parent;
	}
	return root;
}

avl_node* avl_delete(avl_node *root, int key)
{
	avl_node *node = avl_search(root, key);
	if(node == NULL)
	{
		printf("no such key in tree\n");
		return root;
	}
	avl_node *target = node;
	//if node has two children, delete its successor
	if((target->left != NULL)&&(target->right != NULL))
		target = tree_successor(target);

	avl_node *parent = target->parent;
	avl_node *child = NULL;
	if(target->left == NULL)
		child = target->right;
	else
		child = target->left;
	
	int direction = 0;
	if(child != NULL)
		child->parent = parent;
	if(parent == NULL)
		root = child;
	else
	{
		if(parent->left == target)
		{
			parent->left = child;
			direction = 0;
		}
		else
		{
			parent->right = child;
			direction = 1;
		}
	}
	// if target is node's succesor, after delete target, copy the data from 
	// target to node.
	if(target != node)
		node->key = target->key;

	free(target);

	//balance the tree after delete
	while(parent != NULL)
	{
		// you can't use child == parent->left to judge this,
		// because child may be null, parent has no child.
		if(direction == 0)   
		{
			parent->balance += 1;
		}
		else
		{
			parent->balance -= 1;
		}

		if((parent->balance == 1)||(parent->balance == -1))
			break;
		//attention: a deletion maybe require rebalancing all the way
		// back up the tree.
		if((parent->balance ==2)||(parent->balance == -2))
		{
			tree_delete_balance(parent);
			if(parent == root)
				root = parent->parent;
			parent = parent->parent; //after balance, the current parent should change.
		}

		child = parent;
		parent = parent->parent;
		if(parent != NULL)
			direction = child == parent->left? 0:1;
	}

	return root;
}

/*
 * if the balance of the node is greater than 1 or less than -1, 
 * then balance the tree. 
 * case 1. a: node->balance >= 2, b: node->right->balance > 0;
 *         left_rotation the node. a->balance = b->balance.
 * case 2. a: node->balance >=2, b: node->right->balance < 0, c: node->right->left->balance ==0;
 *         right_left_rotation the node. a->balance = b->balance = c->balance = 0.
 * case 3. a: node->balance >= 2, b: node->right->balance < 0, c: node->right->left->balance > 0; 
 *         right_left_roation the node. a->balance = -1, b->balance = 0, c->balance = 0;
 * case 4. a: node->balance >= 2, b: node->right->balance < 0, c: node->right->left->balance < 0;
 *         right_left_rotation the node. a->balance = 0, b->balance = 1, c->balance = 0;
 * case 5 - 8 is symmetrical to case 1-4. 
 */
static void tree_insert_balance(avl_node *node)
{
	if(node->balance > 0)
	{
		avl_node *child = node->right;
		if(child->balance > 0)
		{
			node->balance = child->balance = 0;
			left_rotation(node);
		}
		else
		{
			avl_node *left_child = child->left;
			if(left_child->balance == 0)
				node->balance = child->balance = 0;
			else if(left_child->balance > 0)
			{
				node->balance = -1;
				child->balance = 0;
			}
			else
			{
				node->balance = 0;
				child->balance = 1;
			}
			left_child->balance = 0;
			right_left_rotation(node);
		}
	}
	else
	{
		avl_node *child = node->left;
		if(child->balance < 0)
		{
			node->balance = child->balance = 0;
			right_rotation(node);
		}
		else
		{
			avl_node *right_child= child->right;
			if(right_child->balance == 0)
			{
				node->balance = child->balance = 0;
			}
			else if(right_child->balance > 0)
			{
				node->balance = 0;
				child->balance = -1;
			}
			else
			{
				node->balance = 1;
				child->balance = 0;
			}
			right_child->balance = 0;
			left_right_rotation(node);
		}
	}
}

// tree_delete_balance has 2 more case than tree_insert_balance.
// these are: a: node->balance > 0, b: node->right-balance = 0;
// the other case is sysmetrical to this case.
static void tree_delete_balance(avl_node* node)
{
	if(node->balance > 0)
	{
		avl_node *child = node->right;
		if(child->balance == 0)
		{
			node->balance = 1;
			child->balance = -1;
			left_rotation(node);
		}
		else
			tree_insert_balance(node);
	}
	else if(node->balance < 0)
	{
		avl_node *child = node->left;
		if(child->balance == 0)
		{
			node->balance = 1;
			child->balance = -1;
			right_rotation(node);
		}
		else
			tree_insert_balance(node);
	}
}

static void left_rotation(avl_node *node)
{
	avl_node *parent = node->parent;
	avl_node *right_node = node->right;

	right_node->parent = parent;
	if(parent != NULL)
	{
		if(node == parent->left)
			parent->left = right_node;
		else
			parent->right = right_node;
	}
	
	node->right = right_node->left;
	if(node->right != NULL) 
		node->right->parent = node;
	right_node->left = node;
	node->parent = right_node;
}

static void right_rotation(avl_node *node)
{
	avl_node *parent = node->parent;
	avl_node *left_node = node->left;

	left_node->parent = parent;
	if(parent != NULL)
	{
		if(node == parent->left)
			parent->left = left_node;
		else
			parent->right = left_node; 
	}

	node->left = left_node->right;	
	if(node->left != NULL)
		node->left->parent = node;
	left_node->right = node;
	node->parent = left_node;
}

static void left_right_rotation(avl_node *node)
{
	avl_node *left_node = node->left;
	
	left_rotation(left_node);
	right_rotation(node);
}

static void right_left_rotation(avl_node *node)
{
	avl_node *right_node = node->right;

	right_rotation(right_node);
	left_rotation(node);
}

static avl_node* tree_successor(avl_node *node)
{
	if(node->right != NULL)
	{
		avl_node *right = node->right;
		avl_node* left_child = right->left;
		while(left_child != NULL)
		{
			right = left_child;
			left_child = left_child->left;
		}
		return right;
	}
	else
	{
		avl_node *p = node->parent;
		while(p != NULL)
		{
			if(p->left == node)
				break;
			node = p;
			p = p->parent;
		}
		return p;
	}
}

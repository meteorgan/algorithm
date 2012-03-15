#ifndef AVL_H
#define AVL_H

typedef struct node
{
	int key;
	int balance;  // heigt(right)-height(left)
	struct node *left;
	struct node *right;
	struct node* parent;
}avl_node;

// if the key is not in the tree, return NULL, otherwise, return the node found.
avl_node* avl_search(avl_node *node, int key);
// return the root of tree
avl_node* avl_insert(avl_node *root, int key);
// return the root of tree
avl_node* avl_delete(avl_node *root, int key);
void inorder_walk(avl_node*);
void preorder_walk(avl_node*);

static avl_node* make_node(int data);

static avl_node* tree_successor(avl_node*);
static void tree_insert_balance(avl_node*);
static void tree_delete_balance(avl_node*);
static void left_rotation(avl_node*);
static void right_rotation(avl_node*);
static void left_right_rotation(avl_node*);
static void right_left_rotation(avl_node*);
#endif

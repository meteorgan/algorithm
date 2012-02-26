#ifndef BST_H
#define BST_H

typedef struct bst
{
	int key;
	struct bst *left;
	struct bst *right;
	struct bst *parent;
}bst_node;

void inorder_walk(bst_node *x);
void iterative_inorder_walk(bst_node *x);
void preorder_walk(bst_node *x);
void postorder_walk(bst_node *x);

bst_node* tree_search(bst_node *x, int k);
bst_node* iterative_tree_search(bst_node *x, int k);

bst_node* tree_minimum(bst_node *x);
bst_node* tree_maximum(bst_node *x);

bst_node* tree_predecessor(bst_node *x);
bst_node* tree_successor(bst_node *x);

bst_node* tree_insert(bst_node *T, bst_node *x);
bst_node* iterative_tree_insert(bst_node *T, bst_node *x);
bst_node* tree_delete(bst_node **T, bst_node *x);
#endif

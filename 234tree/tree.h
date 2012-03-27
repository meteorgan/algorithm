#ifndef TREE_H
#define TREE_H

typedef struct node
{
	int key[3];
	struct node *children[4];
	struct node *parent;
	int leaf;
	int keynum;   // the number of keys
}tree_node;

tree_node* make_node(void);
void inorder_walk(tree_node *root);

tree_node* tree_search(tree_node *root, int key);
tree_node* tree_insert(tree_node *root, int key);
tree_node* tree_delete(tree_node *root, int key);

#endif

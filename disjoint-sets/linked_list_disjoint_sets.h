#ifndef LINKED_LIST_DISJOINT_SET_H
#define LINKED_LIST_DISJOINT_SET_H

/*
 * use linked list to implement disjoint sets.
 */

typedef struct node{
	int value;
	struct node* next;
	struct node* head;   // point to the set
}set_node;

typedef struct set{
	int length;
	set_node* head;  //point to the first node of the list.
	set_node* tail; // point to the last node of the list.
}Set;

// create a new set whose only member is x. returns the representation of the set.
Set* make_set(int);

//unites the dynamic sets that contain x and y, say Sx and Sy into a new set 
//that is the union of these two sets. returns the representation of the set.
Set* union_set(int, int);

//returns a pointer to the representation of the set containing x.
Set* find_set(int);
#endif

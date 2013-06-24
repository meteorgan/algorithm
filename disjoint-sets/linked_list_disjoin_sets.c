#include"linked_list_disjoint_sets.h"

Set* make_set(set_node* x) 
{
	Set* set = (Set*)malloc(sizeof(Set));

	set->head = set->tail = node;
	set->length = 1;
	node->head = set;

	return set;
}

Set* union_set(set_node* x, set_node* y)
{
	Set* set_x = find_set(x);
	Set* set_y = find_set(y);

	if(set_x == set_y)
		return set_x;
	if(set_x->length > set_y->length)
	{
		set_x->tail = set_y->tail;
		
		set_node* heady = NULL;
		for(head_y = set_y->head; head_y != set_y->tail; head_y=head_y->next)
			head_y->head = set_x;
		set_y->tail->head = set_x;
		free(set_y);

		return set_x;
	}
	else 
	{
		set_y->tail = set_x->tail;

		set_node* head_x;
		for(head_x=set_x->head; head_x!=set_x->tail; head_x=head_x->next)
			head_x->head  = set_y;
		set_x->tail->head = set_y;
		free(set_x);

		return set_y;
	}
}

Set* find_set(set_node* x)
{
	return x->head;
}

static set_node* make_set_node(int x)
{
	set_node* node = (set_node*)malloc(sizeof(set_node));
	node->value = x;
	node->next = node->head = NULL;

	return node;
}

#include "clist.h"

void init_list(struct i_list * list) {
	list->head = NULL;
	return;
};

void add_node(struct i_list * list, struct i_node * node) {
	if (list->head == NULL) {
		list->head = node;
		node->next = node->prev = NULL;
	} else {
		list->head->prev = node;
		node->next = list->head;
		list->head = node;
		list->head->prev = NULL;
	}
	return;
};

void remove_node(struct i_list * list, struct i_node * node) {
	if (node->prev != NULL) 
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (list->head == node)
		list->head = node->next;
	//free(node);
	return;
};

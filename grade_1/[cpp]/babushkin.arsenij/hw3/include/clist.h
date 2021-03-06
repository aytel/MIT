#ifndef CLIST
#define CLIST
#include <stddef.h>
#include <stdio.h>

struct i_node {
  struct i_node * next, * prev;
};

struct i_list {
  struct i_node * head;
};

void init_list(struct i_list * list);
void add_node(struct i_list * list, struct i_node * node);
void remove_node(struct i_list * list, struct i_node * node);
int get_length(struct i_list * list);

#endif

#ifndef CLIST
#define CLIST
#include <stddef.h>

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

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

void apply(struct i_node * l, void (*op)(struct i_node * node, void * arg), void * arg);

#endif

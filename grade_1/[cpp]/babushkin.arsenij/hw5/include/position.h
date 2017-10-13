#ifndef POSITION
#define POSITION
#include <stdio.h>
#include <stdlib.h>
#include <clist.h>

struct p_node {
  int x, y;
  struct i_node node;
};

void remove_position(struct i_list *list, int x, int y);

void add_position(struct i_list *list, int x, int y);

void show_all_positions(struct i_list *list, FILE * w, int mode);

void remove_all_positions(struct i_list *list);

void show_len(struct i_list *list);

#endif

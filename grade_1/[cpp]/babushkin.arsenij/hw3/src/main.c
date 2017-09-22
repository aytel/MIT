#include "clist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define container_of(ptr, p_node, node) (p_node*)((char*)(ptr) - offsetof(p_node, node))

struct p_node {
  int x, y;
  struct i_node node;
};

void remove_position(struct i_list * list, int x, int y) {
	struct i_node * cur = list->head;
	while (cur != NULL) {
		struct p_node * item = container_of(cur, struct p_node, node);
		if (item->x == x && item->y == y) {
			struct i_node * next = cur->next;
			remove_node(list, cur);
			free(item);
			cur = next;
		} else
			cur = cur->next;
	}
	return;
}

void add_position(struct i_list * list, int x, int y) {
	struct p_node * cur = malloc(sizeof(struct p_node));
	cur->x = x, cur->y = y;
	add_node(list, &cur->node);
	return;
}

void show_all_positions(struct i_list * list) {
	struct i_node * cur = list->head;
	while (cur != NULL) {	
		struct p_node * item = container_of(cur, struct p_node, node);
		printf("(%d %d) ", item->x, item->y);
		printf("\n");
		cur = cur->next;
	}
	return;
}

void remove_all_positions(struct i_list * list) {
	while (list->head != NULL) {
		struct p_node * item = container_of(list->head, struct p_node, node);
		remove_node(list, list->head);
		free(item);
	}
	return;
}

void show_len(struct i_list * list) {
	int cn = 0;
	struct i_node * cur = list->head;
	while (cur != NULL) {
		cn++;
		cur = cur->next;
	}
	printf("%d\n", cn);
	return;
}

int main() {
	struct i_list l;
	init_list(&l);

	/*add_position(&l, 1, 2);
	add_position(&l, 3, 6);
	show_all_positions(&l);
	remove_position(&l, 1, 2);
	show_all_positions(&l);
	return 0;*/

	char * s = (char *)(malloc(sizeof(char *)));
	while (1) {
		scanf("%s", s);
		//printf("%s ", s);
		if (!strcmp(s, "add")) {
			int x, y;
			scanf("%d%d", &x, &y);
			add_position(&l, x, y);
			continue;
		}
		if (!strcmp(s, "rm")) {
			int x, y;
			scanf("%d%d", &x, &y);
			remove_position(&l, x, y);
			continue;
		}
		if (!strcmp(s, "print")) {
			show_all_positions(&l);
			continue;
		}
		if (!strcmp(s, "rma")) {
			remove_all_positions(&l);
			continue;
		}
		if (!strcmp(s, "len")) {
			show_len(&l);
			continue;
		}
		if (!strcmp(s, "exit")) {
			remove_all_positions(&l);
			//free(&l);
			free(s);
			return 0;
		}
		printf("Unknown command\n");
	}
	return 0;
}

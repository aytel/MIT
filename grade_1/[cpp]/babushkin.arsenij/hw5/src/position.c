#include "clist.h"
#include "position.h"

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

void show_all_positions(struct i_list * list, FILE * w, int mode) {
	struct i_node * cur = list->head;
	if (cur == NULL)
		return;
	while (cur->next != NULL)
		cur = cur->next;
	while (cur != NULL) {	
		struct p_node * item = container_of(cur, struct p_node, node);
		if (!mode)
			fprintf(w, "%d %d\n", item->x, item->y);
		else {
			int x = item->x, y = item->y;
			for (int i = 0; i < 3; i++) {
				fputc(x - ((x >> 8) << 8), w);
				x >>= 8;
			}
			for (int i = 0; i < 3; i++) {
				fputc(y - ((y >> 8) << 8), w);
				y >>= 8;
			}
		}
		cur = cur->prev;
	}
	printf("\n");
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
	printf("%d\n", get_length(list));
	return;
}

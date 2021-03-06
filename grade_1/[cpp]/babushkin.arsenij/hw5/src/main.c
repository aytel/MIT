#include "position.h"
#include "clist.h"
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

void read_text(struct i_list * l, char * in) {
	FILE * r = fopen(in, "r");
	int x, y;
	while (fscanf(r, "%d %d", &x, &y) != EOF)
		add_position(l, x, y);
	fclose(r);
}

void read_bin(struct i_list * l, char * in) {
	FILE * r = fopen(in, "r");
	int x1, x2, x3, y1, y2, y3;
	while ((x1 = fgetc(r)) != EOF) {
		x2 = fgetc(r), x3 = fgetc(r);
		y1 = fgetc(r), y2 = fgetc(r), y3 = fgetc(r);
		int x = (x3 << 16) + (x2 << 8) + x1;
		int y = (y3 << 16) + (y2 << 8) + y1;
		add_position(l, x, y);
	}
	fclose(r);
}

void print_text(struct i_list * l, char * out) {
	FILE * w = fopen(out, "w");
	show_all_positions(l, w, 0);
	fclose(w);
}

void print_bin(struct i_list * l, char * out) {
	FILE * w = fopen(out, "w");
	show_all_positions(l, w, 1);
	fclose(w);
}

void print(struct i_list * l, char * frm) {
	void op(struct i_node * node, void * arg) {
		struct p_node * item = container_of(node, struct p_node, node);
		printf((char *)arg, item->x, item->y);
	};
	apply(l->head, op, (void *)frm);
}

void count(struct i_list * l) {
	int cn = 0;
	void op(struct i_node * node, void * arg) {
		(*(int *)arg)++;
	}
	apply(l->head, op, (void *)&cn);
	printf("%d\n", cn);
}

int main(int argc, char **argv) {

	struct i_list l;
	init_list(&l);

	if (!strcmp(argv[1], "loadtext"))
		read_text(&l, argv[2]);
	if (!strcmp(argv[1], "loadbin"))
		read_bin(&l, argv[2]);

	if (!strcmp(argv[3], "savetext"))
		print_text(&l, argv[4]);
	if (!strcmp(argv[3], "savebin"))
		print_bin(&l, argv[4]);
	if (!strcmp(argv[3], "print"))
		print(&l, argv[4]);
	if (!strcmp(argv[3], "count"))
		count(&l);

	remove_all_positions(&l);

	return 0;
}

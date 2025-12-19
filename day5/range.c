#include <stdlib.h>
#include "range.h"

int range_contains(range *r, long long val) {
	if (val >= r->start && val <= r->end) 
		return 1;
	return 0;
}

range_list* rl_create(void) {
	range_list *list = malloc(sizeof(range_list));
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void rl_insert(range_list *list, long long start, long long end) {
	struct range_list_node_ *new = malloc(sizeof(struct range_list_node_));
	new->next = NULL;
	new->r.start = start;
	new->r.end = end;

	if (list->head == NULL) {	
		list->head = new;
		list->tail = new;
	} else {
		list->tail->next = new;
		list->tail = new;
	}
}

int rl_contains(range_list *list, long long val) {
	for (struct range_list_node_ *current = list->head; current != NULL; current = current->next) {
		if (range_contains(&(current->r), val))
			return 1;
	}
	return 0;
}

void rl_destroy(range_list **list_p) {
	struct range_list_node_ *current = (*list_p)->head;
	while (current != NULL) {
		struct range_list_node_ *next = current->next;
		free(current);
		current = next;
	}
	free(*list_p);
	*list_p = NULL;
}

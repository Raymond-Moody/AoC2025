#include <stdlib.h>
#include "range.h"

int range_contains(range *r, long long val) {
	if (val >= r->start && val <= r->end)
		return 1;
	return 0;
}

int range_overlaps(range *a, range *b) {
	if (a == NULL || b == NULL)
		return 0;

	if (
		range_contains(a, b->start) ||
		range_contains(a, b->end) ||
		range_contains(b, a->start) ||
		range_contains(b, a->end))
	{
		return 1;
	}

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
	new->prev = NULL;
	new->r.start = start;
	new->r.end = end;

	if (list->head == NULL) {
		list->head = new;
		list->tail = new;
		return;
	}

	for (
		 struct range_list_node_ *current = list->head;
		 current != NULL;
		 current = current->next)
	{
		if (range_overlaps(&(current->r), &(new->r))) {
			if (new->r.start < current->r.start)
				current->r.start = new->r.start;
			if (new->r.end > current->r.end)
				current->r.end = new->r.end;
			free(new);

			while (
				   current->next != NULL &&
				   range_overlaps(&(current->r), &(current->next->r)))
			{
				struct range_list_node_ *temp = current->next;
				if (temp->r.end > current->r.end)
					current->r.end = temp->r.end;
				current->next = temp->next;
				if (temp == list->tail)
					list->tail = current;
				else
					temp->next->prev = current;
				free(temp);
			}

			return;
		}
		else if (new->r.start < current->r.start) {
			if (current == list->head)
				list->head = new;
			else
				current->prev->next = new;
			new->next = current;
			new->prev = current->prev;
			current->prev = new;
			return;
		}
	}

	list->tail->next = new;
	new->prev = list->tail;
	list->tail = new;
}

int rl_contains(range_list *list, long long val) {
	for (
		 struct range_list_node_ *current = list->head;
		 current != NULL;
		 current = current->next)
	{
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

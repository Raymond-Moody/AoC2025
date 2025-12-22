#ifndef RANGE_H_
#define RANGE_H_

typedef struct range_ range;
typedef struct range_list_ range_list;

struct range_ {
	long long start, end;
};

int range_contains(range*, long long);
int range_overlaps(range*, range*);

struct range_list_node_ {
	struct range_list_node_ *next;
	struct range_list_node_ *prev;
	range r;
};

struct range_list_ {
	struct range_list_node_ *head;
	struct range_list_node_ *tail;
};

range_list* rl_create(void);

void rl_insert(range_list*, long long, long long);

int rl_contains(range_list*, long long);

void rl_destroy(range_list**);

#endif /* RANGE_H_ */

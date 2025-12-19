#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "range.h"

int countFresh(char *filename){
	int count = 0;
	char buffer[64];
	
	FILE *input = fopen(filename, "r");
	if (input == NULL) {
		printf("Failed to open file %s.\n", filename);
		return 0;
	}

	range_list *ranges = rl_create();
	while (fgets(buffer, sizeof(buffer), input) != NULL) {
		if (buffer[0] == '\n')
			break;
		char *start_str = strtok(buffer, "-");
		long long start = atoll(start_str);
		char *end_str = strtok(NULL, "-");
		long long end = atoll(end_str);

		rl_insert(ranges, start, end);
	}

	while (fgets(buffer, sizeof(buffer), input) != NULL) {
		long long id = atoll(buffer);
		if (rl_contains(ranges, id))
			count++;
	}
	rl_destroy(&ranges);
	return count;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		puts("Please provide a filename");
		return 1;
	}

	int fresh = countFresh(argv[1]);
	printf("There are %d fresh ingredients.\n", fresh);
	return 0;
}

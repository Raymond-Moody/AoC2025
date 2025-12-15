#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* readFile(char* filename){
	FILE *in = fopen(filename, "r");
	if (in == NULL) {
		printf("Failed to open file %s.\n", filename);
		return NULL;
	}
	
	size_t content_size = 0;
	size_t last = 0;
	size_t len = 0;
	char *content = NULL;
	
	do {
		content_size += BUFSIZ;
		content = realloc(content, content_size);
		if (content == NULL) {
			puts("Failed to allocate memory for input.\n");
			exit(1);
		}
		fgets(content+last, content_size, in);
		len = strlen(content);
		last = len - 1;
	} while (!feof(in));
	
	fclose(in);
	return content;
}

long long sumRepeated(long long start, long long end) {
	//	printf("Checking %lld-%lld\n", start, end);

	long long sum = 0;
	char current_str[16];
	size_t len;
    for (long long current = start; current <= end; ++current) {
		sprintf(current_str, "%lld", current);
		len = strlen(current_str);
		if (len & 1)
			continue;

		bool invalid = true;
		for (size_t i = 0; i < len / 2; ++i) {
			if (current_str[i] != current_str[i + len / 2]) {
				invalid = false;
				break;
			}
		}
		
		if (invalid) {
			// printf("\t%lld was invalid.\n", current);
			sum += current;
		}
	}
	
	return sum;
}

long long sumPatterns(long long start, long long end) {
	//	printf("Checking %lld-%lld\n", start, end);

	long long sum = 0;
	char current_str[16];
	size_t len;
    for (long long current = start; current <= end; ++current) {
		sprintf(current_str, "%lld", current);
		len = strlen(current_str);

		for (size_t pattern_size = 1; pattern_size <= len / 2; ++pattern_size) {
			bool invalid = true;
			for (size_t i = 0; i < pattern_size; ++i) {
				char expected = current_str[i];
				for (size_t check = i; check < len; check += pattern_size) {
					if (
						current_str[check] != expected ||
						(i != pattern_size - 1 && check == len - 1)
					) {
						invalid = false;
						break;
					}
				}
				
				if (!invalid) {
					break;
				}
			}
			
			if (invalid) {
				// printf("\t%lld was invalid. Pattern size: %ld\n", current, pattern_size);
				sum += current;
				break;
			}
		}
	}
	
	return sum;	
}

long long partOne(char *filename) {
	long long res = 0;
	char *input = readFile(filename);
	if (input == NULL) {
		puts("Failed to read input.");
		return 0;
	}

	char *match = strtok(input, "-");
	while (match != NULL) {
		long long start = atoll(match);
		match = strtok(NULL, ",");
		long long end = atoll(match);
		match = strtok(NULL, "-");
		res += sumRepeated(start, end);
	}
		
	return res;
}

long long partTwo(char *filename) {
	long long res = 0;
	char *input = readFile(filename);
	if (input == NULL) {
		puts("Failed to read input.");
		return 0;
	}
	
	char *match = strtok(input, "-");
	while (match != NULL) {
		long long start = atoll(match);
		match = strtok(NULL, ",");
		long long end = atoll(match);
		match = strtok(NULL, "-");
		res += sumPatterns(start, end);
	}
		
	return res;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		puts("Please provide a file name.");
		return 1;
	}
	
	long long p1 = partOne(argv[1]);
	long long p2 = partTwo(argv[1]);
	printf("Part 1 Result: %20lld\n", p1);
	printf("Part 2 Result: %20lld\n", p2);
	return 0;
}

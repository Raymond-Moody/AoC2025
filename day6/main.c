#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv){
	long long problems[1000][5];
	char operators[1000];
	char buffer[4000];
	int problem_count = 0;
	int operands = 0;

	if (argc < 2)
		puts("Please provide a filename.");

	FILE *input = fopen(argv[1], "r");
	if (input == NULL) {
		printf("Failed to open file %s.\n", argv[1]);
		return 1;
	}
	
	while (fgets(buffer, sizeof(buffer), input) != NULL) {
		char *val_str = strtok(buffer, " ");
		while (val_str != NULL) {
			if (isdigit(val_str[0])) {
				long long val = atoll(val_str);
				problems[][] = val;
			}
			else {
				operators[] = val_str[0];
			}
		}
	}
	fclose(input);

	
	return 0;
}

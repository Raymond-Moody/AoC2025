#include <stdio.h>
#include <stdlib.h>

void generateLayout(char *filename, char **result, int *result_size) {
	FILE *input = fopen(filename, "r");
	if (input == NULL) {
		printf("Could not open '%s'\n", filename);
		return;
	}
	
	char buffer[256];
	int row = 0;

	*result_size = 0;
	if (fgets(buffer, sizeof(buffer), input) != NULL) {
		for (int i = 0; i < sizeof(buffer) && buffer[i] != '\n'; ++i)
			*result_size += 1;
	}
	fseek(input, 0, SEEK_SET);
	*result = malloc(*result_size * *result_size);

	while (fgets(buffer, sizeof(buffer), input) != NULL) {
		for (int i = 0; i < *result_size; ++i) {
			char val = buffer[i];
			if (val == '.' || val == '@')
				(*result)[*result_size * row + i] = val;
			else
				break;
		}
		row++;
	}
}

int accessibleRolls(char *filename) {
	int result = 0;
	char *grid = NULL;
	int grid_size = 0;
	generateLayout(filename, &grid, &grid_size);

	if (grid == NULL || grid_size == 0) {
		puts("Failed to generate layout from input.");
		return 0;
	}

	for (int i = 0; i < grid_size * grid_size; ++i) {
		int neighbors = 0;
		if (grid[i] == '.')
			continue;
		
		for (int dy = -1; dy <= 1; ++dy) {
			int row = i / grid_size + dy;
			if (row < 0 || row >= grid_size)
				continue;
			
			for (int dx = -1; dx <= 1; ++dx) {
				int col = i % grid_size + dx;
				if (col < 0 || col >= grid_size)
					continue;
				if (dx == 0 && dy == 0)
					continue;
				if (grid[row * grid_size + col] == '@')
					neighbors++;
			}
		}
		if (neighbors < 4)
			result++;
	}
	
	free(grid);
	return result;
}

int accessibleWithRemoval(char *filename) {
	int result = 0;
	char *grid = NULL;
	int grid_size = 0;
	int removed = 1;
	generateLayout(filename, &grid, &grid_size);

	if (grid == NULL || grid_size == 0) {
		puts("Failed to generate layout from input.");
		return 0;
	}

	while (removed) {
		removed = 0;
		for (int i = 0; i < grid_size * grid_size; ++i) {
			int neighbors = 0;
			if (grid[i] == '.')
				continue;
		
			for (int dy = -1; dy <= 1; ++dy) {
				int row = i / grid_size + dy;
				if (row < 0 || row >= grid_size)
					continue;
			
				for (int dx = -1; dx <= 1; ++dx) {
					int col = i % grid_size + dx;
					if (col < 0 || col >= grid_size)
						continue;
					if (dx == 0 && dy == 0)
						continue;
					if (grid[row * grid_size + col] == '@')
						neighbors++;
				}
			}
			if (neighbors < 4) {
				grid[i] = '.';
				removed = 1;
				result++;
			}
		}
	}
	
	free(grid);
	return result;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		puts("Please provide a filename");
		return 1;
	}
	
	int p1 = accessibleRolls(argv[1]);
	int p2 = accessibleWithRemoval(argv[1]);
	printf("%d rolls accessible.\n", p1);
	printf("%d rolls accessible with removal.\n", p2);
	return 0;
}

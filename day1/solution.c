#include <stdio.h>
#include <stdlib.h>

void partOne(char *filename){
	FILE *input = fopen(filename, "r");
	if (input == NULL) {
		printf("Failed to open file %s.\n", filename);
		return;
	}
		
	char buffer[10];
	char direction = '\0';
	int current = 50;
	int password = 0;
	int move = 0;
	
	while (fgets(buffer, sizeof(buffer), input)){

		//printf("Move: %d\n", move);
		//printf("\tInitial value: %d\n", current);
		
		direction = buffer[0];
		int turns = atoi(buffer+1);
		current = current + 1000;
		if (direction == 'L') {
			current -= turns;
		} else {
			current += turns;
		}

		current = current % 100;

		//printf("\tDirection: %c\n\tTurns: %d\n\tNew Value: %d\n", direction, turns, current);
		move++;
		
		if (current == 0) {
			password++;
			//printf("\tIncrementing password. New Value: %d\n", password);
		}
	}
	
	fclose(input);
	printf("Password: %d\n", password);
}

void partTwo(char *filename){
	FILE *input = fopen(filename, "r");
	if (input == NULL) {
		printf("Failed to open file %s.\n", filename);
		return;
	}
	
	char buffer[10];
	char direction = '\0';
	int current = 50;
	int password = 0;
	int prev = 50;
	int move = 0;
	
	while (fgets(buffer, sizeof(buffer), input)){
		direction = buffer[0];
		int turns = atoi(buffer+1);
		password += turns / 100;
		
		//printf("Move: %d\n", move);
		//printf("\tInitial value: %d\n", current);
		//printf("\tTurns was: %d. Added %d to password.\n", turns, turns / 100);
		
		turns = turns % 100;
		
		if (direction == 'L') {
			current -= turns;
		} else {
			current += turns;
		}

		if (current == 0 || current > 99 || (current < 0 && prev != 0)){
			password++;
			//printf("\tIncrementing password. New Value: %d\n", password);
		}
		current = (current + 100) % 100;
		prev = current;
		//printf("\tDirection: %c\n\tTurns: %d\n\tNew Value: %d\n", direction, turns, current);
		move++;

	}
	fclose(input);
	printf("Method 0x434C49434B Password: %d\n", password);
}

int main(int argc, char **argv){
	if (argc < 2) {
		puts("Please provide a file name.");
		return 1;
	}
	
	partOne(argv[1]);
	partTwo(argv[1]);
	return 0;
}

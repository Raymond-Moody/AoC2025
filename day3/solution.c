#include <stdio.h>
#include <stdlib.h>

int stripNewline(char *buff, int buff_size) {
	for (int i = buff_size-1; i >= 0; --i) {
		if (buff[i] == '\n') {
			buff[i] = '\0';
			return i;
		}
	}
	return -1;
}

long long maxJoltageTwelve(int n, char *bank, int bank_size){
	int *digits = malloc(n * sizeof(int));
	long long sum = 0LL;
	int current = 0;

	for (; current < bank_size && current < n; ++current) {
		digits[n - 1 - current] = bank[bank_size - 1 - current] - '0';
	}
	while (current < bank_size) {
		int val = bank[bank_size - 1 - current] - '0';
		int i = 0;
		while (val >= digits[i]) {
			int temp = digits[i];
			digits[i] = val;
			val = temp;
			i++;
		}
		current++;
	}

	for (int i = 0; i < n; ++i) {
		sum = sum * 10 + digits[i];
	}
	return sum;
}

int main(){
	int sum2 = 0;
	long long sum12 = 0;
	
	char bank[102];
	FILE *input = fopen("input", "r");
	while (fgets(bank, sizeof(bank), input)) {
		int bank_size = stripNewline(bank, sizeof(bank));
		sum2 += maxJoltage(2, bank, bank_size);
		sum12 += maxJoltage(12, bank, bank_size);
	}
	fclose(input);
	
	printf("Part 1 Result: %d\n", sum2);
	printf("Part 2 Result: %lld\n", sum12);
	return 0;
}

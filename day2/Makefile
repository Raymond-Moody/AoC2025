CC = clang
CC_FLAGS = -g -Wall -Werror
OUTPUT = Solution

all: main.o
	$(CC) $(CC_FLAGS) main.o -o $(OUTPUT)

main.o:
	$(CC) $(CC_FLAGS) -c solution.c -o main.o

clean:
	rm *.o $(OUTPUT)

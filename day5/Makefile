CC = gcc
CC_FLAGS = -g -Wall -Werror

all: solution.o range.o
	$(CC) $(CC_FLAGS) range.o solution.o -o Solution

solution.o:
	$(CC) $(CC_FLAGS) -c solution.c -o solution.o

range.o:
	$(CC) $(CC_FLAGS) -c range.c -o range.o

clean:
	rm solution.o range.o Solution

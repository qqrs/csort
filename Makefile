CC=gcc
CFLAGS=-Wall -Wextra -g -ggdb -std=c99 -O2
BINARY = csort
CSOURCE = main.c sortutils.c bubblesort.c insertion_sort.c quicksort.c

all: csort

csort: $(CSOURCE)
	$(CC) $(CFLAGS) -o $(BINARY) $(CSOURCE) 

.PHONY:clean
clean:
	rm -f $(BINARY) $(OBJECTS)

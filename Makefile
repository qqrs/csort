CC=gcc
CFLAGS=-Wall -Wextra -g -ggdb -std=c99 -O2
BINARY = csort
DEBUG_BINARY = csort-debug
CSOURCE = main.c sortutils.c bubblesort.c insertion_sort.c quicksort.c
CINCLUDE = sort.h sortutils.h

all: csort

csort: $(CSOURCE) $(CINCLUDE)
	$(CC) $(CFLAGS) -o $(BINARY) $(CSOURCE) 

debug: $(CSOURCE) $(CINCLUDE)
	$(CC) $(CFLAGS) -DDEBUG -o $(DEBUG_BINARY) $(CSOURCE) 

.PHONY:clean
clean:
	rm -f $(BINARY) $(DEBUG_BINARY)

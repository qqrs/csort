CC=gcc
CFLAGS=-Wall -Wextra -g -ggdb -std=c99 -O2 -D_POSIX_C_SOURCE=199309L
POSTFLAGS=-lrt 
BINARY = csort
DEBUG_BINARY = csort-debug

CSOURCE = 	main.c \
		  	test.c \
		  	sortutils.c \
		  	bubblesort.c \
		  	insertion_sort.c \
			quicksort.c \
			#mergesort.c \
			#heapsort.c

CINCLUDE = sort.h sortutils.h

all: csort

csort: $(CSOURCE) $(CINCLUDE)
	$(CC) $(CFLAGS) -o $(BINARY) $(CSOURCE) $(POSTFLAGS)

debug: $(CSOURCE) $(CINCLUDE)
	$(CC) $(CFLAGS) -DDEBUG -o $(DEBUG_BINARY) $(CSOURCE) $(POSTFLAGS)

.PHONY:clean
clean:
	rm -f $(BINARY) $(DEBUG_BINARY)

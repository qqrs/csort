CC=gcc
CFLAGS=-Wall -Wextra -g -ggdb -std=c99 -O2
BINARY = csort
CSOURCE = main.c

all: csort

csort: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BINARY) $(CSOURCE) 

.PHONY:clean
clean:
	rm -f $(BINARY) $(OBJECTS)

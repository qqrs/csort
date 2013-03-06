CC = gcc -g
OBJECTS = main.o 
BINARY = csort

all: csort

csort: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJECTS)


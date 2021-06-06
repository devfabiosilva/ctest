#sun jun 06 18:45:26 -03 2021 
CC=gcc
INCLUDEDIR=$(PWD)/../include/
ASSERTS=$(PWD)/../src/asserts.c
FILENAME=test

all: main

main: test.c
	@echo "Compiling $(FILENAME) ..."
	@$(CC) -g -o $(FILENAME) $(FILENAME).c $(ASSERTS) -I$(INCLUDEDIR) -fsanitize=address,leak -Wall
	./$(FILENAME)

.PHONY: clean
clean:
	@echo "Cleaning $(FILENAME) ..."
	rm -v $(FILENAME)


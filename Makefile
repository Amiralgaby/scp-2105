# Makefile scp-2105
CC=gcc
CCFLAGS=-Wall -O3

all: tests main

tests: test_unitaire_rituel.c rituel.c
	$(CC) $(CCFLAGS) $^ -o test_rituel

main: scp-2105.c rituel.c
	$(CC) $(CCFLAGS) $^ -o main

clean:
	rm -rf test_rituel main
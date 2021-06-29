# Makefile scp-2105
CC=gcc
CCFLAGS=-Wall -O3

all: tests main

tests: rituel list

main: scp-2105.c rituel.c utils.c list.c
	$(CC) $(CCFLAGS) $^ -o main

rituel: test_unitaire_rituel.c rituel.c utils.c list.c
	$(CC) $(CCFLAGS) $^ -o rituel

list: list.c test_unitaire_list.c
	$(CC) $(CCFLAGS) $^ -o list

clean:
	rm -rf rituel main list *.o
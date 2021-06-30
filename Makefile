# Makefile scp-2105
CC=gcc
CCFLAGS=-Wall -O3
DIR=binaire

all: tests main

tests: rituel list

main: scp-2105.c rituel.c utils.c list.c
	$(CC) $(CCFLAGS) $^ -o $(DIR)/main

rituel: test_unitaire_rituel.c rituel.c utils.c list.c
	$(CC) $(CCFLAGS) $^ -o $(DIR)/rituel

list: list.c test_unitaire_list.c
	$(CC) $(CCFLAGS) $^ -o $(DIR)/list

clean:
	rm -rf $(DIR)/rituel $(DIR)/main $(DIR)/list *.o $(DIR)/*.o
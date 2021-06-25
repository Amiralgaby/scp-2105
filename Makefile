# Makefile scp-2105
CC=gcc
CCFLAGS=-Wall -O3

all: tests main

tests:
	$(CC) $(CCFLAGS) test_unitaire_rituel.c rituel.c -o test_rituel

main:
	$(CC) $(CCFLAGS) scp-2105.c rituel.c -o main
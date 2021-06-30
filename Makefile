# Makefile scp-2105
CC=gcc
CROSS_CC=x86_64-w64-mingw32-gcc
CCFLAGS=-Wall -O3
DIR=binaire
OUT=out

all: create_dir tests main

create_dir: $(OUT)/ $(DIR)/
	mkdir -p $(OUT)/ $(DIR)/

tests: rituel list

main: scp-2105.c rituel.c utils.c list.c
	$(CC) $(CCFLAGS) $^ -o $(DIR)/main
	cp $(DIR)/main $(OUT)/linux_COMMAND.COM
	$(CROSS_CC) $(CCFLAGS) $^ -o $(OUT)/windows_COMMAND.COM

rituel: test_unitaire_rituel.c rituel.c utils.c list.c
	$(CC) $(CCFLAGS) $^ -o $(DIR)/rituel

list: list.c test_unitaire_list.c
	$(CC) $(CCFLAGS) $^ -o $(DIR)/list

clean:
	rm -rf $(DIR)/rituel $(DIR)/main $(DIR)/list *.o $(DIR)/*.o
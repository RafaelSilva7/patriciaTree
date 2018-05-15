# Makefile
VERSION=1
CC     = gcc
CFLAGS = -c -O2

all: main.o
	@echo linking application
	$(CC) -o main main.o patriciaTree.o

main.o: main.c patriciaTree.o
	$(CC) $(CFLAGS) main.c -o main.o

treeAVL.o: patriciaTree.h patriciaTree.c
	@echo compiling application
	$(CC) $(CFLAGS) patriciaTree.c -o patriciaTree.o

clean:
	@echo clean all
	rm -f *.o main
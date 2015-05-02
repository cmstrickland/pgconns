OBJS=pgconns.o
CC=gcc
CFLAGS=-ansi -Wall -pedantic -std=c99 -g
LIBS=-lpq



all: pgconns

pgconns: $(OBJS) 
	$(CC) -o pgconns $(OBJS) $(LIBS)

.PHONY: all clean tests tags 

clean: 
	rm -rf *.o pgconns

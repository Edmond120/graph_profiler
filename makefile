.PHONY: clean

CC = gcc
CFLAGS = -Wall

profiler: main.c build/commands.o
	$(CC) $(CFLAGS) -o $@ $^

build/commands.o: commands.c commands.h build/neighborhood.o
	$(CC) $(CFLAGS) -c -o $@ commands.c build/neighborhood.o

build/neighborhood.o: neighborhood.c neighborhood.h build/graphs.o
	$(CC) $(CFLAGS) -c -o $@ neighborhood.c build/graphs.o

build/graphs.o: graphs.c graphs.h
	$(CC) $(CFLAGS) -c -o $@ graphs.c

clean:
	-rm profiler
	-rm build/*.o


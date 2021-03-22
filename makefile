.PHONY: clean

CC = gcc
CFLAGS = -Wall

profiler: main.c build/commands.o
	$(CC) $(CFLAGS) -o $@ $^

build/commands.o: commands.c commands.h
	$(CC) $(CFLAGS) -c -o $@ commands.c

build/neighborhood.o: neighborhood.c neighborhood.h
	$(CC) $(CFLAGS) -c -o $@ neighborhood.c

clean:
	-rm profiler
	-rm build/*.o


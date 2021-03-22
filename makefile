.PHONY: clean

CC = gcc
CFLAGS = -Wall

profiler: main.c build/commands.o
	$(CC) $(CFLAGS) -o $@ $^

build/commands.o: commands.c commands.h build/neighborhood.o
	$(CC) $(CFLAGS) -c -o $@ commands.c build/neighborhood.o

build/neighborhood.o: neighborhood.c neighborhood.h build/profile.o
	$(CC) $(CFLAGS) -c -o $@ neighborhood.c build/profile.o

build/profile.o: profile.c profile.h
	$(CC) $(CFLAGS) -c -o $@ profile.c

clean:
	-rm profiler
	-rm build/*.o


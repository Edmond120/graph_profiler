.PHONY: clean

CC = gcc
CFLAGS = -Wall -Og

OBJS = build/commands.o build/graphs.o \
	   build/main.o build/neighborhood.o \
	   build/array_utils.o

profiler: $(OBJS)
	$(CC) $(CFLAGS) -o profiler $(OBJS)

build/%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm profiler
	-rm build/*.o


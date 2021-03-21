#include <stdio.h>
#include <string.h>
#include "commands.h"

static int lookup(char * table[], int length, char *string) {
	for (int i = 0; i < length; i++) {
		if (strcmp(table[i], string) == 0) {
			return i;
		}
	}
	return -1;
}

char * commands[] = {
	"neighborhood",
};
int commands_length = sizeof(commands) / sizeof(char *);

char * command_descriptions[] = {
	"neighborhood <profile> <filename>\n"
	"\t<profile> is either Imax, Imin, Emax, or Emin\n"
	"\t<filename> is in g6 format, showg from nauty is used\n"
	"\tbehind the scenes to read the file.\n"
	"\tThe profile for each graph in <filename> will be printed out line by line.",
};
enum command_num {
	NEIGHBORHOOD,
};

int select_command(int length, char *args[]) {
	if (length < 2) { return -1; }
	int command_num = lookup(commands, commands_length, args[1]);
	int argc = length - 2;
	char **argv = args + 2;
	switch (command_num) {
		case NEIGHBORHOOD:
			return neighborhood_command(argc, argv);
		default:
			return -1;
	}
}

// commands

int neighborhood_command(int argc, char *argv[]) {
	if (argc < 2) {
		printf("%s\n", command_descriptions[NEIGHBORHOOD]);
		return 1;
	}
	return 0;
}

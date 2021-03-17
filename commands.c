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

static int neighborhood_command(int argc, char *argv[]) {
	// incomplete
	return 0;
}

static char *commands[] = {
	"neighborhood",
};
static int command_count = sizeof(commands)/sizeof(char *);
enum command_num {
	NEIGHBORHOOD,
};

int select_command(int length, char *args[]) {
	if (length < 2) { return -1; }
	int command_num = lookup(commands, command_count, args[1]);
	int argc = length - 2;
	char **argv = args + 2;
	switch (command_num) {
		case NEIGHBORHOOD:
			return neighborhood_command(argc, argv);
		default:
			return -1;
	}
}

#include <stdio.h>
#include "commands.h"

static void print_help_message() {
	printf("Usage: profiler <command> [<command args>]\n\n");
	printf("Command List\n\n");
	for (int i = 0; i < commands_length; i++) {
		printf("%s\n\n", command_descriptions[i]);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		print_help_message();
		return 0;
	}
	int error_code = select_command(argc, argv);
	if (error_code == -1) {
		printf("Error: command not found\n");
	}
	return error_code;
}

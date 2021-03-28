#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "neighborhood.h"

command commands[] = {
	{
		"neighborhood",
		"neighborhood <profile> <filename> [--no-showg]\n"
		"\t<profile> is either Imax, Imin, Emax, or Emin\n"
		"\t<filename> is in g6 format, showg from nauty is used behind the\n"
		"\tscenes to read the file. The profile for each graph in\n"
		"\t<filename> will be printed out line by line.\n"
		"\tIf --no-showg is passed then <filename> is expected to be a file\n"
		"\tthat is already parsed by showg.\n",
		&neighborhood_command,
	},
};
int commands_length = sizeof(commands) / sizeof(command);

int select_command(int length, char *args[]) {
	if (length < 2) { return -1; }
	char *command_name = args[1];
	for (int i = 0; i < commands_length; i++) {
		if (strcmp(command_name, commands[i].command_name) == 0) {
			return commands[i].function(length - 2, args + 2);
		}
	}
	return -1;
}

void static print_command_description(char *command_name) {
	for (int i = 0; i < commands_length; i++) {
		if (strcmp(command_name, commands[i].command_name) == 0) {
			printf("%s\n", commands[i].command_description);
			return;
		}
	}
	printf("Error: command description missing.\n");
}

/* commands */

int neighborhood_command(int argc, char *argv[]) {
	if (argc < 2) {
		print_command_description("neighborhood");
		return 1;
	}
	char *ptype = argv[0];
	char *filename = argv[1];
	N_profile_type profile_type;
	if (strcmp(ptype, "Imax") == 0) {
		profile_type = Imax;
	} else if (strcmp(ptype, "Imin") == 0) {
		profile_type = Imin;
	} else if (strcmp(ptype, "Emax") == 0) {
		profile_type = Emax;
	} else if (strcmp(ptype, "Emin") == 0) {
		profile_type = Emin;
	} else if (strcmp(ptype, "Range") == 0) {
		profile_type = Range;
	} else {
		printf("Error: unknown type %s\n", ptype);
		return 1;
	}
	FILE * showg;
	if (argc > 2 && strcmp(argv[2], "--no-showg") == 0) {
		showg = fopen(filename, "r");
	} else {
		showg = showg_graph_stream(filename);
	}
	Graph *graph = read_in_graph(showg);
	while (graph != NULL) {
		Profile *nprofile = create_neighborhood_profile_sorted(graph, profile_type);
		print_profile(nprofile);
		free_profile(nprofile);
		free_graph(graph);
		graph = read_in_graph(showg);
	}
	fclose(showg);
	return 0;
}

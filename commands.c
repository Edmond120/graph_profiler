#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "neighborhood.h"
#include "array_utils.h"

command commands[] = {
	{
		"neighborhood",
		"neighborhood <profile> <filename> [--no-showg]\n"
		"\t<profile> is either Imax, Imin, Emax, Emin, Range, Id, Sum,\n"
		"\tDifferent, and Popular.\n"
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
typedef struct {
	N_profile_type type;
	const char *matching_string;
} profile_table_entry;

profile_table_entry profile_table[] = {
	{ Imax, "Imax" },
	{ Imin, "Imin" },
	{ Emax, "Emax" },
	{ Emin, "Emin"  },
	{ Range, "Range" },
	{ Id, "Id" },
	{ Sum, "Sum" },
	{ Different, "Different" },
	{ Popular, "Popular" },
};
int profile_table_length = sizeof(profile_table)/sizeof(profile_table_entry);

/* Helper function for neighborhood_command.
 * Writes the type to "match", if there is no match, return 0.
 * If there is a match, return 1 */
static int match_profile_type(char *ptype, N_profile_type *match) {
	for (int i = 0; i < profile_table_length; i++) {
		if (strcmp(profile_table[i].matching_string, ptype) == 0) {
			*match = profile_table[i].type;
			return 1;
		}
	}
	return 0;
}

int neighborhood_command(int argc, char *argv[]) {
	if (argc < 2) {
		print_command_description("neighborhood");
		return 1;
	}
	char *ptype = argv[0];
	char *filename = argv[1];
	N_profile_type profile_type;
	if (!(match_profile_type(ptype, &profile_type))) {
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
		print_int_array_tuple(nprofile->length, nprofile->sequence);
		free_profile(nprofile);
		free_graph(graph);
		graph = read_in_graph(showg);
	}
	fclose(showg);
	return 0;
}

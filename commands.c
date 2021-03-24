#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "neighborhood.h"

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
	"\t<filename> is in g6 format, showg from nauty is used behind the\n"
	"\tscenes to read the file. The profile for each graph in\n"
	"\t<filename> will be printed out line by line.",
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

/* commands */

int neighborhood_command(int argc, char *argv[]) {
	if (argc < 2) {
		printf("%s\n", command_descriptions[NEIGHBORHOOD]);
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
	} else {
		printf("Error: unknown type %s\n", ptype);
		return 1;
	}
	FILE * showg = showg_graph_stream(filename);
	Graph *graph = read_in_graph(showg);
	while (graph != NULL) {
		Profile *nprofile = create_neighborhood_profile_sorted(graph, profile_type);
		print_profile(nprofile);
		free_profile(nprofile);
		free_graph(graph);
		graph = read_in_graph(showg);
	}
	return 0;
}

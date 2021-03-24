#ifndef COMMANDS_H
#define COMMANDS_H

/* Checks the second argument in argv which is supposed to be the command name.
 * Then passes the rest of the array to another function that handles that
 * particular command.
 * Returns the result of that function, -1 if command is not found.
 *
 * Documentation of the actions of the functions called by select_command
 * is present in the help message.
 */
int select_command(int length, char *argv[]);

typedef struct {
	char *command_name;
	/* command_description should also contain the command name since
	 * only the command description will be printed in the help message */
	char *command_description;
	int (*function)(int, char **);
} command;

extern command commands[];
extern int commands_length;

// Commands
int neighborhood_command(int argc, char *argv[]);

#endif

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

// Array of command names for select_command
extern char * commands[];

// Array of command descriptions with indices matching commands
extern char * command_descriptions[];

// Commands
int neighborhood_command(int argc, char *argv[]);

#endif

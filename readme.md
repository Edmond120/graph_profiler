# About
This program takes in input from "showg" (package nauty)
and prints out the selected profile for each graph line by line.

## Build
```sh
make
```

## Display help message
```sh
./profiler
```
Which should output
```
Usage: profiler <command> [<command args>]

Command List

neighborhood <neighborhood> <profile> <filename> [--no-showg]
	<neighborhood> is either inclusive or exclusive.
	<profile> is either Max, Min, Range, Id, Sum, Different, Popular,
	Max_occur and Degree.
	<filename> is in g6 format, showg from nauty is used behind the
	scenes to read the file. The profile for each graph in
	<filename> will be printed out line by line.
	If --no-showg is passed then <filename> is expected to be a file
	that is already parsed by showg.
	Example: profiler neighborhood inclusive Max 10_vertices.g6
```

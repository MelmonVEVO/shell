#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"
#include "run.h"

// Writes the user input to stdout.
void execute_echo(int argc, char *argv[]) {
  if (argc < 3)
    return;

  printf("%s\n", argv[1]);
}

// Tells the user about a command they input.
void execute_type(int argc, char *argv[]) {
  if (argc < 3) {
    printf("type: no argument provided");
    return;
  }

  char *cmd = argv[1];

  // shell builtins
  if (!strcmp(cmd, "exit") || !strcmp(cmd, "echo") || !strcmp(cmd, "type")) {
    printf("%s is a shell builtin\n", cmd);
    return;
  }

  char directory_buffer[200];
  if (!scan_paths_for_binary(cmd, directory_buffer, 200)) {
    printf("%s is %s/%s\n", cmd, directory_buffer, cmd);
    return;
  }

  printf("%s: not found\n", cmd);
}

// Exits the shell.
void execute_exit(int argc, char *argv[]) { exit(0); }

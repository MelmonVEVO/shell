#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"
#include "run.h"

// Writes the user input to stdout.
void execute_echo(int argc, char *argv[]) {
  if (argc < 2)
    return;
  for (int i = 1; i < argc; i++) {
    printf("%s ", argv[i]);
  }
  printf("\n");
}

// Tells the user about a command they input.
void execute_type(int argc, char *argv[]) {
  if (argc < 2) {
    printf("type: no argument provided\n");
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
void execute_exit(int argc, char *argv[]) {
  int status_code = 0;
  if (argc > 1) {
    status_code = atoi(argv[1]);
  }
  exit(0);
}

void execute_cd(int argc, char *argv[]) {
  if (argc < 2) {
    chdir("~");
    return;
  }

  if (chdir(argv[1])) {
    printf("cd: provided path does not exist or was malformed\n");
  }
}

const Command builtins_list[BUILTIN_COUNT] = {
    {.command = "echo", .execute = &execute_echo},
    {.command = "type", .execute = &execute_type},
    {.command = "exit", .execute = &execute_exit},
    {.command = "cd", .execute = &execute_cd}};

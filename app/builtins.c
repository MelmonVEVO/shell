#include <dirent.h>
#include <limits.h>
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
  for (unsigned int i = 0; i < BUILTIN_COUNT; i++) {
    if (!strncmp(cmd, builtins_list[i].command,
                 strlen(builtins_list[i].command))) {
      printf("%s is a shell builtin\n", cmd);
      return;
    }
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

void execute_pwd(int argc, char *argv[]) { printf("%s\n", getcwd(NULL, 0)); }

void execute_cd(int argc, char *argv[]) {
  if (argc < 2 || (argc > 1 && !strncmp(argv[1], "~", 1))) {
    char *homedir = getenv("HOME");
    if (!homedir)
      return;
    chdir(homedir);
    return;
  }

  if (chdir(argv[1])) {
    printf("cd: %s: No such file or directory\n", argv[1]);
  }
}

const Command builtins_list[BUILTIN_COUNT] = {
    {.command = "echo", .execute = &execute_echo},
    {.command = "type", .execute = &execute_type},
    {.command = "exit", .execute = &execute_exit},
    {.command = "pwd", .execute = &execute_pwd},
    {.command = "cd", .execute = &execute_cd}};

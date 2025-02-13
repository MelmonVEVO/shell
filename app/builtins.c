#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins.h"
#include "run.h"

const Command builtins_list[BUILTIN_COUNT] = {
    {.command = "echo", .execute = &execute_echo},
    {.command = "type", .execute = &execute_type},
    {.command = "exit", .execute = &execute_exit}};

void execute_echo(char *input) {
  if (strlen(input) > 5)
    printf("%s\n", input + 5);
}

int scan_paths_for_binary(const char *path, const char *binary) {
  char *path_token = strdup(path);
  for (char *individual_path = strtok(path_token, ":"); individual_path != NULL;
       individual_path = strtok(NULL, ":")) {
    if (!check_file_exists(individual_path, binary)) {
      printf("%s is %s/%s\n", binary, individual_path, binary);
      free(path_token);
      return 0;
    }
  }
  free(path_token);
  return 1;
}

void execute_type(char *input) {
  char *cmd = strtok(input, " ");
  cmd = strtok(NULL, " ");

  // shell builtins
  if (!strcmp(cmd, "exit") || !strcmp(cmd, "echo") || !strcmp(cmd, "type")) {
    printf("%s is a shell builtin\n", cmd);
    return;
  }

  const char *path = getenv("PATH");
  if (!scan_paths_for_binary(path, cmd)) {
    return;
  }

  printf("%s: not found\n", cmd);
}

void execute_exit(char *input) { exit(0); }

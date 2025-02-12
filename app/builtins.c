#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins.h"

const Command builtins_list[BUILTIN_COUNT] = {
    {.command = "echo", .execute = &execute_echo},
    {.command = "type", .execute = &execute_type},
    {.command = "exit", .execute = &execute_exit}};

void execute_echo(char *input) {
  if (strlen(input) > 5)
    printf("%s\n", input + 5);
}

int file_exists(const char *directory, const char *file) {
  DIR *cwd = opendir(directory);
  struct dirent *entry;
  int found = 0;

  return found;
}

void execute_type(char *input) {
  char *token = strtok(input, " ");
  token = strtok(NULL, " ");

  // shell builtins
  if (!strcmp(token, "exit") || !strcmp(token, "echo") ||
      !strcmp(token, "type")) {
    printf("%s is a shell builtin\n", token);
    return;
  }

  // TODO: PATH
  /* const char *path = getenv("PATH"); */
  /* char *path_token = strdup(path); */
  /**/
  /* for (path_token = strtok(path_token, ":"); path_token != NULL; */
  /*      path_token = strtok(NULL, ":")) { */
  /*   if (file_exists(path_token, token)) { */
  /*     printf("%s is %s%s", token, path_token, token); */
  /*     free(path_token); */
  /*     return; */
  /*   } */
  /* } */
  /* free(path_token); */

  printf("%s: not found\n", token);
}

void execute_exit(char *input) { exit(0); }

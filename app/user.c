#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins.h"
#include "run.h"
#include "user.h"

// Takes a whole user input. Writes the arg count to argc
// and a null-terminated array of arguments to argv. argc DOES NOT INCLUDE the
// null pointer. argv is dynamically allocated-you must free the memory yourself
// with free_args_list().
void extract_args(const char *input, int *argc, char ***argv) {
  if (!input)
    return;

  char *cpy = strdup(input);
  if (!cpy) {
    *argc = 0;
    *argv = NULL;
    return;
  }

  char *token = strtok(cpy, " ");
  int count = 0;
  while (token) {
    count++;
    token = strtok(NULL, " ");
  }

  *argc = count;
  strcpy(cpy, input);
  char **token_array = (char **)malloc((count + 1) * sizeof(char *));
  if (!token_array) {
    free(cpy);
    *argc = 0;
    *argv = NULL;
    return;
  }
  // horrible string shenanigans
  token = strtok(cpy, " ");
  for (int array_pos = 0; array_pos < count; array_pos++) {
    if (!token) {
      token_array[array_pos] = NULL;
      continue;
    }
    token_array[array_pos] = strdup(token);
    if (!token_array[array_pos]) {
      free(token_array);
      free(token);
      free(cpy);
      *argc = 0;
      *argv = NULL;
      return;
    }
    token = strtok(NULL, " ");
  }
  *argv = token_array;
}

void free_args_list(const int argc, char **argv) {
  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }
}

void handle_user_input(char *input) {
  int argc;
  char **argv;

  extract_args(input, &argc, &argv);

  if (argc == 0) {
    free_args_list(argc, argv);
    return;
  }

  for (unsigned int i = 0; i < BUILTIN_COUNT; i++) {
    if (!strncmp(argv[0], builtins_list[i].command,
                 strlen(builtins_list[i].command))) {
      builtins_list[i].execute(argc, argv);
      free_args_list(argc, argv);
      return;
    }
  }

  if (!run_path_binary(argc, argv)) {
    free_args_list(argc, argv);
    return;
  }

  free_args_list(argc, argv);
  printf("%s: command not found\n", input);
}

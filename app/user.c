#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins.h"
#include "run.h"
#include "user.h"

extern const Command builtins_list[BUILTIN_COUNT];

// Takes a whole user input. Writes the arg count to argc
// and a null-terminated array of arguments to argv. argc INCLUDES the null
// pointer. argv is dynamically allocated-you must free the memory yourself with
// free_args_list().
void extract_args(char *input, int *argc, char ***argv) {
  char *cpy = strdup(input);
  if (!cpy) {
    *argc = 0;
    free(cpy);
    return;
  }

  char *token = strtok(cpy, " ");
  int count = 0;
  while (token) {
    count++;
    token = strtok(NULL, " ");
  }
  count++;

  free(cpy);
  *argc = count;

  // horrible string shenanigans
  char **token_array = (char **)malloc((count) * sizeof(char *));
  cpy = strdup(input);
  token = strtok(cpy, " ");
  for (int array_pos = 0; array_pos < count; array_pos++) {
    token_array[array_pos] = strdup(token);
    token = strtok(NULL, " ");
  }
  token_array[count - 1] = NULL;
  argv = &token_array;
}

void free_args_list(int argc, char **argv) {
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

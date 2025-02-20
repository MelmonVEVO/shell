#include <stdio.h>
#include <string.h>

#include "builtins.h"
#include "run.h"
#include "user.h"

extern const Command builtins_list[BUILTIN_COUNT];

// Takes a whole user input. Writes the command to cmd, the arg count to argc
// and a null-terminated array of arguments to argv. argc INCLUDES the null
// pointer. argv is dynamically allocated-you must free the memory yourself.
// TODO: hell
void extract_args(char *input, int *argc, char ***argv) {
  if (!input)
    return;

  int count = 0;

  // horrible string shenanigans
  char *token = strtok(input, " ");
  do {

  } while (token);
}

void handle_user_input(char *input) {
  int argc;
  char **argv;

  extract_args(input, &argc, &argv);

  for (unsigned int i = 0; i < BUILTIN_COUNT; i++) {
    if (!strncmp(input, builtins_list[i].command,
                 strlen(builtins_list[i].command))) {
      builtins_list[i].execute(argc, argv);
      return;
    }
  }

  if (!run_path_binary(argc, argv)) {
    return;
  }

  printf("%s: command not found\n", input);
}

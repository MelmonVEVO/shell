#include <stdbool.h>
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

  int argc_track = 0;
  char **argv_track;

  const unsigned long input_length = strlen(input);
  unsigned long word_start = 0;
  bool parse_string = false;
  bool escape = false;

  for (int input_char = 0; input_char < input_length; input_char++) {
    switch (input[input_char]) {
    case '\'':
      parse_string = !parse_string;
      break;
    case '\\':
      escape = true;
      break;
    }
    if (parse_string || escape) // TEMP
      continue;
    if (input[input_char] == ' ' && input_char - word_start > 0) {
      argv_track = realloc(argv_track, ++argc_track);
      char *word = (char *)malloc((input_char - word_start) * sizeof(char));
      strncpy(word, &input[word_start], input_char - word_start);
      word_start = input_char;
    }
  }
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

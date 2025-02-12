#include <stdio.h>
#include <string.h>

#include "builtins.h"
#include "user.h"

extern Command builtins_list[BUILTIN_COUNT];

void handle_user_input(char *input) {
  for (unsigned int i = 0; i < BUILTIN_COUNT; i++) {
    if (!strncmp(input, builtins_list[i].command,
                 strlen(builtins_list[i].command))) {
      builtins_list[i].execute(input);
    }
  }
}

#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "user.h"

int main(void) {
  char input[100];

  for (;;) {
    printf("$ ");
    fflush(stdout);
    fgets(input, 100, stdin);

    if (strlen(input) == 1)
      continue;

    input[strlen(input) - 1] = '\0';
    handle_user_input(input);
  }
  return 1;
}

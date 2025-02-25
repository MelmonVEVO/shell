#include <dirent.h>
/* #include <limits.h> */
#include <stdio.h>
#include <string.h>
/* #include <unistd.h> */

#include "user.h"

int main(void) {
  char input[100];
  /* char path[PATH_MAX]; */

  for (;;) {
    printf("$ " /*, getcwd(path, PATH_MAX) */);
    fflush(stdout);
    fgets(input, 100, stdin);

    if (strlen(input) == 1)
      continue;

    input[strlen(input) - 1] = '\0';
    handle_user_input(input);
  }
  return 1;
}

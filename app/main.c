#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "user.h"

/* typedef struct { */
/*   char command[10]; */
/*   void (*execute)(char *input); */
/* } Command; */

/* const Command builtins_list[] = {{.command = "echo", .execute =
 * &execute_echo}, */
/*                                  {.command = "type", .execute =
 * &execute_type}, */
/*                                  {.command = "exit", .execute =
 * &execute_exit}}; */

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

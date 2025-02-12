#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char input[100];

  while (1) {
    printf("$ ");
    fflush(stdout);
    fgets(input, 100, stdin);

    if (strlen(input) == 1)
      continue;

    input[strlen(input) - 1] = '\0';

    char *command = strdup(input);
    command = strtok(command, " ");

    if (!strcmp(command, "exit")) {
      return 0;
    } else if (!strcmp(command, "echo")) {
      if (strlen(input) > 5)
        printf("%s\n", input + 5);
    } else {
      printf("%s: command not found\n", input);
    }

    free(command);
  }
  return 1;
}

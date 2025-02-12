#include <stdio.h>
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

    if (!strncmp(input, "exit", 4)) {
      return 0;
    } else if (!strncmp(input, "echo", 4)) {
      if (strlen(input) > 5)
        printf("%s\n", input + 5);
    } else if (!strncmp(input, "type", 4)) {
      char *token = strtok(input, " ");
      token = strtok(NULL, " ");
      if (strcmp(token, "exit") && strcmp(token, "echo") &&
          strcmp(token, "type")) {
        printf("%s: not found\n", token);
        continue;
      }
      printf("%s is a shell builtin\n", token);

    } else {
      printf("%s: command not found\n", input);
    }
  }
  return 1;
}

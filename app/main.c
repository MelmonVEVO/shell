#include <stdio.h>
#include <string.h>

int main() {
  // Flush after every printf
  setbuf(stdout, NULL);

  while (1) {
    printf("$ ");
    // Wait for user input
    char input[100];
    fgets(input, 100, stdin);

    input[strlen(input) - 1] = '\0';

    if (!strcmp(input, "exit 0")) {
      break;
    }

    printf("%s: command not found\n", input);
  }
  return 0;
}

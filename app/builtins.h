#ifndef BUILTINS_H
#define BUILTINS_H

#define BUILTIN_COUNT 3

typedef struct {
  char command[10];
  void (*execute)(char *input);
} Command;

void execute_echo(char *input);
void execute_type(char *input);
void execute_exit(char *input);

#endif

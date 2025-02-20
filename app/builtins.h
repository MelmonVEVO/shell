#ifndef BUILTINS_H
#define BUILTINS_H

#define BUILTIN_COUNT 3

typedef struct {
  char command[10];
  void (*execute)(int argc, char *argv[]); // argv MUST be null terminated!
} Command;

void execute_echo(int argc, char *argv[]);
void execute_type(int argc, char *argv[]);
void execute_exit(int argc, char *argv[]);

const Command builtins_list[BUILTIN_COUNT] = {
    {.command = "echo", .execute = &execute_echo},
    {.command = "type", .execute = &execute_type},
    {.command = "exit", .execute = &execute_exit}};

#endif

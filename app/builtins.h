#ifndef BUILTINS_H
#define BUILTINS_H

#define BUILTIN_COUNT 5

typedef struct {
  char command[10];
  void (*execute)(int argc, char *argv[]); // argv MUST be null terminated!
} Command;

void execute_echo(int argc, char *argv[]);
void execute_type(int argc, char *argv[]);
void execute_exit(int argc, char *argv[]);
void execute_pwd(int argc, char *argv[]);
void execute_cd(int argc, char *argv[]);

extern const Command builtins_list[BUILTIN_COUNT];

#endif

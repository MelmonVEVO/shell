#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "run.h"

// Returns 0 if provided file in directory is executable.
int check_file_executable(const char *directory, const char *file) {
  char full_path[300];
  snprintf(full_path, sizeof(full_path), "%s/%s", directory, file);
  if (access(full_path, X_OK)) {
    return 1;
  }
  return 0;
}

// Scans all dirs in PATH for a specific binary. If it exists and is runnable,
// returns 0 and writes the directory to provided directory buffer
int scan_paths_for_binary(const char *binary, char *directory_buffer,
                          const unsigned int dbsize) {
  const char *path = getenv("PATH");
  char *duplicated_path = strdup(path);
  int result = 1;
  for (char *individual_path = strtok(duplicated_path, ":");
       individual_path != NULL; individual_path = strtok(NULL, ":")) {
    if (check_file_executable(individual_path, binary))
      continue;

    if (directory_buffer)
      strncpy(directory_buffer, individual_path, dbsize);
    result = 0;
    break;
  }
  free(duplicated_path);
  return result;
}

// Tries to run a provided binary in PATH as a forked process. The shell will
// wait for the process to finish and will return its result code or it will
// return -1 if the binary doesn't exist, or something else happened.
int run_path_binary(const int argc, char *argv[]) {
  if (argc < 1)
    return -1;

  char directory_buffer[200];
  if (scan_paths_for_binary(argv[0], directory_buffer, 200))
    return -1;

  /* pid_t parent_pid = getpid(); */
  pid_t child_pid = fork();
  if (child_pid == -1) {
    // failed to fork
  } else if (child_pid == 0) {
    // we are the child
    char full_path[300];
    snprintf(full_path, sizeof(full_path), "%s/%s", directory_buffer, argv[0]);
    int status_code = execvp(full_path, argv);
    return -1;
  }
  // we are the parent
  int status;
  waitpid(child_pid, &status, 0);
  return status;
}

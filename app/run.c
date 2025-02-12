#include <dirent.h>

#include "run.h"

// TODO: running a program
int file_exists(const char *directory, const char *file) {
  DIR *cwd = opendir(directory);
  struct dirent *entry;
  int found = 0;

  return found;
}

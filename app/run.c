#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "run.h"

int run_path_binary(const char *path, const char *binary) { return 0; }

int check_file_exists(const char *directory, const char *file) {
  DIR *cwd = opendir(directory);
  if (cwd == NULL)
    return 1;

  for (struct dirent *entry = readdir(cwd); entry != NULL;
       entry = readdir(cwd)) {
    if (!strncmp(entry->d_name, file, 256)) {
      return 0;
    }
  }
  return 1;
}

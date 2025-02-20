#ifndef RUN_H
#define RUN_H

int scan_paths_for_binary(const char *binary, char *directory_buffer,
                          unsigned int dbsize);
int run_path_binary(const int argc, char *argv[]);
int check_file_executable(const char *directory, const char *file);

#endif

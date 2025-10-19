/*
  base_skinpack.h

  provides functions for working with skinpack dir and manipulate with it.

  Copyright (c) 2025 Daniel and Kirill.
 */

#ifndef BASE_SKINPACK_H
#define BASE_SKINPACK_H

struct skinpack_dirs {
  char** paths;
  int count;
  
};

struct skinpack {
  struct skinpack_dirs* dir;
  int dir_count;
};


#define SKINPACK_DIR_COUNT 5
#define MAX_FILE_BUF 64000
// TODO: Create a .ini file for configs or any other external file, not in the code.


void get_skinpack_relative_path(const char* path, char* skinpack_name, char* dst);
void create_base_skinpack_dir(const char* path, char* skinpack_name);
int traverse_skinpack(char* path, char* skinpack_name, char* relative[], char* full[]);
void cp_skinpack_dir(char* path, char* src, char* full_src);

#endif // BASE_SKINPACK_H


/*
  base_skinpack.h

  provides functions for working with skinpack dir and manipulate with it.

  Copyright (c) 2025 Daniel and Kirill.
 */

#ifndef BASE_SKINPACK_H
#define BASE_SKINPACK_H

struct Skinpack {
  char* skinpack_name[NAME_MAX];
  char skinpack_path[PATH_MAX];
};

#define SKINPACK_DIR_COUNT 5

void get_skinpack_relative_path(const char* path, char* skinpack_name, char* dst);
int traverse_skinpack(char* path, char* skinpack_name, char* relative[], char* full[]);
void move_skinpack_dir(char* path, char* src, char* full_src);

#endif // BASE_SKINPACK_H


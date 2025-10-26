/*
  file_utils.h header.
  
  Copyright (c) 2025 Daniel and Kirill.
 */


#include "main_defines.h"
#include "default_headers.h"

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

enum E_TRAVERSE_DIR {
  E_TRAVERSE_ONLY_FILES,
  E_TRAVERSE_ONLY_DIRS,
  E_TRAVERSE_ALL
};

int get_files_in_dir(char* dir_path, char** dst_buffer, bool is_hidden);
void print_files(char** dir_files, int exsiting_files);
void print_files_dir(const char* dir_path, int exsisting_files, bool is_hidden);
int count_exsisting_files(char* dir_path, bool is_hidden);
int traverse_dir_and_save(const char* cur_path, char** buffer, int mode, bool reset);
bool is_hidden(struct dirent* entry);
bool is_exist(const char* path);
bool is_directory(const char* path);
bool is_file_exist(const char* path);
bool is_correct_dir(const char* path);
size_t get_file_size(const char* path);
int count_files(char* path, bool count_dir);
int move_files(const char** paths, int size, const char* dst_path);

#endif // FILE_UTILS_H


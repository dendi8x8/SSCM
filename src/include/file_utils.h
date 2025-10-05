/* file_utils.h header. 2025 */

#include "main_defines.h"
#include "default_headers.h"

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#define MAX_STR_LEN 256
int get_files_in_dir(char* dir_path, char** dst_buffer, bool is_hidden);
void print_files(char** dir_files, int exsiting_files);
void print_files_dir(const char* dir_path, int exsisting_files, bool is_hidden);
int count_exsisting_files(char* dir_path, bool is_hidden);
int traverse_dir_and_save(const char* cur_path, char** buffer);
char* full_path(char* d_name, char* path);
bool is_hidden(struct dirent* entry);
int is_directory(const char* path);

#endif // FILE_UTILS_H 


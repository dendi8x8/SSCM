/* file_utils.h header. 2025 */

#include "main_defines.h"
#include "default_headers.h"

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

int get_files_in_dir(char* dir_path, char** dst_buffer, bool is_hidden);
void print_files(char** dir_files, int exsiting_files);
void print_files_dir(const char* dir_path, int exsisting_files, bool is_hidden);
int count_exsisting_files(char* dir_path, bool is_hidden);

#endif // FILE_UTILS_H 


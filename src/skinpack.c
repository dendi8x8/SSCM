#include "include/default_headers.h"
#include "include/file_utils.h"
#include "include/skinpack.h"
#include "include/alloc.h"

/* function GET_SKINPACK_RELATIVE_PATH
   PURPOSE:
   get by full path in argument path relative path of root skinpack.
 */
void get_skinpack_relative_path(const char* path, char* skinpack_name, char* dst) {
  const char* sub_str = skinpack_name;
  const char* root_pos = strstr(path, sub_str);
  root_pos = root_pos + strlen(skinpack_name);
  
  printf("RELATIVE_ROOT_PATH: %s at pos %td\n", root_pos, root_pos - path);

  strcpy(dst, root_pos);
}

void create_skinpack_folder() {
  return;
}


/*
  
 */
int traverse_skinpack(char* path, char* skinpack_name, char* relative[], char* full[]) {
#define SCRIPT_FILES_MAX 32

  char* dst_path = malloc(strlen(path) + strlen("scripts"));
  strcpy(dst_path, path);
  strcat(dst_path, "/scripts");
  printf("%s\n", dst_path);

  if (!dst_path && !is_correct_dir(dst_path)) {
    perror("");
    return -1;
  }
  
  int file_count = traverse_dir_and_save(dst_path, full);
  puts("Files paths before:");
  print_files(full, file_count);

  for (int i = 0; i < file_count; i++) {
    get_skinpack_relative_path(full[i], skinpack_name, relative[i]);
  }

  puts("Files paths after:");
  print_files(relative, file_count);
  
  return file_count;
}

void move_skinpack_dir(char* dst, char* src, char* full_src) {
  char* result = malloc(PATH_MAX);

  char* full_dst_path = malloc(PATH_MAX);
  realpath(dst, full_dst_path);

  sprintf(result, "%s%s", full_dst_path, src);
  printf("dst: %s\n src: %s\n  res: %s\n", full_dst_path, src ,result);
  rename(full_src, result);
  
  
  free(full_dst_path);
  free(result);
}

void free_traversed_skinpacks(char** traversed_skinpacks) {
  dealloc_buf(traversed_skinpacks, SKINPACK_DIR_COUNT);
}

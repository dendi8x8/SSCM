#include "include/default_headers.h"
#include "include/file_utils.h"
#include "include/skinpack.h"
#include "include/alloc.h"

#include <sys/types.h>
#include <sys/stat.h>

/* function GET_SKIN_RELATIVE_PATH
   PURPOSE:
   get by full path in argument path relative path of root skinpack.
 */
char* get_skin_relative_path(const char* path, char* skinpack_name) {
  const char* sub_str = skinpack_name;
  const char* root_pos = strstr(path, sub_str);
  root_pos++; // Trim /
  root_pos = root_pos + strlen(skinpack_name);
  
  return strdup(root_pos);
}

/* #Todo: Write a documentation for this function.
  
 */
int traverse_skinpack(char* path, char* skinpack_name, char* relative[], char* full[]) {
#define SCRIPT_FILES_MAX 32

  char* dst_path = malloc(strlen(path) + NAME_MAX);
  strcpy(dst_path, path);
  strcat(dst_path, "");

  if (!dst_path && !is_correct_dir(dst_path)) {
    perror("");
    return -1;
  }
  
  int file_count = traverse_dir_and_save(dst_path, full, E_TRAVERSE_ALL, true);

  print_files(full, file_count);

  for (int i = 0; i < file_count; i++) {
    relative[i] = get_skin_relative_path(full[i], skinpack_name);
  }

  print_files(relative, file_count);
  
  return file_count;
}

/* #TODO: Write documentation for this function.

 */
void cp_skinpack_dir(char* dst, char* src_dir, const char* full_src) {
  char* result = malloc(PATH_MAX);
  char* full_dst = malloc(PATH_MAX);
  // TODO: Create optimizations by dynamic allocating memory.
  char buffer[MAX_FILE_BUF / 32];
  
  realpath(dst, full_dst);
  sprintf(result, "%s%s", full_dst, src_dir); // #TODO: Create universal concatenating function.

  // Create file* to src. file.
  FILE* src_file = fopen(full_src, "rb");
  if (!src_file) {
    perror("");
    fclose(src_file);
    free(result);
    free(full_dst);
    return;
  }
  // Creates file* to dst. file.
  FILE* dst_file = fopen(result, "wb");
  if(!dst_file) {
    perror("");
    fclose(dst_file);
    free(result);
    free(full_dst);
    return;
  }

  // Read src. file and copy it to the dst. file.
  size_t bytes = 0;
  while ((bytes = fread(buffer, 1, sizeof(buffer), src_file))) {
    fwrite(buffer, 1, sizeof(buffer), dst_file);
  }

  fclose(src_file);
  fclose(dst_file);
  free(full_dst);
  free(result);
}

/* LOCAL FUNCTION
   
 */
static void create_dir(const char* full_path, const char* dir[], const int count) {
  char** buf = malloc(sizeof(char*) * count);
  alloc_buf(buf, count, NAME_MAX);

  // Creates path to dir for creating it.
  for (int i = 0; i < count; i++) {
    sprintf(buf[i], "%s/%s", full_path, dir[i]);
  }
  // Makes dir with that absolute path.
  for (int i = 0; i < count; i++) {
    mkdir(buf[i], 0777);
  }

  dealloc_buf(buf, count);
}

char* rm_file_name(const char* path) {
  int len = strlen(path);
  int i = len;
  char new_path[len];
  strcpy(new_path, path);
  
  while (path[i--] != '/') {
    new_path[i] = 0;
  }
  
  return strdup(new_path);
}

char* get_subdir(const char* src_path, const char* src_root) {
  int root_len = strlen(src_root) + 1; // Skip /
  char* subdir_occ = strstr(src_path, src_root);
  
  return strdup(subdir_occ + root_len);
}

void cp_file(const char* dst_path, const char* src_path, const char* src_root) {
  FILE* dst_file = fopen(dst_path, "w");
  if (!dst_file) {
    perror("");
    fprintf(stderr, "dst_path: %s\n", dst_path);
    fclose(dst_file);
    return;
  }

  FILE* src_file = fopen(src_path, "r");
  if (!src_file) {
    perror("");
    fprintf(stderr, "src_path: %s\n", src_path);
    fclose(src_file);
    return;
  }

  char c;
  while (true) {
    c = fgetc(src_file);
    if(c == EOF) {
      break;
    }

    fputc(c, dst_file);
  }
  
  fclose(src_file);
  fclose(dst_file);
  return;
}


// #REFACTOR: Extract body to the functions for easy reading.
/* LOCAL FUNCTION

 */
void create_base_skinpack_dir(const char* sp_path, char* skinpack_name, const char* base_path) {
  // 1. Create base dirs in skinpack.
  char* base_dirs[MAX_FILES_SKINPACK];
  alloc_buf(base_dirs, MAX_FILES_SKINPACK, PATH_MAX);
  
  int base_dirs_count = traverse_dir_and_save(base_path, base_dirs, E_TRAVERSE_ONLY_DIRS, true); // Traversing only dirs!
  print_files(base_dirs, base_dirs_count);
  printf("buf[%d]: %s\n", 0, base_dirs[0]);
  printf("base_dirs_count: %d\n", base_dirs_count);

  // Copy this dirs
  char* result_paths[base_dirs_count];
  alloc_buf(result_paths, base_dirs_count, PATH_MAX);

  // trim full path.
  for (int i = 0; i < base_dirs_count; i++) {
    char* trim_str = get_skin_relative_path(base_dirs[i], base_path);
    sprintf(result_paths[i], "%s/%s", sp_path, trim_str);
  }

  // Make dir.
  for (int i = 0; i < base_dirs_count; i++) {
    mkdir(result_paths[i], 0777);
    printf("Created dir: %s\n", result_paths[i]);
  }
  
  dealloc_buf(result_paths, base_dirs_count);
  dealloc_buf(base_dirs, MAX_FILES_SKINPACK);
  // 2. Move files from base to resulting skinpack
     
  char* base_files[MAX_FILES_SKINPACK];
  alloc_buf(base_files, MAX_FILES_SKINPACK, PATH_MAX);

  char *files_full_paths[MAX_FILES_SKINPACK];
  int base_files_count = traverse_dir_and_save(base_path, base_files, E_TRAVERSE_ONLY_FILES, true);
  alloc_buf(files_full_paths, base_files_count, PATH_MAX);
  print_files(base_files, base_files_count);
  
  // trim full path.
  for (int i = 0; i < base_files_count; i++) {
    char* trim_str = get_skin_relative_path(base_files[i], base_path);
    printf("trim str %s\n", trim_str);
    sprintf(files_full_paths[i], "%s/%s", sp_path, trim_str);
    printf("res str: %s\n", files_full_paths[i]);
  }

  for (int i = 0; i < base_files_count; i++) {
    cp_file(files_full_paths[i], base_files[i], base_path);
    printf("created file at path: %s\n", files_full_paths[i]);
  }

  dealloc_buf(files_full_paths, base_files_count);
  dealloc_buf(base_files, MAX_FILES_SKINPACK);
}


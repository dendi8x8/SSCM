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
  root_pos++; // Trim slash(/)
  root_pos = root_pos + strlen(skinpack_name);
  
  return strdup(root_pos);
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

char* trim_full_path(char* base_dir, char* base_path, char* sp_path) {
  char* trim_str = get_skin_relative_path(base_dir, base_path);
  char res_path[PATH_MAX];
  sprintf(res_path, "%s/%s", sp_path, trim_str);
  return strdup(res_path);
}

// #REFACTOR: Extract body to the functions for easy reading.
/* LOCAL FUNCTION

 */
void create_base_skinpack_dir(const char* sp_path, char* skinpack_name, const char* base_path) {
  // 1. Traverse dirs
  char* base_dirs[MAX_FILES_SKINPACK];
  alloc_buf(base_dirs, MAX_FILES_SKINPACK, PATH_MAX);
  
  int base_dirs_count = traverse_dir_and_save(base_path, base_dirs, E_TRAVERSE_ONLY_DIRS, true); // Traversing only dirs!

  char* result_paths[base_dirs_count];
  alloc_buf(result_paths, base_dirs_count, PATH_MAX);

  for (int i = 0; i < base_dirs_count; i++) {
   result_paths[i] = trim_full_path(base_dirs[i], base_path, sp_path);
  }
  // Move traversed dirs
  for (int i = 0; i < base_dirs_count; i++) {
    mkdir(result_paths[i], 0777);
  }

  dealloc_buf(result_paths, base_dirs_count);
  dealloc_buf(base_dirs, MAX_FILES_SKINPACK);
  
  // 2. Move files from traversed dirs to resulting skinpack.
  char* base_files[MAX_FILES_SKINPACK];
  alloc_buf(base_files, MAX_FILES_SKINPACK, PATH_MAX);

  char *files_full_paths[MAX_FILES_SKINPACK];
  int base_files_count = traverse_dir_and_save(base_path, base_files, E_TRAVERSE_ONLY_FILES, true);
  alloc_buf(files_full_paths, base_files_count, PATH_MAX);
  print_files(base_files, base_files_count);

  for (int i = 0; i < base_files_count; i++) {
    files_full_paths[i] = trim_full_path(base_files[i], base_path, sp_path);
  }
  
  // 3. Copy traversed files to resulting skinpack.
  for (int i = 0; i < base_files_count; i++) {
    cp_file(files_full_paths[i], base_files[i], base_path);
    printf("created file at path: %s\n", files_full_paths[i]);
  }
  
  dealloc_buf(files_full_paths, base_files_count);
  dealloc_buf(base_files, MAX_FILES_SKINPACK);
}

static char* get_skinpack_dir(char* path) {
  printf("path %s\n", path);
  int len = strlen(path);

  int s_count = 0;
  int i = len;
  printf("len %d\n", len);

  while (i > 0) {
    if (s_count == 2) break;
    if (path[i] == '/') {
      s_count++;
      continue;
    }
    
    i--;
  }
  
  int pos = i + 1; // Trim slash /
  return strdup(path + pos);
}

void cp_skin(char* sp_path, char* base_path, char* skin_path) {
  if (!is_correct_dir(skin_path)) {
    fprintf(stderr, "err: %s %s\n", strerror(errno), skin_path);
    exit(errno);
  }
  
  char* subdir_path = "materials/models/weapons/v_models";
  char res_str[PATH_MAX];
  
  sprintf(res_str, "%s/%s/%s", sp_path, subdir_path, get_skinpack_dir(skin_path));
  printf("Res str: %s\n", res_str);
  
  cp_file(res_str, skin_path, base_path);
  printf("Copied %s to %s\n", res_str, sp_path);
}

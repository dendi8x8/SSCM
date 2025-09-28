#include <stdio.h>         // for input/output support and files creation
#include <stdlib.h>        // for standart lib functions
#include <stdbool.h>       // for true false support
#include <sys/stat.h>      // for mkdir syscall
#include <dirent.h>
#include <string.h>        // for string functions like strncpy
// Disable raylib loading for tui mvp
#if 0
#include "include/raylib.h"
#endif

#define MAX_FILES 1028
#define STRING_LEN 256

// Returns 1 if result is unsuccesfull
int get_files_in_dir(char* dir_path, char** dst_buffer, bool is_hidden) {
    DIR *dir;
    struct dirent *entry;
    
    dir = opendir(dir_path);
    if (!dir) {
      fprintf(stderr, "Can't get files in dir %s\n", dir_path);
      return 1;
    }

    int i = 0;
    char mod_string[STRING_LEN];
    while ((entry = readdir(dir)) != NULL) {
      if (!is_hidden && entry->d_name[0] == '.') continue;
      sprintf(mod_string, "%s/%s", dir_path, entry->d_name);
      strncpy(dst_buffer[i], mod_string, STRING_LEN);
      i++;
    }

    printf("\n");
    return 0;
}

int alloc_buf(char* buf[], int size) {
  if (!buf) return -1;
  for (int i = 0; i < size; i++) {
    buf[i] = malloc(STRING_LEN);
  }
}

int dealloc_buf(char* buf[], int size) {
 for (int i = 0; i < size; i++) {
     free(buf[i]);
  }
}
void print_files(char** dir_files, int exsiting_files) {
  for (int i = 0; i < exsiting_files; i++) {
    printf("Buffer[%d]: %s\n", i, dir_files[i]);
  }
  puts("");
}

int count_exsisting_files(char* dir_path, bool is_hidden) {
  int count = 0;
  struct dirent *entry;
  DIR* dir = opendir(dir_path);
    
  if (!dir) { //#TODO: Catch other errors, described at opendir man.
    fprintf(stderr, "Can't open dir at: %s\n", dir_path);
    return 1;
  }

  while((entry = readdir(dir)) != NULL) {
    if(!is_hidden && entry->d_name[0] == '.') continue;
    count++;
  }
  
  return count;
}

int main(void) {
  // First step for today: create skinpack copying to output directory with saved structure of skinpack
  const char* src_dir = "tests/dir_files";
  const char* dst_dir = "tests/out_dir";
  int exsisting_files = 0;
  bool is_hidden = false;
  char* dir_files[MAX_FILES];

  alloc_buf(dir_files, MAX_FILES);

  int result = get_files_in_dir(src_dir, dir_files, is_hidden);
  if (result == 1) {
    fprintf(stderr, "Can't get files in dir %s\n", src_dir);
  }
  
  exsisting_files = count_exsisting_files(src_dir, is_hidden);
  print_files(dir_files, exsisting_files);

  dealloc_buf(dir_files, MAX_FILES);
  return 0;
}

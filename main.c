#include <stdio.h>         // for input/output support and files creation
#include <stdlib.h>        // for standart lib functions 
#include <stdbool.h>       // for true false support
#include <sys/stat.h>      // for mkdir syscall
#include <dirent.h>

// Disable raylib loading for tui mvp
#if 0
#include "include/raylib.h"
#endif

// Returns 1 if result is unsuccesful
int get_files_in_dir(char* dir_path, char** dst_buffer, int size) {
    DIR *dir;
    struct dirent *entry;
    
    dir = opendir(dir_path);
    if (!dir) {
      fprintf(stderr, "Can't get files in dir %s\n", dir_path);
      return 1;
    }

    int i = 1;
    bool is_hidden_show = false; 
    while ((entry = readdir(dir)) != NULL) {
      if (!is_hidden_show && entry->d_name[0] == '.') continue;
      printf("Entry[%d] d_name: %s\n", i, entry->d_name);
      i++;
    }
    
    printf("\n");
    return 0;
}

int main(void) {
  // First step for today: create skinpack copying to output directory with saved structure of skinpack
  
  const char* src_dir = "tests/dir_files";
  const char* dst_dir = "tests/out_dir";

  char** dir_files = {};
  int result = get_files_in_dir(src_dir, NULL, 0);
  
  if (result == 1) {
    fprintf(stderr, "Can't get files in dir %s\n", src_dir);
  }
  
  return 0;
}


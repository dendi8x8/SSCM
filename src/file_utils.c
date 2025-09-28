/* file_utils.c file. 2025 */

//#include ""
#include "include/file_utils.h"

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


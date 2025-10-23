/* file_utils.c file. 2025 */

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
    closedir(dir);
    return 0;
}

bool is_directory(const char* path) {
  struct stat file_stat;
  stat(path, &file_stat);

  switch (file_stat.st_mode & S_IFMT) {
  case S_IFDIR:
    return true;
    break;
  case S_IFREG:
    return false;
    break;
  default:
    return false;
  }
}

bool is_exist(const char* path) {
  if (!opendir(path)) {
    return false;
  }
  
  return true;
}

bool is_hidden(struct dirent* entry) {
  if(entry->d_name[0] == '.') {
    return true;
  }
  
  return false;
}

bool is_file_exist(const char* path) {
  if (!fopen(path, "r")) {
    return false;
  }
  
  return true;
  
}

bool is_correct_dir(const char* path) {
  if (!is_exist(path)) {
    return false;
  }

  if (!is_directory(path)) {
    return false;
  }
  
  return true;
}

/* FUNCTION FULL_PATH
   PURPOSE:
   Getting full path of directory specified in 2 arguments (char*) d_name and (char*) path.

   RETURN VALUE:
   Returns non-zero value if unsucessfull
 */
static int full_path(char* d_name, char* path, char* dest) {
  char resolved_path[PATH_MAX] = {};
  
  realpath(path, resolved_path);
  sprintf(dest, "%s/%s", resolved_path, d_name);
  
  return 0;
}

/* FUNCTION
   PURPOSE: Return the count of files and/or(specified in 2 arg.) dir.
   RETURN: int
 */
int count_files(char* cur_path, bool count_dir) {
  DIR* dir = opendir(cur_path);
  if(!is_correct_dir(cur_path)) return -1;
  
  struct dirent* entry;
  static int file_count;
  char path_full[PATH_MAX] = {};
  char absolute_path[PATH_MAX];
  
  while(true) {
    entry = readdir(dir);
    if (entry == NULL) break;
    if (is_hidden(entry)) continue;

    full_path(entry->d_name, cur_path, path_full);

    if (is_correct_dir(path_full)) {
      if(count_dir) {
        file_count++;
      }
      count_files(path_full, count_dir);
    } else {
      file_count++;
    }
  }

  return file_count;
} 
 

/* FUNCTION TRAVERSE_DIR_AND_SAVE
   PURPOSE:
   Traverse file by path specified in (consts char*)cur_path and write entries to (char**)paths.
   DON'T COUNT THE ROOT DIR specified in (const char*)cur_path argument
   
   RETURN VALUE:
   Returns count of files in specifeid dir. Not including .. and . links in dirs.
 */
int traverse_dir_and_save(const char* cur_path, char** paths, int mode, bool reset) {
  DIR* dir = opendir(cur_path);
  struct dirent* entry;
  char path[PATH_MAX];
  char absolute_path[PATH_MAX];

  if (paths == NULL) return -1;
  
  static int i = 0;
  static int file_count = 0;
  static int dir_count = 0;
  if (reset) {
    i = 0;
    file_count = 0;
    dir_count = 0;
  }

  while (true) {
    entry = readdir(dir);
    if (entry == NULL) break;
    if (is_hidden(entry)) continue;

    // Get full path from current entry and cur_path and write it to path var.
    full_path(entry->d_name, cur_path, path);
    strcpy(absolute_path, path); // There copy this to absoulute_path.

    if (is_directory(absolute_path)) {
      if (mode == E_TRAVERSE_ONLY_DIRS || mode == E_TRAVERSE_ALL) {
        sprintf(paths[dir_count], "%s", absolute_path);
        dir_count++;
      }
      traverse_dir_and_save(absolute_path, paths, mode, false);
    } else {
      if (mode == E_TRAVERSE_ONLY_FILES || mode == E_TRAVERSE_ALL) {
        sprintf(paths[file_count], "%s", absolute_path);
        file_count++;
      }
    }
    
    if (mode == E_TRAVERSE_ALL) {
      sprintf(paths[i], "%s", absolute_path);
    }
    i++;
  }
  
  if (mode == E_TRAVERSE_ALL)        return i;
  if (mode == E_TRAVERSE_ONLY_FILES) return file_count;
  if (mode == E_TRAVERSE_ONLY_DIRS)  return dir_count;
  // ELSE:
  return -1;
}

void print_files(char** dir_files, int exsiting_files) {
  for (int i = 0; i <= exsiting_files - 1; i++) {
    printf("Buffer[%d]: %s\n", i, dir_files[i]);
  }
}

void print_files_dir(const char* dir_path, int exsisting_files, bool is_hidden) {
  struct dirent *entry;
  DIR* dir = opendir(dir_path);

  while ((entry = readdir(dir)) != NULL) {
    if (!is_hidden && entry->d_name[0] == '.') continue;
    printf("%s\n", entry->d_name);
  }
}

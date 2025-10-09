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

int is_directory(const char* path) {
    struct stat file_stat;
    stat(path, &file_stat);
    
    switch (file_stat.st_mode & S_IFMT) {
    case S_IFDIR:
	return true;
	break;
    case S_IFREG:
	return false;
	break;
    }
}

bool is_hidden(struct dirent* entry) {
  if(entry->d_name[0] == '.') {
    return true;
  }
  
  return false;
}

/* FUNCTION FULL_PATH
   PURPOSE:
   Getting full path of directory specified in 2 arguments (char*) d_name and (char*) path.

   RETURN VALUE:
   Returns non-zero value if unsucessfull
 */
int full_path(char* d_name, char* path, char* dest) {
  char resolved_path[PATH_MAX] = {};
  
  realpath(path, resolved_path);
  sprintf(dest, "%s/%s", resolved_path, d_name);
  
  return 0;
}

void free_path(char* str) {
  free(str);
}

/* FUNCTION TRAVERSE_DIR_AND_SAVE
   PURPOSE:
   Traverse file by path specified in (consts char*)cur_path and write entries to (char**)paths.

   RETURN VALUE:
   Returns count of files in specifeid dir. Not including .. and . links in dirs.
 */
int traverse_dir_and_save(const char* cur_path, char** paths) {
  DIR* dir = opendir(cur_path);
  struct dirent* entry;
  char path[PATH_MAX];
  char absolute_path[PATH_MAX];

  if(paths == NULL) return -1;

  static int i = 0;
  static int file_c = 0;


  while (true) {
    entry = readdir(dir);
    if (entry == NULL) break;
    if (is_hidden(entry)) continue;

    // Get full path from current entry and cur_path and write it to path var
    full_path(entry->d_name, cur_path, path);
    strcpy(absolute_path, path); // There copy this to absoulute_path
    
    if(is_directory(absolute_path)) {
      traverse_dir_and_save(absolute_path, paths);
    } else {
      // It's copy only files to buffer
      file_c++;
      sprintf(paths[i++], "%s", absolute_path);
    }
  }

  return file_c;
}

/* FUNCTION MOVE_FILES
   PURPOSE:
   Moving files specified in (char**) paths buffer by calling rename syscall.

   RETURN VALUE:
   Return non-zero value if unsucesfull
 */
int move_files(char** paths) {
  // Go through the paths arr and change paths dir to the destination dir.
  printf("NOT IMPLEMENTED\n");
  exit(0);
}

void print_files(char** dir_files, int exsiting_files) {
  for (int i = 0; i < exsiting_files - 1; i++) {
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

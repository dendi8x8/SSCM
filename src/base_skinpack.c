#include "include/default_headers.h"
#include <errno.h>
/*
  PURPOSE: Create base skinpack dir in specified dir.
  PARAMETRS:
  dir_path: specified dir where base skinpack will be created.
*/

#ifdef ENABLE_BASE_SKINPACK_FUNC
// #TODO: Check for allocation errors
base_struct* init_base_skinpack_struct() {
  base_struct *base;

  for (int i = 0; i < DIRS_COUNT; i++) {
    base + i = malloc(sizeof(base->models_d) * DIR_LENGTH_MAX); // It's alocating 16 bytes(char = 1 byte)

    
  }

  return base;
}
#endif

DIR* create_base_skinpack_dir(const char* dir_path) {
  DIR* dir;
  mode_t mode = 0775;
  
  int result = mkdir(dir_path, mode);
    if (!result) {
      fprintf(stderr, "Error in creating base skinpack dir at %s\n", dir_path);
  }
    
  dir = opendir(dir_path);
  if (!dir) {
    fprintf(stderr, "Error in opendir at %s", dir_path);
  }

  return dir;
}

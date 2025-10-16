/* MIT License

   SSCM - Skinpack Selection for Clientmode (Android).

   main.c: Main initializations and inits.
   
   Created by Daniel aka @dendi8x8 and Kirill aka @zSav1Xz.
   
   Copyright (c) 2025 Daniel and Kirill.
 */

/* SYTEM LIBRARIES in default_headers.h */
#include "include/default_headers.h"

/* EXTERNAL LIBRARIES */
// Disable raylib loading for tui mvp
#ifdef LIBRAYLIB_ON
#include "external_libs/raylib/include/raylib.h"
#endif

/* MAIN DEFINES */
#include "include/main_defines.h"

/* PROJECT HEADERS */
#include "include/file_utils.h"     // #TODO: Write documentation for functions in this header.
#include "include/skinpack.h"
#include "include/alloc.h"

/* FUNCTION INIT
   PURPOSE:
   Init main variables of project.
 */
void init() {
  return;
}


int main(int argc, char* argv[]) {
  init();
  // #TODO: Create init function for standart variables.
  const char default_dir[PATH_MAX]; // It's current working directory.
  getcwd(default_dir, PATH_MAX);
  
  int files_count = 0;
  char* files[MAX_FILES];
  
  alloc_buf(files, SKINPACK_DIR_COUNT, PATH_MAX);
  
  if (!is_correct_dir(default_dir)) {
    char* err_msg = strerror(errno);
    printf("err: %s: %s\n", default_dir, err_msg);
    return -1;
  }

  // #FIXME: Non constant array initializers.
  char* scripts_relative[32];
  char* scripts_full[32];
  int models_file_count = 0;
  
  alloc_buf(scripts_relative, 32, PATH_MAX);
  alloc_buf(scripts_full, 32, PATH_MAX);
  
  models_file_count = traverse_skinpack("resources/base", "base", scripts_relative, scripts_full);

  for (int i = 0; i < models_file_count; i++) {
    move_skinpack_dir("resources/out", scripts_relative[i], scripts_full[i]);
  }

  dealloc_buf(scripts_relative, 32); 
  dealloc_buf(scripts_full, 32);
  
  dealloc_buf(files, SKINPACK_DIR_COUNT);
  
  printf("ERRNO: %d\nErr: %s\n", errno, strerror(errno));
  return 0;
}

/*
  TODOES LIST for 2025-10-10:
  COUNT(6)
  15:Write documentation for file_utils.h.
  32:Write a tui path selection.
  32: Create init function for standart variables.
  39:Add check for errors.
  #TODO: Add absolute pathes initializion for correct work program outside building dirs
  #TODO: Add errno write to stderr in error handlers.
*/

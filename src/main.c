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
#include "include/alloc.h"
#include "include/file_utils.h"     // #TODO: Write documentation for functions in this header.
#include "include/skinpack.h"

/* FUNCTION INIT
   PURPOSE:
   Init main variables of project.
 */
int init(int argc, char* argv[]) {
  char test_dir_path[PATH_MAX] = {};
  
  if (argc <= 1) {
    test_dir_path[0] = '.';
  } else if (is_directory(argv[1])){
    strcpy(test_dir_path, argv[1]);
  } else {
    printf("Err: %s: not a directory!\n", argv[1]);
    return errno;
  }

  printf("Selected dir: %s\n", test_dir_path);
  create_base_skinpack_dir(test_dir_path, "");
  return 0;
}

int main(int argc, char* argv[]) {
  init(argc, argv);
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

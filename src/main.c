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
  
  if (argc < 2) {
    puts("No dir selected. Exiting...");
    return 2;
  } else if (is_directory(argv[1])){
    strcpy(test_dir_path, argv[1]);
  } else {
    printf("Err: %s: not a directory!\n", argv[1]);
    return errno;
  }

  char* base_dir_path = malloc(PATH_MAX);
  const char* base_dir_rel_path = "resources/base";

  if(!realpath(base_dir_rel_path, base_dir_path)) {
    fprintf(stderr, "err: %s %s\n", strerror(errno), base_dir_rel_path);
    return errno;
  }

  char skinpack_dir_path[strlen(argv[1])];
  
  if (!realpath(argv[1], skinpack_dir_path)) {
    fprintf(stderr, "err: %s %s\n", strerror(errno), argv[1]);
  }
  
  printf("Selected dir: %s\n", skinpack_dir_path);
  printf("Do you want continue?(y or n)");
  char c;

  scanf("%c", &c);
  if (c == 'y') {
    create_base_skinpack_dir(skinpack_dir_path, "", base_dir_path);  
  } else if (c == 'n') {
    puts("Canceling operation... Exiting..");
    return 0;
  } else {
    printf("Enter correct operation!\n");
  }

  
  free(base_dir_path);
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

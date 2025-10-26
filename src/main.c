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
    exit(ENOENT);
  } else if (is_directory(argv[1])){
    strcpy(test_dir_path, argv[1]);
  } else {
    printf("Err: %s: not a directory!\n", argv[1]);
    exit(errno);
  }

  // Create base dir path where storese a base strucutre of all skinpacks
  char* base_dir_path = malloc(PATH_MAX);
  const char* base_dir_rel_path = "resources/base";

  // Get full path to base dir
  if(!realpath(base_dir_rel_path, base_dir_path)) {
    fprintf(stderr, "err: %s %s\n", strerror(errno), base_dir_rel_path);
    exit(errno);
  }

  // Get full path of created skinpack_dir_path buffer
  char skinpack_dir_path[strlen(argv[1])];
  if (!realpath(argv[1], skinpack_dir_path)) {
    fprintf(stderr, "err: %s %s\n", strerror(errno), argv[1]);
    exit(errno);
  }

  printf("Selected dir: %s\n", skinpack_dir_path);
  printf("Do you want continue?(y or n)");

  char c;
  scanf("%c", &c);
  if (c == 'y') {
  } else if (c == 'n') {
    puts("Canceling operation... Exiting..");
    return EXIT_SUCCESS;
  } else {
    printf("Enter correct operation!\n");
    return EXIT_FAILURE;
  }

  // Create skinpack base, stores it path in skinpack_dir_path.
  //  create_base_skinpack_dir(skinpack_dir_path, "", base_dir_path);

  char* base_skins_path = "resources/skinpackSX/materials/models/weapons/v_models";
  char* base_skins_paths[MAX_FILES_SKINPACK];
  alloc_buf(base_skins_paths, MAX_FILES_SKINPACK, PATH_MAX);

  int base_skins_count = traverse_dir_and_save(base_skins_path, base_skins_paths, E_TRAVERSE_ONLY_DIRS, true);
  print_files(base_skins_paths, base_skins_count);

  const char* skins_subdir = "/materials/models/weapons/v_models";
  char* sp_path_subdired = malloc(strlen(skinpack_dir_path) + strlen(skins_subdir));
  
  strcpy(sp_path_subdired, skinpack_dir_path);
  strcat(sp_path_subdired, skins_subdir);

  if(!is_correct_dir(sp_path_subdired)) {
    fprintf(stderr, "err: %s %s\n", strerror(errno), sp_path_subdired);
    exit(ENOENT);
  }

  printf("base skins paths: %s\n", base_skins_paths[0]);
  printf("skinpath path: %s\n", sp_path_subdired);
  printf("base path: %s\n", base_skins_path);
  cp_skin(sp_path_subdired, base_skins_path, base_skins_paths[0], "out_skinpack");
  
  dealloc_buf(base_skins_paths, MAX_FILES_SKINPACK);
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

/* MIT License

   SSCM - Skinpack Selection for Clientmode (Android).

   main.c: Main initializations and inits.
   
   Created by Daniel aka @dendi8x8 and Kirill aka @zSav1Xz.
   
   Copyright (c) 2025 Daniel and Kirill.
 */

/* SYTEM LIBRARIES in default_headers.h */
#include "include/default_headers.h"

/* EXTERNAL LIBRARIES */
// Enabling raylib.

/* MAIN DEFINES */
#include "include/main_defines.h"
#include "include/menu.h"
/* PROJECT HEADERS */
#include "include/alloc.h"
#include "include/file_utils.h"
#include "include/skinpack.h"
/* GUI RAYLIB */
#include "include/menu.h"

/* FUNCTION INIT
   PURPOSE:
   Init a project.
 */
int init(int argc, char* argv[]) {
  int result = Init_Menu(argc, argv);
  if (result < 0) {
    fprintf(stderr, "Failed to init gui.\nErrno: %s(%d)\n", strerror(errno), errno);
  }
  
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

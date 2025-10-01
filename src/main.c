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
#include "include/base_skinpack.h" // Empty header file.

int alloc_buf(char* buf[], int size) {
  if (!buf) return -1;
  for (int i = 0; i < size; i++) {
    buf[i] = malloc(STRING_LEN);
  }
}

int dealloc_buf(char* buf[], int size) {
 for (int i = 0; i < size; i++) {
     free(buf[i]);
  }
}

int main(void) {
  // #TODO: Create init function for standart variables.
  const char* src_dir = "dir_files"; // #TODO: Add tui path selection
  const char* dst_dir = "tests/out_dir";
  const char* base_skinpack_dir = "resources/skinpack_base";
  int exsisting_files = 0;
  bool is_hidden = false;
  char* dir_files[MAX_FILES];

  create_base_skinpack_dir(base_skinpack_dir);
  print_files_dir(base_skinpack_dir, exsisting_files, is_hidden);
  return 0;
}


/*
  TODOES LIST for 2025-10-1:
  COUNT(6)
  15:Write documentation for file_utils.h.
  32:Write a tui path selection.
  32: Create init function for standart variables.
  39:Add check for errors.
  #TODO: Add absolute pathes initializion for correct work program outside building dirs
  #TODO: Add errno write to stderr in error handlers.
  
*/

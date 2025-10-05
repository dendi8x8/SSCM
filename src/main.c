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
  const char* test_dir = "resources/test"; // #TODO: Add tui path selection
  const char* base_skinpack_dir = "resources/base_skinpack";
  
  int exsisting_files = 0;
  bool is_hidden = false;
  char* files[MAX_FILES];
  alloc_buf(files, PATH_MAX);

  if (!opendir(test_dir)) {
    perror("");
    fprintf(stderr, "%s\n", test_dir);
    return -1;
  }
  traverse_dir_and_save(test_dir, files);

  //exsisting_files = count_exsisting_files(test_dir, false);
  print_files(files, 4);
  
  dealloc_buf(files, PATH_MAX);
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

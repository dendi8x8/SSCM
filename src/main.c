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

int main(int argc, char* argv[]) {
  // #TODO: Create init function for standart variables.
  const char* default_dir = "."; // #TODO: Add tui path selection
  
  int files_count = 0;
  bool is_hidden = false;
  char* files[MAX_FILES];
  
  alloc_buf(files, PATH_MAX);

  if (!opendir(default_dir)) {
    perror("");
    fprintf(stderr, "%s\n", default_dir);
    return -1;
  }

  if(argc <= 1) {
    files_count = traverse_dir_and_save(default_dir, files);
  } else {
    files_count = traverse_dir_and_save(argv[1], files);
  }

  print_files(files, files_count);
  
  dealloc_buf(files, PATH_MAX);
  
  return 0;
}


/*
  TODOES LIST for 2025-10-7:
  COUNT(6)
  15:Write documentation for file_utils.h.
  32:Write a tui path selection.
  32: Create init function for standart variables.
  39:Add check for errors.
  #TODO: Add absolute pathes initializion for correct work program outside building dirs
  #TODO: Add errno write to stderr in error handlers.
*/

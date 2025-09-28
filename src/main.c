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
  // First step for today: create skinpack copying to output directory with saved structure of skinpack [no]
  const char* src_dir = "tests/dir_files";
  const char* dst_dir = "tests/out_dir";
  int exsisting_files = 0;
  bool is_hidden = false;
  char* dir_files[MAX_FILES];

  alloc_buf(dir_files, MAX_FILES); // #TODO: Add check for errors

  int result = get_files_in_dir(src_dir, dir_files, is_hidden);
  if (result == 1) {
    fprintf(stderr, "Can't get files in dir %s\n", src_dir);
  }
  
  exsisting_files = count_exsisting_files(src_dir, is_hidden);
  print_files(dir_files, exsisting_files);

  dealloc_buf(dir_files, MAX_FILES);
  return 0;
}

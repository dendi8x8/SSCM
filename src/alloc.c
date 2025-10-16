#include <stdlib.h>

void alloc_buf(char* buf[], int size, int cap) {
  for (int i = 0; i < size; i++) {
    buf[i] = malloc(cap);
  }
}

void dealloc_buf(char* buf[], int size) {
  for (int i = 0; i < size; i++) {
    free(buf[i]);
  }
}

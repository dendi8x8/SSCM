/*
  alloc.h header.
  
  Copyright (c) 2025 Daniel and Kirill.
 */

#ifndef ALLOC_H
#define ALLOC_H

void alloc_buf(char* buf[], int size, int cap);
void dealloc_buf(char* buf[], int size);

#endif // ALLOC_H

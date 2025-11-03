/*
  menu.h header.
  
  Copyright (c) 2025 Daniel and Kirill.
*/

#include "default_headers.h"

#define LIBRAYLIB_ON
#ifdef LIBRAYLIB_ON
#include "raylib.h"
#endif

#ifndef MENU_H
#define MENU_H

#define BG_COLOR     WHITE
#define TEXT_COLOR   PURPLE
#define BUTON_COLOR  DARKPURPLE

int Init_Menu(int argc, char* argv[]);

#endif /* MENU_H */

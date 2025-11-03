/*
  base_skinpack.h

  provides functions for working with skinpack dir and manipulate with it.

  Copyright (c) 2025 Daniel and Kirill.
 */ 

#ifndef BASE_SKINPACK_H
#define BASE_SKINPACK_H

typedef struct Array {
  void* arr;
  size_t size;
} Array;

typedef struct String {
  char* str;
  size_t len;
  size_t cap;
} String;

typedef struct Skin {
  String* gun_type;
  String* gun_name;
  String* skin_name;
  String* path;
} Skin;

typedef struct skins {
  struct Skin* skins_arr;
  size_t count;
} Skins_Collection;

enum CATEGORY_TYPE {
  bladed_weapon,
  pistol,
  submachine_gun,
  rifle,
  sniper_rifle,
  shoutgun
};

#define SKINPACK_DIR_COUNT 5
#define MAX_SKINS_FILES 10
#define MAX_FILE_BUF 64000
#define MAX_FILES_SKINPACK 2500
#define TYPES_COUNT 6
#define MAX_SKIN_NAME_LEN 64

char*             get_skin_relative_path(const char* path, char* skinpack_name);
void              create_base_skinpack_dir(const char* path, char* skinpack_name, const char* base_path);
void              cp_skinpack_dir(char* path, char* src_dir, const char* full_src);
void              cp_skin(char* sp_path, char* base_path, char* skin_name, char* skinpack_name);
Skins_Collection* Init_SkinsCollection(size_t count);
void              Destroy_SkinsCollection(Skins_Collection* skins);
String*           Create_String(char* str);
void              Clear_String(String* s);
int               Parse_Skins(Skins_Collection* skins, char** paths, char* base_path);
void              Print_Skins(Skins_Collection* skins);
  
#endif // BASE_SKINPACK_H


#include "include/default_headers.h"
#include "include/file_utils.h"
#include "include/skinpack.h"
#include "include/alloc.h"

// TODO: Create a .ini file for configs or any other external file, not in the code.
static const char models_paths[3][PATH_MAX] = {
  "models/",
  "models/weapons"
};

static const char scripts_paths[1][PATH_MAX] = {
  "scripts/"
};

static const char sound_paths[64][PATH_MAX] = {
  "weapons/",
  "weapons/ak47",
  "weapons/aug",
  "weapons/awp",
  "weapons/bizon",
  "weapons/bknife",
  "weapons/c4",
  "weapons/cz_75",
  "weapons/cz75a",
  "weapons/deagle",
  "weapons/decoy",
  "weapons/elite",
  "weapons/famas",
  "weapons/fists",
  "weapons/fiveseven",
  "weapons/flashbang",
  "weapons/fx",
  "weapons/fx/nearmiss",
  "weapons/fx/rics",
  "weapons/fx/tink"
  "weapons/g3sg1",
  "weapons/galilar",
  "weapons/glock18",
  "weapons/he",
  "weapons/hegrenade",
  "weapons/hkp2000",
  "weapons/incgrenade",
  "weapons/knife",
  "weapons/knife_bowie",
  "weapons/knife_falchion",
  "weapons/knife_gypsy",
  "weapons/knife_push",
  "weapons/knife_stilletof",
  "weapons/knife_ursus",
  "weapons/knife_window",
  "weapons/m4a1",
  "weapons/m4a4",
  "weapons/m249",
  "weapons/mac10",
  "weapons/mag7",
  "weapons/molotov",
  "weapons/mp5",
  "weapons/mp5sd",
  "weapons/mp7",
  "weapons/mp9",
  "weapons/negev",
  "weapons/nova",
  "weapons/p90",
  "weapons/p250",
  "weapons/p2000",
  "weapons/revolver",
  "weapons/sawedoff",
  "weapons/scar20",
  "weapons/sg553",
  "weapons/sg556",
  "weapons/smoke",
  "weapons/smokegrenade",
  "weapons/ssg08",
  "weapons/tec9",
  "weapons/ump45",
  "weapons/usp",
  "weapons/xm1014",
  "weapons/zeus"
};


/* function GET_SKINPACK_RELATIVE_PATH
   PURPOSE:
   get by full path in argument path relative path of root skinpack.
 */
void get_skinpack_relative_path(const char* path, char* skinpack_name, char* dst) {
  const char* sub_str = skinpack_name;
  const char* root_pos = strstr(path, sub_str);
  root_pos = root_pos + strlen(skinpack_name);
  strcpy(dst, root_pos);
}

/* #Todo: Write a documentation for this function.
  
 */
int traverse_skinpack(char* path, char* skinpack_name, char* relative[], char* full[]) {
#define SCRIPT_FILES_MAX 32

  char* dst_path = malloc(strlen(path) + strlen("scripts"));
  strcpy(dst_path, path);
  strcat(dst_path, "/scripts");

  if (!dst_path && !is_correct_dir(dst_path)) {
    perror("");
    return -1;
  }
  
  int file_count = traverse_dir_and_save(dst_path, full);
  print_files(full, file_count);

  for (int i = 0; i < file_count; i++) {
    get_skinpack_relative_path(full[i], skinpack_name, relative[i]);
  }

  print_files(relative, file_count);
  
  return file_count;
}

void cp_skinpack_dir(char* dst, char* src, char* full_src) {
  char* result = malloc(PATH_MAX);
  char* full_dst = malloc(PATH_MAX);
  // TODO: Create optimizations by dynamic allocating memory.
  char buffer[MAX_FILE_BUF / 32];
  
  realpath(dst, full_dst);
  sprintf(result, "%s%s", full_dst, src);

  FILE* src_file = fopen(full_src, "rb");
  if (!src_file) {
    perror("");
    fclose(src_file);
    return;
  }

  FILE* dst_file = fopen(result, "wb");
  if(!dst_file) {
    perror("");
    fclose(dst_file);
    return;
  }
  
  size_t bytes = 0;
  while ((bytes = fread(buffer, 1, sizeof(buffer), src_file))) {
    fwrite(buffer, 1, sizeof(buffer), dst_file);
  }

  fclose(src_file);
  fclose(dst_file);
  free(full_dst);
  free(result);
}

void create_base_skinpack_dir(char* path, char* skinpack_name) {
#if 0
  struct skinpack* base;
  sprintf("%s%s", path, );
  traverse_skinpack()
#endif
}


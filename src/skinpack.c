#include "include/default_headers.h"
#include "include/file_utils.h"
#include "include/skinpack.h"
#include "include/alloc.h"

#include <sys/types.h>
#include <sys/stat.h>

// TODO: Create a .ini file for configs or any other external file, not in the code.
#define MODELS_PATHS_SIZE 2
#define DIR_TYPE_MODELS 1
static const char* Models_Paths[MODELS_PATHS_SIZE] = {
  "models/",
  "models/weapons"
};

#define SCRIPTS_PATHS_SIZE 1
#define DIR_TYPE_SCRIPTS 2
static const char* Scripts_Paths[SCRIPTS_PATHS_SIZE] = {
  "scripts/"
};

#define SOUND_PATHS_SIZE 63
#define DIR_TYPE_SOUND 3
static const char* Sound_Paths[SOUND_PATHS_SIZE] = {
  "sound/",
  "sound/weapons/",
  // After this dirs to fill:
  "sound/weapons/ak47",
  "sound/weapons/aug",
  "sound/weapons/awp",
  "sound/weapons/bizon",
  "sound/weapons/bknife",
  "sound/weapons/c4",
  "sound/weapons/cz_75",
  "sound/weapons/cz75a",
  "sound/weapons/deagle",
  "sound/weapons/decoy",
  "sound/weapons/elite",
  "sound/weapons/famas",
  "sound/weapons/fists",
  "sound/weapons/fiveseven",
  "sound/weapons/flashbang",
  "sound/weapons/fx",
  "sound/weapons/fx/nearmiss",
  "sound/weapons/fx/rics",
  "sound/weapons/fx/tink"
  "sound/weapons/g3sg1",
  "sound/weapons/galilar",
  "sound/weapons/glock18",
  "sound/weapons/he",
  "sound/weapons/hegrenade",
  "sound/weapons/hkp2000",
  "sound/weapons/incgrenade",
  "sound/weapons/knife",
  "sound/weapons/knife_bowie",
  "sound/weapons/knife_falchion",
  "sound/weapons/knife_gypsy",
  "sound/weapons/knife_push",
  "sound/weapons/knife_stilletof",
  "sound/weapons/knife_ursus",
  "sound/weapons/knife_window",
  "sound/weapons/m4a1",
  "sound/weapons/m4a4",
  "sound/weapons/m249",
  "sound/weapons/mac10",
  "sound/weapons/mag7",
  "sound/weapons/molotov",
  "sound/weapons/mp5",
  "sound/weapons/mp5sd",
  "sound/weapons/mp7",
  "sound/weapons/mp9",
  "sound/weapons/negev",
  "sound/weapons/nova",
  "sound/weapons/p90",
  "sound/weapons/p250",
  "sound/weapons/p2000",
  "sound/weapons/revolver",
  "sound/weapons/sawedoff",
  "sound/weapons/scar20",
  "sound/weapons/sg553",
  "sound/weapons/sg556",
  "sound/weapons/smoke",
  "sound/weapons/smokegrenade",
  "sound/weapons/ssg08",
  "sound/weapons/tec9",
  "sound/weapons/ump45",
  "sound/weapons/usp",
  "sound/weapons/xm1014",
  "sound/weapons/zeus"
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

/* #TODO: Write documentation for this function.

 */
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
    free(result);
    free(full_dst);
    return;
  }

  FILE* dst_file = fopen(result, "wb");
  if(!dst_file) {
    perror("");
    fclose(dst_file);
    free(result);
    free(full_dst);
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

/* LOCAL FUNCTION
   
 */
static void create_dir(const char* full_path, const char* dir[], int count) {
  char** buf = malloc(sizeof(char*) * count);
  alloc_buf(buf, count, 256);
  
  for (int i = 0; i < count; i++) {
    sprintf(buf[i], "%s/%s", full_path, dir[i]);
  }

  for (int i = 0; i < count; i++) {
    mkdir(buf[i], 0777);
  }

  if(!buf) return;
  dealloc_buf(buf, count);
}

enum E_DIR_TYPE {
  DP_MODELS,
  DP_SCRIPTS,
  DP_SOUND
};

/* LOCAL FUNCTION

 */
static void fill_dir(const char* sp_path, const char* base_path, int dir_type, int count) {
  char res_str[NAME_MAX];
  switch (dir_type) {
  case DP_MODELS:
    sprintf(res_str, "%s/%s", base_path, "models/weapons");
    break;
  case DP_SCRIPTS:
    sprintf(res_str, "%s/%s", base_path, "scripts");
    break;
  case DP_SOUND:
    sprintf(res_str, "%s/%s", base_path, "sound");
    break;
  default:
    fprintf(stderr, "Error: unknown dir type: %d", dir_type);
    return;
  }

  const int base_count = count_files(res_str, false);
  char *paths[base_count];
  alloc_buf(paths, base_count, PATH_MAX / 8);

  traverse_dir_and_save(res_str, paths);

  dealloc_buf(paths, base_count);
}

void create_base_skinpack_dir(const char* path, char* skinpack_name) {
  char full_path[PATH_MAX];
  realpath(path, full_path);
  
  printf("full_path: %s\n", full_path);
  create_dir(full_path, Sound_Paths, SOUND_PATHS_SIZE);         // Create sounds dir
  create_dir(full_path, Scripts_Paths, SCRIPTS_PATHS_SIZE);     // Create scripts dir
  create_dir(full_path, Models_Paths, MODELS_PATHS_SIZE);       // Create models dir

  int files_count = count_files(strdup("resources/sp_base/sound/weapons"), false);
  printf("files_count: %d\n", files_count);
  fill_dir(path, "resources/sp_base", DP_SOUND, files_count);
}


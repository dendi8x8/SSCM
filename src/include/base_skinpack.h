#define DIR_LENGTH_MAX 16
#define DIRS_COUNT 3

typedef struct base_skinpack_struct_t {
  char *models_d[DIR_LENGTH_MAX];
  char *scripts_d[DIR_LENGTH_MAX];
  char *sound_d[DIR_LENGTH_MAX];
} base_struct;

DIR* create_base_skinpack_dir(const char* dir_path);

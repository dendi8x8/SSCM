#include "include/menu.h"
#include "include/file_utils.h"
#include "include/skinpack.h"

int Init_Menu(int argc, char* argv[]) {
  const int screenWidth = 800;
  const int screenHeight = 450;
  
  InitWindow(screenWidth, screenHeight, "SSCM - Skinpack selection for clientmod.");
  SetTargetFPS(60);

  // 0) Init paths variables.
  const char* skins_base_path = "resources/skins_base";
  const char* skins_dir = "resources/skins_base/weapons";
  const char* icons_dir = "resources/skins_base/icons";
  
  printf("result icon path: %s\n", icons_dir);
  printf("result weapons path: %s\n", skins_dir);
  
  char* skins[MAX_FILES_SKINPACK];
  alloc_buf(skins, MAX_FILES_SKINPACK, PATH_MAX);
  
  int paths_count = traverse_dir_and_save(skins_dir, skins, E_TRAVERSE_ONLY_DIRS, true);
  puts("-------------");
  print_files(skins, paths_count);
  puts("-------------");
  // Skins_Collection struct filling
  Skins_Collection* skins_t;
  skins_t = Init_SkinsCollection(paths_count);

  printf("count: %ld\n", skins_t->count);
  
  int skins_count = Parse_Skins(skins_t, skins, skins_base_path);
  printf("SKINS COUNT: %d\n", skins_count);
  
  puts("There\n");
  // Main game loop
  while (!WindowShouldClose()) {
    // Update
    
    // Draw
    BeginDrawing();
      ClearBackground(BG_COLOR);

      // Draw skins
      for (int i = 0; i < skins_count; i++) {
        DrawText(skins_t->skins_arr[i].skin_name->str, 20, 40 + (i * 20), 20, TEXT_COLOR);
      }
    EndDrawing();
  }
  
  Destroy_SkinsCollection(skins_t);
  dealloc_buf(skins, MAX_FILES_SKINPACK);
  
  CloseWindow();        // Close window and OpenGL context
  return 0;
}

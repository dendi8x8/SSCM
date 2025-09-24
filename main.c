#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/raylib.h"

int main(void) {
  int width, height;
  width = 750;
  height = 500;
  
  InitWindow(width, height, "SSCM");
  SetTargetFPS(60);

  double time_from_launch = 0;

  while(time_from_launch < 10) {
    time_from_launch = GetTime();
    printf("Window is running: %lf\n seconds", time_from_launch);
  }
  
  CloseWindow();
  return 0;
}

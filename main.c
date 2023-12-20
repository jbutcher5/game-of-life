#include <stdbool.h>
#include "src/field.h"

int main(void) {
  const int screenWidth = 960;
  const int screenHeight = 540;

  InitWindow(screenWidth, screenHeight, "Conway's Game of Life");

  SetTargetFPS(60);

  static bool buffer[BUFF_SIZE];

  while (!WindowShouldClose()) {
    PaintCell((bool*)buffer);
    BeginDrawing();
    ClearBackground(BLACK);
    RenderBuffer((bool*)buffer);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

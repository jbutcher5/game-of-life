#include <stdbool.h>
#include "src/field.h"

int main(void) {
  // Init window
  
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Conway's Game of Life");
  SetTargetFPS(60);
  
  static bool buffer[BUFF_SIZE];

  while (!WindowShouldClose()) {
    // Check for mouse down on a cell

    PaintCell((bool*)buffer);

    // Render game
    
    BeginDrawing();
    ClearBackground(BLACK);
    RenderBuffer((bool*)buffer);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

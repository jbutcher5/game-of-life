#include "src/field.h"
#include "src/game.h"
#include <raylib.h>

int main(void) {
  // Init window
  
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Conway's Game of Life");
  SetTargetFPS(60);
  
  bool *buffer = RequestBuffer();
  GameState state = Editing;
  double last_update = 0;
  
  while (!WindowShouldClose()) {
    double time = GetTime();
    
    // Check for mouse down on a cell

    if (state == Editing)
      PaintCell((bool*)buffer);
    else if (state == Running && time - last_update >= 0.2) {
      buffer = UpdateCells(buffer);
      last_update = time;
    }

    if (IsKeyPressed(KEY_P) && state != Running)
      state = Running;
    else if (IsKeyPressed(KEY_P))
      state = Paused;
    
    // Render game
    
    BeginDrawing();
    ClearBackground(BLACK);
    RenderBuffer((bool*)buffer);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

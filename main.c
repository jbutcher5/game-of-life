#include "src/field.h"
#include "src/game.h"
#include "src/menu.h"
#include <raylib.h>
#include <omp.h>

#define MAX_THREADS 4

int main(void) {
  omp_set_num_teams(MAX_THREADS);

  // Init window
  
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Conway's Game of Life");
  SetTargetFPS(60);


  // Main Menu

  Component menu_components[] = {{(Vector2){10, 10}, (Vector2){100, 40}, (void*)"Test", Label}};
  Menu main_menu = {menu_components, 1, (Vector2){0, 0}, (Vector2){100, 40}};

  bool *buffer = RequestBuffer();
  GameState state = Editing;
  double last_update = 0;
  
  while (!WindowShouldClose()) {
    double time = GetTime();
    
    // Check for mouse down on a cell

    if (IsKeyDown(KEY_G))
      RenderMenu(main_menu);
    
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

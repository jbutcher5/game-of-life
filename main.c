#include "src/field.h"
#include "src/game.h"
#include "src/menu.h"
#include "src/menu_config.h"

#include <stdio.h>
#include <raylib.h>
#include <omp.h>

#define MAX_THREADS 4

int main(void) {
  omp_set_num_teams(MAX_THREADS);

  // Init window
  
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Conway's Game of Life");
  SetTargetFPS(60);
  SetExitKey(-1);

  // Main Menu

  Menu main_menu = {menu_components, 10, (Vector2){50, 50}, (Vector2){400, 300}};
  bool main_menu_open = false;

  Menu control_bar = {control_bar_components, 4, (Vector2){80, 0}, (Vector2){100, 30}};

  bool *buffer = RequestBuffer();
  GameState state = Editing;

  double update_delta = 0.2;
  double last_update = 0;

  Context ctx = {buffer, &state, &update_delta};
  
  while (!WindowShouldClose()) {
    double time = GetTime();
    snprintf(update_buffer_insert, 8, "%f", update_delta);

    // Check for mouse down on a cell

    if (IsKeyPressed(KEY_ESCAPE))
      main_menu_open = !main_menu_open;
    
    if (state == Editing && !main_menu_open)
      PaintCell((bool*)buffer);
    else if (state == Running && time - last_update >= update_delta && !main_menu_open) {
      buffer = UpdateCells(buffer);
      last_update = time;
    }

    // Render game
    
    BeginDrawing();
    ClearBackground(BLACK);
    RenderBuffer((bool*)buffer);
    RenderMenu(control_bar);

    if (main_menu_open) {
      UpdateMenu(&main_menu, ctx);
      RenderMenu(main_menu);
    } else {
      UpdateMenu(&control_bar, ctx);
    }
    
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

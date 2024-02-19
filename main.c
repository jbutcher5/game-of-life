#include "src/field.h"
#include "src/game.h"
#include "src/menu.h"
#include "src/button_funcs.h"

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

  ButtonContent reset_button = {reset, "Reset"};
  ButtonContent fullscreen_button = {toggle_window_size, "Fullscreen"};
  
  Component menu_components[] = {
    {(Vector2){10, 20}, (Vector2){50, 40}, (void*)"Reset Field:", Label},
    {(Vector2){100, 5}, (Vector2){60, 40}, &reset_button, Button},
    {(Vector2){100, 55}, (Vector2){60, 40}, &fullscreen_button, Button}
  };
  Menu main_menu = {menu_components, 3, (Vector2){50, 50}, (Vector2){300, 300}};
  bool main_menu_open = false;

  bool *buffer = RequestBuffer();
  GameState state = Editing;
  double last_update = 0;

  Context ctx = {&buffer, &state};
  
  while (!WindowShouldClose()) {
    double time = GetTime();
    
    // Check for mouse down on a cell

    if (IsKeyPressed(KEY_ESCAPE))
      main_menu_open = !main_menu_open;
    
    if (state == Editing && !main_menu_open)
      PaintCell((bool*)buffer);
    else if (state == Running && time - last_update >= 0.2 && !main_menu_open) {
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
    if (main_menu_open) {
      UpdateMenu(&main_menu, ctx);
      RenderMenu(main_menu);
    }
     EndDrawing();
  }

  CloseWindow();

  return 0;
}

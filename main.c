#include "src/field.h"
#include "src/game.h"
#include "src/menu.h"
#include <raylib.h>
#include <omp.h>

#include <stdio.h>

#define MAX_THREADS 4

#pragma clang diagnostic ignored "-Wunused-parameter"

void test_func(Context _) {
  puts("Hello!");
}

int main(void) {
  omp_set_num_teams(MAX_THREADS);

  // Init window
  
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Conway's Game of Life");
  SetTargetFPS(60);

  // Main Menu

  ButtonContent test_button = {test_func, "Click Me!"};
  
  Component menu_components[] = {
    {(Vector2){5, 30}, (Vector2){50, 40}, (void*)"Test:", Label},
    {(Vector2){50, 5}, (Vector2){50, 40}, &test_button, Button}
  };
  Menu main_menu = {menu_components, 2, (Vector2){50, 50}, (Vector2){200, 80}};

  bool *buffer = RequestBuffer();
  GameState state = Editing;
  double last_update = 0;

  Context ctx = {buffer, &state};
  
  while (!WindowShouldClose()) {
    double time = GetTime();
    
    // Check for mouse down on a cell

    if (IsKeyDown(KEY_G))
      UpdateMenu(&main_menu, ctx);
    
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
    if (IsKeyDown(KEY_G))
      RenderMenu(main_menu);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

#include "raylib.h"
#include "stdbool.h"

#define SCALE 1
#define BUFF_WIDTH 1000
#define BUFF_HEIGHT 1000
#define BUFF_SIZE BUFF_WIDTH * BUFF_HEIGHT

static inline Vector2 CellScreenPosition(int n) {
  return (Vector2){.x = (n % 1000)*10*SCALE, .y = (int)(n / 1000)*10*SCALE};
}

static inline int BufferIndex(float x, float y) {
  return x/(10 * SCALE) + (int)(y/(10 * SCALE))*1000;  
}

void RenderBuffer(bool *buffer) {
  for (int i = 0; i < BUFF_SIZE; i++)
    if (buffer[i]) {
      Vector2 pos = CellScreenPosition(i);
      DrawRectangle(pos.x, pos.y, 8 * SCALE, 8 * SCALE, RAYWHITE);
    }
}

void PaintCell(bool *buffer) {
  static int last_index = -1;
  
  Vector2 pos = GetMousePosition();
  int index = BufferIndex(pos.x, pos.y);

  if (IsMouseButtonDown(0) && index != last_index) {
    last_index = index; 
    buffer[index] = !buffer[index];
  }
}

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

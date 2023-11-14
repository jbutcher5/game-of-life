#include "raylib.h"
#include "stdbool.h"

#include "stdio.h"

#define SCALE 1
#define BUFF_WIDTH 1000
#define BUFF_HEIGHT 1000
#define BUFF_SIZE BUFF_WIDTH * BUFF_HEIGHT

static inline Vector2 CellScreenPosition(int n) {
  return (Vector2){.x = (n % 1000)*10*SCALE, .y = (int)(n / 1000)*10*SCALE};
}

static inline int BufferIndex(float x, float y) {
  printf("y: %f\n", ((y * BUFF_WIDTH) / (10 * SCALE)));
  return (int)(x + (y * 960))/(10 * SCALE);  
}

void RenderBuffer(bool *buffer) {
  for (int i = 0; i < BUFF_SIZE; i++)
    if (buffer[i]) {
      Vector2 pos = CellScreenPosition(i);
      DrawRectangle(pos.x, pos.y, 8 * SCALE, 8 * SCALE, RAYWHITE);
    }
}

void PaintCell(bool *buffer) {
  Vector2 pos = GetMousePosition();
  int index = BufferIndex(pos.x, pos.y);

  printf("%f %f (%d)\n", pos.x, pos.y, index);
  
  if (IsMouseButtonDown(1))
    buffer[index] = !buffer[index];
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

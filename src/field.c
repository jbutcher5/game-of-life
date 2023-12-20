#include "field.h"

Vector2 CellScreenPosition(int n) {
  return (Vector2){.x = (n % 1000)*10*SCALE, .y = (int)(n / 1000)*10*SCALE};
}

int BufferIndex(float x, float y) {
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

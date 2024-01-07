#include "field.h"

Vector2 CellScreenPosition(int n) {
  // Convert buffer indexes to screen positions
  return (Vector2){.x = (n % 1000)*10*SCALE, .y = (int)(n / 1000)*10*SCALE};
}

int BufferIndex(float x, float y) {
  // Check if position is out-of-bounds 
  if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
    return -1;
  
  // Convert screen positions to buffer indexes
  return x/(10 * SCALE) + (int)(y/(10 * SCALE))*1000;  
}

void RenderBuffer(bool *buffer) {
  // Iterate throught the buffer and render each active cell
  for (int i = 0; i < BUFF_SIZE; i++)
    if (buffer[i]) {
      Vector2 pos = CellScreenPosition(i);
      DrawRectangle(pos.x, pos.y, 8 * SCALE, 8 * SCALE, RAYWHITE);
    }
}

void PaintCell(bool *buffer) {
  static int last_index = -1;

  // Get the index the mouse is over
  
  Vector2 pos = GetMousePosition();
  int index = BufferIndex(pos.x, pos.y);

  // If left mouse button is down and it's not
  // the same as the last index invert it's state
  
  if (IsMouseButtonDown(0) && index != last_index) {
    last_index = index; 
    buffer[index] = !buffer[index];
  }
}

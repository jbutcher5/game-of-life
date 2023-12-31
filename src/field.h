#pragma once
#include <raylib.h>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

#define SCALE 1
#define BUFF_WIDTH 1000
#define BUFF_HEIGHT 1000
#define BUFF_SIZE BUFF_WIDTH * BUFF_HEIGHT

Vector2 CellScreenPosition(int n);
int BufferIndex(float x, float y);
void RenderBuffer(bool *buffer);
void PaintCell(bool *buffer);

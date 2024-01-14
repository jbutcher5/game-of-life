#pragma once
#include "field.h"

typedef enum {
  Editing,
  Running,
  Paused,
} GameState;

bool *RequestBuffer(void);
bool *UpdateCells(bool *buffer);

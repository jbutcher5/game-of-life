#pragma once

#include "game.h"
#include <raylib.h>

typedef struct {
  bool *buffer;
  GameState *state;
  double *last_update;
} Context;

typedef enum {
  Label,
  Button
} ComponentType;

typedef char* LabelContent;

typedef struct {
  void (*func) (Context);
  char *label;
}  ButtonContent;

typedef struct {
  Vector2 position;
  Vector2 size;
  void *content;
  ComponentType type;
} Component;

typedef struct {
  Component *components;
  int component_count;
  Vector2 position;
  Vector2 size;
} Menu;

void DrawMenuBox(Vector2 position, Vector2 size);
void RenderMenu(Menu menu);
void UpdateMenu(Menu *menu);

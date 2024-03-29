#pragma once

#include "game.h"
#include <raylib.h>

typedef struct {
  bool *buffer;
  GameState *state;
  double *update_delta;
} Context;

typedef enum {
  Label,
  Button,
  Input
} ComponentType;

typedef char* LabelContent;

typedef struct {
  void (*func) (Context);
  char *label;
} ButtonContent;

typedef struct {
  char *buffer;
  int buf_len;
  int buf_max;
  bool focused;
} InputContent;

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

void RenderMenu(Menu menu);
void UpdateMenu(Menu *menu, Context ctx);

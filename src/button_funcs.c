#include "button_funcs.h"
#include "field.h"
#include "game.h"
#include "stdio.h"
#include "stdlib.h"

#include <raylib.h>

#pragma clang diagnostic ignored "-Wunused-parameter"

char file_path[16] = {0};

ButtonContent reset_button = {reset, "Reset"};
ButtonContent fullscreen_button = {toggle_window_size, "Fullscreen"};
ButtonContent export_button = {serialise_field, "Export"};

InputContent import_input = {file_path, 0, 16, false};

Component menu_components[] = {
  {(Vector2){10, 20}, (Vector2){50, 40}, (void*)"Reset Field:", Label},
  {(Vector2){100, 5}, (Vector2){60, 40}, &reset_button, Button},
  {(Vector2){10, 70}, (Vector2){50, 40}, (void*)"Toggle Fullscreen:", Label},
  {(Vector2){120, 55}, (Vector2){60, 40}, &fullscreen_button, Button},
  {(Vector2){120, 105}, (Vector2){60, 40}, &export_button, Button},
  {(Vector2){120, 155}, (Vector2){60, 40}, &import_input, Input},
};

void reset(Context ctx) {
  *ctx.state = Editing;
  for (int i = 0; i < BUFF_SIZE; i++)
    (*ctx.buffer)[i] = 0;
}

void toggle_window_size(Context _) {
  static bool is_windowed = true;

  if (is_windowed)
    SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
  else
    SetWindowSize(GetMonitorWidth(GetCurrentMonitor())/2, GetMonitorHeight(GetCurrentMonitor())/2);

  is_windowed = !is_windowed;
}

void serialise_field(Context ctx) {
  FILE *file = fopen("tmp.txt", "w");
  freopen("tmp.txt", "a", file);

  if (!file)
    return;

  char buf_size[128];

  for (int i = 0; i < BUFF_SIZE; i++)
    if ((*ctx.buffer)[i]) {
      snprintf(buf_size, 128, "%d\n", i);
      fputs(buf_size, file);
    }

  fclose(file);
}

void deserialise_field(Context ctx) {
  FILE *file = fopen(file_path, "r");

  if (!file) {
    for (int i = 0; i < 16; i++)
      file_path[i] = 0;

    import_input.buf_len = 0;

    return;
  }
  
  reset(ctx);

  char buffer[32] = {0};
  int buffer_len = 0;
  
  for (int c = fgetc(file); c != EOF; c = fgetc(file)) {
    if (c == '\n') {
      // TODO: Check I'm not accessing bad memory
      (*ctx.buffer)[atoi(buffer)] = true;
      buffer_len = 0;

      for (int i = 0; i < 32; i++)
	buffer[i] = 0;
    }
    else {
      // TODO: Check I'm not accessing bad memory
      buffer[buffer_len] = c;
      buffer_len++;
    }
  }

  fclose(file);
}

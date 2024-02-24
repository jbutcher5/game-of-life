#include "menu_config.h"
#include "field.h"
#include "game.h"
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#pragma clang diagnostic ignored "-Wunused-parameter"

char import_file_path[32], export_file_path[32] = {0};

ButtonContent reset_button = {reset, "Reset"};
ButtonContent fullscreen_button = {toggle_window_size, "Fullscreen"};
ButtonContent import_button = {deserialise_field, "Import"};
ButtonContent export_button = {serialise_field, "Export"};

InputContent import_input = {import_file_path, 0, 32, false};
InputContent export_input = {export_file_path, 0, 32, false};

Component menu_components[] = {
  {(Vector2){10, 20}, (Vector2){50, 40}, (void*)"Reset Field:", Label},
  {(Vector2){100, 5}, (Vector2){60, 40}, &reset_button, Button},
  {(Vector2){10, 70}, (Vector2){50, 40}, (void*)"Toggle Fullscreen:", Label},
  {(Vector2){120, 55}, (Vector2){60, 40}, &fullscreen_button, Button},
  {(Vector2){10, 120}, (Vector2){50, 40}, (void*)"Export Field:", Label},
  {(Vector2){100, 105}, (Vector2){60, 40}, &export_button, Button},
  {(Vector2){180, 105}, (Vector2){120, 40}, &export_input, Input},
  {(Vector2){10, 170}, (Vector2){50, 40}, (void*)"Import Field:", Label},
  {(Vector2){100, 155}, (Vector2){60, 40}, &import_button, Button},
  {(Vector2){180, 155}, (Vector2){120, 40}, &import_input, Input},
};

ButtonContent play_button = {play_pause, (char[]){'>', 0, 0, 0}};
ButtonContent speedup_button = {speedup, ">>"};
ButtonContent slowdown_button = {slowdown, "<<"};

char update_buffer[32] = "Update (Seconds): ";

char *update_buffer_insert = update_buffer + sizeof(char) * 18;

Component control_bar_components[] = {
  {(Vector2){5, 5}, (Vector2){20, 20}, &play_button, Button},
  {(Vector2){30, 5}, (Vector2){20, 20}, &speedup_button, Button},
  {(Vector2){55, 5}, (Vector2){20, 20}, &slowdown_button, Button},
  {(Vector2){80, 10}, (Vector2){20, 20}, update_buffer, Label},
};

void slowdown(Context ctx) {
  *ctx.update_delta -= 0.1 * (*ctx.update_delta - 0.1 > 0);
}

void speedup(Context ctx) {
  *ctx.update_delta += 0.1 * (*ctx.update_delta + 0.1 < 10);
}

void play_pause(Context ctx) {
  if (*ctx.state == Editing || *ctx.state == Paused) {
    *ctx.state = Running;
    play_button.label[0] = '|';
    play_button.label[1] = ' ';
    play_button.label[2] = '|';
    return;
  }

  play_button.label[0] = '>';
  play_button.label[1] = 0;
  play_button.label[2] = 0;
  *ctx.state = Paused;
}

void reset(Context ctx) {
  *ctx.state = Editing;
  for (int i = 0; i < BUFF_SIZE; i++)
    ctx.buffer[i] = false;
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
  FILE *file = fopen(export_file_path, "w");
  freopen(export_file_path, "a", file);

  if (!file) {
    for (int i = 0; i < 16; i++)
      export_file_path[i] = 0;

    export_input.buf_len = 0;
    return;
  }

  char buf_size[128];

  for (int i = 0; i < BUFF_SIZE; i++)
    if (ctx.buffer[i]) {
      snprintf(buf_size, 128, "%d\n", i);
      fputs(buf_size, file);
    }

  fclose(file);
}

void deserialise_field(Context ctx) {
  FILE *file = fopen(import_file_path, "r");

  if (!file) {
    for (int i = 0; i < 16; i++)
      import_file_path[i] = 0;

    import_input.buf_len = 0;
    return;
  }
  
  reset(ctx);

  char buffer[32] = {0};
  int buffer_len = 0;
  
  for (int c = fgetc(file); c != EOF; c = fgetc(file)) {
    if (c == '\n') {
      // TODO: Check I'm not accessing bad memory
      ctx.buffer[atoi(buffer)] = true;
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

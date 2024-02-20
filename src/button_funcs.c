#include "button_funcs.h"
#include "field.h"
#include "game.h"
#include "stdio.h"

#include <raylib.h>

#pragma clang diagnostic ignored "-Wunused-parameter"

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

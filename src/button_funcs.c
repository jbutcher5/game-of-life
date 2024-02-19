#include "button_funcs.h"
#include "field.h"
#include "game.h"

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

#pragma once

#include "menu.h"

void reset(Context);
void toggle_window_size(Context);
void serialise_field(Context);
void deserialise_field(Context);

extern char file_path[16];
extern ButtonContent reset_button, fullscreen_button, export_button;
extern InputContent import_input;
extern Component menu_components[];

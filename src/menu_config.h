#pragma once

#include "menu.h"

void reset(Context);
void toggle_window_size(Context);
void serialise_field(Context);
void deserialise_field(Context);

extern char export_file_path[32], import_file_path[32];
extern ButtonContent reset_button, fullscreen_button, export_button, import_button;
extern InputContent export_input, import_input;
extern Component menu_components[];

void play_pause(Context);

extern ButtonContent play_button;
extern Component control_bar_components[];

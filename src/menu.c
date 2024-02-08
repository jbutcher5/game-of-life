#include "menu.h"
#include <raylib.h>
#include <raymath.h>

void DrawMenuBox(Vector2 position, Vector2 size) {
  DrawRectangle(position.x, position.y, size.x, size.y, BLACK);
  DrawRectangleLines(position.x, position.y, size.x, size.y, RAYWHITE);
}

Vector2 MeasureTextV2(const char *text, int fontSize)
{
    Vector2 textSize = { 0.0f, 0.0f };

    // Check if default font has been loaded
    if (GetFontDefault().texture.id != 0)
    {
        int defaultFontSize = 10;   // Default Font chars height in pixel
        if (fontSize < defaultFontSize) fontSize = defaultFontSize;
        int spacing = fontSize/defaultFontSize;

        textSize = MeasureTextEx(GetFontDefault(), text, (float)fontSize, (float)spacing);
    }

    return textSize;
}

void RenderComponent(Menu *menu, Component component) {
  Vector2 screen_pos = Vector2Add(menu->position, component.position);
  Vector2 text_pos;
  switch (component.type) {
  case Label:
    text_pos = Vector2Add(screen_pos, Vector2Scale(component.size, 0.5));
    text_pos = Vector2Subtract(text_pos,
			       Vector2Scale(MeasureTextV2(component.content, 10), 0.5));
    DrawMenuBox(screen_pos, component.size);
    DrawText(component.content, text_pos.x, text_pos.y, 10, RAYWHITE);
    break;
  case Button:

    break;
  };
}

void RenderMenu(Menu menu) {
  DrawMenuBox(menu.position, menu.size);

  for (int i = 0; i < menu.component_count; i++)
    RenderComponent(&menu, menu.components[i]);
}

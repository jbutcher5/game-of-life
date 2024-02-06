#include "menu.h"
#include <raylib.h>

void DrawMenuBox(Vector2 position, Vector2 size) {
  DrawRectangle(position.x, position.y, size.x, size.y, BLACK);
  DrawRectangleLines(position.x, position.y, size.x, size.y, RAYWHITE);
}

void RenderComponent(Component component) {
  
}

void RenderMenu(Menu menu) {
  DrawMenuBox(menu.position, menu.size);

  for (int i = 0; i < menu.component_count; i++)
    RenderComponent(menu.components[i]);
}

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
  // Calculate screen position of component
  Vector2 screen_pos = Vector2Add(menu->position, component.position);

  // Change rendering method depending on the type of component
  if (component.type == Button) {
    ButtonContent *content = component.content;

    // Align text to the centre of the button
    Vector2 text_pos = Vector2Add(screen_pos, Vector2Scale(component.size, 0.5));
    text_pos = Vector2Subtract(text_pos,
			       Vector2Scale(MeasureTextV2(content->label, 10), 0.5));

    // Draw box and text
    DrawMenuBox(screen_pos, component.size);
    DrawText(content->label, text_pos.x, text_pos.y, 10, RAYWHITE);
  } else if (component.type == Label) {
    // Draw text (not centred)
    DrawText(component.content, screen_pos.x, screen_pos.y, 10, RAYWHITE);
  } else if (component.type == Input) {
    InputContent *content = component.content;

    char *text = "Type Here";
    Color colour = DARKGRAY;
    
    if (content->buf_len > 0) {
      text = content->buffer;
      colour = RAYWHITE;
    }

    // Align text to the centre of the button
    Vector2 text_pos = Vector2Add(screen_pos, Vector2Scale(component.size, 0.5));
    text_pos = Vector2Subtract(text_pos,
			       Vector2Scale(MeasureTextV2(text, 10), 0.5));
    
    DrawMenuBox(screen_pos, component.size);
    DrawText(text, text_pos.x, text_pos.y, 10, colour);
  }
}

void RenderMenu(Menu menu) {
  DrawMenuBox(menu.position, menu.size);

  // Iterate through each menu component
  for (int i = 0; i < menu.component_count; i++)
    RenderComponent(&menu, menu.components[i]);
}

void UpdateMenu(Menu *menu, Context ctx) {
  for (int i = 0; i < menu->component_count; i++) {
    Component *component = menu->components + i;
    if (component->type == Button) {
      ButtonContent *content = component->content;
      Vector2 screen_pos = Vector2Add(component->position, menu->position);
      
      // Check if mouse is over AABB
      Vector2 mouse_pos = GetMousePosition();
      bool is_colliding = mouse_pos.x >= screen_pos.x &&
	mouse_pos.x <= screen_pos.x + component->size.x &&
	mouse_pos.y >= screen_pos.y &&
	mouse_pos.y <= screen_pos.y + component->size.y;
	
      if (is_colliding && IsMouseButtonPressed(0))
	content->func(ctx);
    } else if (component->type == Input) {
      InputContent *content = component->content;
      Vector2 screen_pos = Vector2Add(component->position, menu->position);

      // Check if mouse is over AABB
      Vector2 mouse_pos = GetMousePosition();
      bool is_colliding = mouse_pos.x >= screen_pos.x &&
	mouse_pos.x <= screen_pos.x + component->size.x &&
	mouse_pos.y >= screen_pos.y &&
	mouse_pos.y <= screen_pos.y + component->size.y;

      // Check if input should be focused
      if (IsMouseButtonPressed(0))
	content->focused = is_colliding;

      // Check if input is focused and characters are being typed
      if (content->focused) {
	int c = GetCharPressed();

	// If a backspace is typed
	if (IsKeyPressed(KEY_BACKSPACE) && content->buf_len > 0) {
	  content->buf_len--;
	  content->buffer[content->buf_len] = 0;
	}
	else if (c && content->buf_len + 1 != content->buf_max) {
	  content->buffer[content->buf_len] = (char)c;
	  content->buf_len++;
	}
      }
    }
  }
}

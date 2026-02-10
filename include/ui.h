#ifndef UI_H
#define UI_H

#include "raylib.h"

#define GET 0
#define SET 1

// Draws a button and returns true if clicked
// bounds: The position and size of the button
// text: The label displayed on the button
bool GuiButton(Rectangle bounds, const char *text, Color color);

// sets or gets the position of the mouse on the virtual canvas
//
Vector2 virtualMousePosition(int mode, float scale);
#endif

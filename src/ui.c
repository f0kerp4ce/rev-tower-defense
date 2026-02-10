#include "ui.h"
#include <math.h>
#include <stdio.h>

extern const int virtualHeight;
extern const int virtualWidth;


Vector2 virtualMousePosition(int mode, float newScale) {
    // must be called first with a SET to the scale
    static float scale;
    if (mode == SET) scale = newScale;

    Vector2 mouse = GetMousePosition();
    Vector2 virtualMouse = { 0 };
    virtualMouse.x = (mouse.x - (GetScreenWidth() - (virtualWidth * scale)) * 0.5f) / scale;
    virtualMouse.y = (mouse.y - (GetScreenHeight() - (virtualHeight * scale)) * 0.5f) / scale;

    // Clamp the mouse so it doesn't go "outside" the virtual canvas
    virtualMouse.x = fmaxf(fminf(virtualMouse.x, (float)virtualWidth), 0);
    virtualMouse.y = fmaxf(fminf(virtualMouse.y, (float)virtualHeight), 0);
    return virtualMouse;
}

bool GuiButton(Rectangle bounds, const char *text, Color color) {
    Vector2 mousePoint = virtualMousePosition(GET, 0.0f);
    bool clicked = false;

    if (CheckCollisionPointRec(mousePoint, bounds)) {
        color = GRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            clicked = true;
        }
    }

    DrawRectangleRec(bounds, color);
    DrawRectangleLinesEx(bounds, 2, DARKGRAY);

    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);
    
    int textX = bounds.x + (bounds.width / 2) - (textWidth / 2);
    int textY = bounds.y + (bounds.height / 2) - (fontSize / 2);

    DrawText(text, textX, textY, fontSize, BLACK);

    return clicked;
}

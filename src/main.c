#include "raylib.h"
#include "ui.h"
#include <math.h>
#include <stdio.h>

const int virtualWidth = 3840;
const int virtualHeight = 2160;

typedef enum GameScreen { LOGO = 0, TITLE, LEVELS, RESEARCH, SETTINGS } GameScreen;

int main(void) {
    const int initScreenWidth = 1792;
    const int initScreenHeight = 1024;


    // This creates the window and the OpenGL context
    SetWindowMinSize(640, 480);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(initScreenWidth, initScreenHeight, "Reverse Tower Defense - Menu");

    RenderTexture2D virtualCanvas = LoadRenderTexture(virtualWidth, virtualHeight);
    SetTextureFilter(virtualCanvas.texture, TEXTURE_FILTER_BILINEAR); // smoother scaling

    Texture2D background = LoadTexture("resources/recraftloadingscreen3.png");

    GameScreen currentScreen = TITLE;


    // Set the game to run at 144 frames-per-second
    SetTargetFPS(144);

    // === MAIN LOOP ===
    // WindowShouldClose checks if the ESC key is pressed or the close button is clicked
    bool exitWindow = 0;
    while (!WindowShouldClose() && !exitWindow) {
      // --- Update Logic ---
        int w = GetScreenWidth();
        int h = GetScreenHeight();

        float scale = fminf((float)w/virtualWidth, (float)h/virtualHeight);
        // Calculate the position to center the canvas in the window (Letterboxing)
        Rectangle destRec = { 
            (w - ((float)virtualWidth * scale)) * 0.5f, 
            (h - ((float)virtualHeight * scale)) * 0.5f, 
            (float)virtualWidth * scale, 
            (float)virtualHeight * scale 
        };
        // first set the scale for the virtual mouse
        virtualMousePosition(SET, scale);

        // --- Drawing ---
        BeginDrawing();

        ClearBackground(BLACK); // colour of the background outside the virtual canvas


        BeginTextureMode(virtualCanvas);
        ClearBackground(RAYWHITE);
        DrawTextureEx(background, (Vector2) {0, 0}, 0.0f, (float) 3840 / 1792, WHITE); // DrawTextureEx: texture, position, rotation, scale, color


        switch(currentScreen) {
            case TITLE:
                // We check logic and draw at the same time!
                if (GuiButton((Rectangle){ w/2 - 100, h/2 - 100, 200, 40 }, "LEVELS", LIGHTGRAY)) {
                    currentScreen = LEVELS;
                    background = LoadTexture("resources/recraftloadingscreen2.png");
                }

                if (GuiButton((Rectangle){ w/2 - 100, h/2 - 50, 200, 40 }, "RESEARCH", LIGHTGRAY)) {
                    currentScreen = RESEARCH;
                }
 
                if (GuiButton((Rectangle){ w/2 - 100, h/2, 200, 40 }, "SETTINGS", LIGHTGRAY)) {
                    currentScreen = SETTINGS;
                }

                if (GuiButton((Rectangle){ w/2 - 100, h/2 + 50, 200, 40 }, "QUIT", MAROON)) {
                    exitWindow = true;
                }
                break;
            case LEVELS:
                DrawText("Level Selection coming soon!", 200, 200, 20, GREEN);
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    currentScreen = TITLE;
                    background = LoadTexture("resources/recraftloadingscreen3.png");
                }
                break;

            default: break;
        }
        EndTextureMode();
        // draw the virtual canvas to the screen
        DrawTexturePro(virtualCanvas.texture,
                       (Rectangle) { 0.0f, 0.0f, (float) virtualCanvas.texture.width, (float)-virtualCanvas.texture.height},
                       destRec,
                       (Vector2) { 0, 0 },
                       0.0f,
                       WHITE);
        EndDrawing();
    }

    // 3. De-Initialization
    UnloadTexture(background); // Clean up memory
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

#include "../include/gamestate.h"
#include "../include/inputhandler.h"
#include "../include/menu.h"
#include "../include/player.h"
#include "../include/window.h"
#include <raylib.h>

int main() {
    // --- Inicialización de audio ---
    InitAudioDevice();
    Music beat = LoadMusicStream("assets/beat.wav");
    beat.looping = true;
    PlayMusicStream(beat);

    // --- Inicialización de ventana ---
    int monitor = GetCurrentMonitor();
    int width = GetMonitorWidth(monitor);
    int height = GetMonitorHeight(monitor);

    InitWindow(width, height, window::WINDOW_NAME);
    if (window::FULLSCREEN_ON_START) {
        ToggleFullscreen();
    }

    SetTargetFPS(120);

    Menu menu;
    InputHandler input;
    Player player;

    // --- Loop principal ---
    while (!WindowShouldClose()) {
        // --- Audio ---
        UpdateMusicStream(beat);  

        // --- Input y estado ---
        if (gamestate.hideCursor) HideCursor(); else ShowCursor();
        int state = gamestate.Get();

        switch (state) {
            case 0: menu.Update(); break;
            case 1: input.Update(); player.Update(input); break;
        }

        // --- Dibujado ---
        BeginDrawing();
        ClearBackground(gamestate.bgColor);

    Camera2D camera = {0};
camera.target = {window::WORLD_WIDTH / 2.0f, window::WORLD_HEIGHT / 2.0f};  // centro del mundo
camera.offset = {window::ScreenWidth() / 2.0f, window::ScreenHeight() / 2.0f}; // centro de la ventana
camera.zoom = (float)window::ScreenHeight() / window::WORLD_HEIGHT; // escala proporcional

        BeginMode2D(camera);
            switch (state) {
                case 0: menu.Draw(); break;
                case 1: player.Draw(); break;
            }
        EndMode2D();

        // --- Debg ---
        if (gamestate.debug) DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, GREEN);

        EndDrawing();
    }

    // --- Cleanup ---
    UnloadMusicStream(beat);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

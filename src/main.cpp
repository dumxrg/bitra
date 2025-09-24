#include "../include/gamestate.h"
#include "../include/menu.h"
#include "../include/window.h"
#include <raylib.h>

int main() {
  InitWindow(window::WINDOW_WIDTH, window::WINDOW_HEIGHT, window::WINDOW_NAME);
  if (window::FULLSCREEN_ON_START) {
    ToggleFullscreen();
}
  Menu menu;

  while (!WindowShouldClose()) {
    (gamestate.hideCursor == true) ? HideCursor() : ShowCursor();
    int state = gamestate.Get();
    BeginDrawing();
    ClearBackground(BLACK);

    switch (state) {
    case 0:
      menu.Update(state);
      menu.Draw();
      break;

    case 1:
      break;
    }

    DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, GREEN);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

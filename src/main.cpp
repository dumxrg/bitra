#include "../include/gamestate.h"
#include "../include/inputhandler.h"
#include "../include/menu.h"
#include "../include/player.h"
#include "../include/window.h"

int main() {
  InitWindow(window::WINDOW_WIDTH, window::WINDOW_HEIGHT, window::WINDOW_NAME);
  if (window::FULLSCREEN_ON_START) {
    ToggleFullscreen();
  }
  Menu menu;
  InputHandler input;
  Player player;

  while (!WindowShouldClose()) {
    (gamestate.hideCursor == true) ? HideCursor() : ShowCursor();
    int state = gamestate.Get();

    ClearBackground(gamestate.bgColor);
    switch (state) {
    case 0:
      menu.Update();

      break;

    case 1:
      input.Update();
      player.Update(input);
      break;
    }
    
    BeginDrawing();
    switch (state) {
    case 0:
      menu.Draw();
      break;
    case 1:
      player.Draw();
      break;
    }
    if (gamestate.debug) {
      DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, GREEN);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

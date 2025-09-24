#include "../include/menu.h"
#include "../include/gamestate.h"
#include "../include/window.h"
#include <raylib.h>

void Menu::Update(int &state) {
  Rectangle button = {window::WINDOW_WIDTH / 2.0f - 200 / 2.0f,
                      window::WINDOW_HEIGHT / 1.5f, 200, 20};
  if (GetKeyPressed() != 0) {
    gamestate.Next();
  }
}

void Menu::Draw() {
  DrawText("BITRA", window::WINDOW_WIDTH / 2 - MeasureText("BITRA", 100) / 2,
           window::WINDOW_HEIGHT / 2 - 100 / 2, 100, YELLOW);
  DrawText("PRESS ANY BUTTON TO START",
           window::WINDOW_WIDTH / 2 - MeasureText("PRESS ANY BUTTON TO START", 30) / 2,
           (float)window::WINDOW_HEIGHT / 1.25f, 30, YELLOW);
}

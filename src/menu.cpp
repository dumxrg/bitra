#include "../include/menu.h"
#include "../include/gamestate.h"
#include "../include/window.h"

void Menu::Update() {
  if (GetKeyPressed() != 0 || GetGamepadButtonPressed()) {
    gamestate.Next();
  }
}

void Menu::Draw() {
  DrawText(title, window::WINDOW_WIDTH / 2 - MeasureText(title, titleFontSize) / 2,
           window::WINDOW_HEIGHT / 2 - titleFontSize / 2, titleFontSize, YELLOW);
  DrawText(subTitle,
           window::WINDOW_WIDTH / 2 - MeasureText(subTitle, subTitleFontSize) / 2,
           (float)window::WINDOW_HEIGHT / 1.25f, subTitleFontSize, YELLOW);
}

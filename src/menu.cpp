#include "../include/menu.h"
#include "../include/gamestate.h"
#include "../include/window.h"

void Menu::Update() {
  if (GetKeyPressed() != 0 || GetGamepadButtonPressed()) {
    gamestate.Next();
  }
}

void Menu::Draw() {
 DrawText(title, (window::WORLD_WIDTH - MeasureText(title, titleFontSize)) / 2,
         (window::WORLD_HEIGHT - titleFontSize) / 2, titleFontSize, YELLOW);

DrawText(subTitle,
         (window::WORLD_WIDTH - MeasureText(subTitle, subTitleFontSize)) / 2,
         window::WORLD_HEIGHT * 0.8f,
         subTitleFontSize, YELLOW);

}

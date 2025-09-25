#ifndef MENU_H
#define MENU_H

#include "raylib.h"

class Menu {
public:
const char* title = "Bitra";
const constexpr static short titleFontSize = 100;

const char* subTitle = "Press any button to start!";
const constexpr static short subTitleFontSize = 20;


    void Update();
    void Draw();            
};

#endif

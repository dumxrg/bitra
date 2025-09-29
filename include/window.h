#ifndef WINDOW_H
#define WINDOW_H

#include <raylib.h>

struct window {
    static constexpr float WORLD_WIDTH = 1280.0f;
    static constexpr float WORLD_HEIGHT = 720.0f;

    static constexpr const char* WINDOW_NAME = "Bitra";
    static constexpr const bool FULLSCREEN_ON_START = true;
    static inline int Width()  { return GetScreenWidth(); }
static inline int Height() { return GetScreenHeight(); }


    static inline int ScreenWidth() { return GetScreenWidth(); }
    static inline int ScreenHeight() { return GetScreenHeight(); }
};

#endif

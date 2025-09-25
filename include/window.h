#ifndef WINDOWS_H
#define WINDOWS_H

struct window {
    static constexpr const short WINDOW_WIDTH = 1020;
    static constexpr const short WINDOW_HEIGHT = (WINDOW_WIDTH / 16) * 9;  // 16:9 ratio
    static constexpr const char* WINDOW_NAME = "Bitra";
    static constexpr const bool FULLSCREEN_ON_START = false;
};

#endif

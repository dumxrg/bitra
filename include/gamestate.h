
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <raylib.h>
class GameState {
public:
    int state = 0;
    Color bgColor{0,0,0,255};
    constexpr  static bool debug = true;
    bool hideCursor = true;
    void Next() { state++; }
    constexpr int Get() const { return state; }
};

extern GameState gamestate;

#endif

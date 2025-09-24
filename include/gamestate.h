
#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
public:
    int state = 0;
    bool debug = true;
    bool hideCursor = true;
    void Next() { state++; }
    int Get() const { return state; }
};

extern GameState gamestate;

#endif

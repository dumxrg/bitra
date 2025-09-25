#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <raylib.h>

class InputHandler {
public:
    void Update();

    Vector2 GetRawInputDir() const;       
    Vector2 GetNormalizedInputDir() const; 
     bool dashPressed = IsKeyDown(KEY_P) ;
private:
    Vector2 inputDir = {0.0f, 0.0f};
};

#endif

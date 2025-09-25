#include "../include/inputhandler.h"


#include <raymath.h>

void InputHandler::Update() {
    inputDir = {0.0f, 0.0f};

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    inputDir.y -= 1.0f;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  inputDir.y += 1.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  inputDir.x -= 1.0f;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) inputDir.x += 1.0f;

    if (IsGamepadAvailable(0)) {
   
        float axisX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
        float axisY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

        const float deadzone = 0.2f;
        if (fabs(axisX) > deadzone) inputDir.x += axisX;
        if (fabs(axisY) > deadzone) inputDir.y += axisY;
    }
  

    //Support for android soon
}

Vector2 InputHandler::GetRawInputDir() const {
    return inputDir;
}

Vector2 InputHandler::GetNormalizedInputDir() const {
   
    return { Vector2Normalize(inputDir)};
}

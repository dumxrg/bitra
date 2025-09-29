//player.cpp
#include "../include/player.h"
#include <algorithm> 
#include <raylib.h>
#include <raymath.h>
#include "../include/gamestate.h"

Player::Player() : player{position.x, position.y, size, size}
{}

void Player::Update(const InputHandler& input) {
    float delta = GetFrameTime();
    Vector2 move = input.GetNormalizedInputDir();
        if (input.IsDashPressed()) { 
        isDashing = true;
    }
    if (isDashing) {
        dashingTimer += delta;
    }

    if (dashingTimer > dashTimer) {
        isDashing = false;
        dashingTimer = 0;
        
    }


    

    float currentSpeed = isDashing ? dashSpeed : speed;
    Vector2 velocity = Vector2Scale(move, currentSpeed * delta);
    position = Vector2Add(position, velocity);

    position.x = std::clamp(position.x, halfSize, window::WORLD_WIDTH - halfSize);
position.y = std::clamp(position.y, halfSize, window::WORLD_HEIGHT - halfSize);

    player.x = position.x;
    player.y = position.y;
}


void Player::Draw() const {
    if (gamestate.debug ==true){
        if(isDashing){
        DrawText("Dashing",10, 50, 10, RED);
        }else{
            DrawText("Not Dashing",10, 50, 10, RED);

        }

    }
        Vector2 origin = {player.width / 2.0f, player.height / 2.0f};
    float rotation = 0.0f;
     DrawCircleV(position, halfSize, YELLOW);

    DrawRectanglePro(player, origin, rotation, playerColor);

}

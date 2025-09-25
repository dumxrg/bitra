#include "../include/player.h"
#include <algorithm> 
#include <raylib.h>

Player::Player()
    : player{position.x, position.y, size, size}
{}

void Player::Update(const InputHandler& input) {
    float delta = GetFrameTime();
    Vector2 move = input.GetNormalizedInputDir();
    if (IsKeyPressed(KEY_P))  {
        position.x += move.x * dashSpeed * delta;
        position.y += move.y * dashSpeed * delta;
     }else{
         position.x += move.x * speed * delta;
          position.y += move.y * speed * delta ;
          
     }
        
    position.x = std::max(halfSize, std::min(position.x, (float)GetScreenWidth() -halfSize));
    position.y = std::max(halfSize, std::min(position.y, (float)GetScreenHeight() - halfSize));
       
    player.x = position.x ;
    player.y = position.y ;
}

void Player::Draw() const {
    Vector2 origin = {player.width / 2.0f, player.height / 2.0f};
    float rotation = 0.0f;
     DrawCircleV(position, halfSize, YELLOW);

    DrawRectanglePro(player, origin, rotation, playerColor);

}

//player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "inputhandler.h"
#include "window.h"
#include <raylib.h>
class Player {
public:
//Player Props
  Color playerColor{BLUE};
  float rotation = 0;
  static constexpr float size = 20.0f;
Vector2 position{window::WORLD_WIDTH / 2.0f, window::WORLD_HEIGHT / 2.0f};
float halfSize = size * 0.5f;
Rectangle player;



//Movement
  static constexpr float speed = 500.0f;
//Dash Logic
  static constexpr float dashSpeed = speed*3;
  bool isDashing;
  float dashingTimer = 0;
  static constexpr float dashTimer = 0.1f;
  

  Player();
  void Update(const InputHandler &input);
  void Draw() const;
};

#endif

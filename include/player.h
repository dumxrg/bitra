#ifndef PLAYER_H
#define PLAYER_H

#include "inputhandler.h"
#include "window.h"
#include <raylib.h>
class Player {
public:
  Vector2 position{window::WINDOW_WIDTH / 2.0f, window::WINDOW_HEIGHT / 2.0f};
  float rotation = 0;
  static constexpr float size = 10.0f;
  static constexpr float speed = 440.0f;
  static constexpr float dashSpeed = 1000.0f;

  Rectangle player;
  Color playerColor{BLUE};
  float halfSize = size * 0.5f;

  Player();

  void Update(const InputHandler &input);
  void Draw() const;
};

#endif

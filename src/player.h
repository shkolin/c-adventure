#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

const float DEFAULT_PLAYER_SPEED = 3.0f;

enum PlayerDirection {
  UP = 1,
  DOWN = 2,
  LEFT = 3,
  RIGHT = 4,
};

enum PlayerState {
  Idle,
  Walking,
};

typedef struct PlayerSize {
  int width;
  int height;
} PlayerSize;

typedef struct Player {
  PlayerSize size;
  Vector2 position;
  float speed;
  enum PlayerState state;
  enum PlayerDirection direction;
} Player;

#endif

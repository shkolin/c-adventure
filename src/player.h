#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

const float DEFAULT_PLAYER_SPEED = 3.0f;

enum PlayerDirection {
  UP = 3,
  DOWN = 0,
  LEFT = 2,
  RIGHT = 1,
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
  int current_frame;
  int frame_counter;
  int frames_speed;
  int num_frames;
} Player;

#endif

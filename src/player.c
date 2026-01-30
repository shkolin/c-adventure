#include "player.h"

// Define constants
const float DEFAULT_PLAYER_SPEED = 3.0f;
const int DEFAULT_ANIMATION_SPEED = 16;
const int DEFAULT_NUM_FRAMES = 4;

// Initialize animation with default or custom values
void InitAnimation(Animation *animation, int frames_speed, int num_frames) {
  animation->current_frame = 0;
  animation->frame_counter = 0;
  animation->frames_speed = frames_speed;
  animation->num_frames = num_frames;
}

// Update animation frame based on counter
void UpdateAnimation(Animation *animation) {
  animation->frame_counter++;

  if (animation->frame_counter >= animation->frames_speed) {
    animation->frame_counter = 0;
    animation->current_frame++;

    if (animation->current_frame >= animation->num_frames) {
      animation->current_frame = 0;
    }
  }
}

// Reset animation to first frame
void ResetAnimation(Animation *animation) {
  animation->current_frame = 0;
  animation->frame_counter = 0;
}

// Get the source rectangle for the current animation frame
Rectangle GetAnimationSourceRect(const Animation *animation, int frame_width,
                                 int frame_height, int direction) {
  return (Rectangle){animation->current_frame * frame_width,
                     direction * frame_height, frame_width, frame_height};
}

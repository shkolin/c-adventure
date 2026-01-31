#include "player.h"

// Define constants
const float DEFAULT_PLAYER_SPEED = 3.0f;
const int DEFAULT_ANIMATION_SPEED = 16;
const int DEFAULT_NUM_FRAMES = 4;

// Initialize animation with default or custom values
void init_animation(Animation *animation, int frames_speed, int num_frames)
{
    animation->current_frame = 0;
    animation->frame_counter = 0;
    animation->frames_speed = frames_speed;
    animation->num_frames = num_frames;
}

// Update animation frame based on counter
void update_animation(Animation *animation)
{
    animation->frame_counter++;

    if (animation->frame_counter >= animation->frames_speed)
    {
        animation->frame_counter = 0;
        animation->current_frame++;

        if (animation->current_frame >= animation->num_frames)
        {
            animation->current_frame = 0;
        }
    }
}

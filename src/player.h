#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

extern const float DEFAULT_PLAYER_SPEED;

// Animation constants
extern const int DEFAULT_ANIMATION_SPEED;
extern const int DEFAULT_NUM_FRAMES;

typedef struct Animation
{
    int current_frame;
    int frame_counter;
    int frame_rate;
    int num_frames;
} Animation;

enum PlayerDirection
{
    DIR_UP = 3,
    DIR_DOWN = 0,
    DIR_LEFT = 2,
    DIR_RIGHT = 1,
};

enum PlayerState
{
    IDLE,
    WALKING,
};

typedef struct PlayerSize
{
    int width;
    int height;
} PlayerSize;

typedef struct Player
{
    PlayerSize size;
    PlayerSize frame;
    Vector2 position;
    float speed;
    enum PlayerState state;
    enum PlayerDirection direction;
    Animation animation;
} Player;

// Animation functions
void init_animation(Animation *animation, int frame_rate, int num_frames);
void update_animation(Animation *animation);

#endif

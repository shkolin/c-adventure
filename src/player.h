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
    int frames_speed;
    int num_frames;
} Animation;

enum PlayerDirection
{
    UP = 3,
    DOWN = 0,
    LEFT = 2,
    RIGHT = 1,
};

enum PlayerState
{
    Idle,
    Walking,
};

typedef struct PlayerSize
{
    int width;
    int height;
} PlayerSize;

typedef struct Player
{
    PlayerSize size;
    PlayerSize frame_size;
    Vector2 position;
    float speed;
    enum PlayerState state;
    enum PlayerDirection direction;
    Animation animation;
} Player;

// Animation functions
void init_animation(Animation *animation, int framesSpeed, int numFrames);
void update_animation(Animation *animation);

#endif

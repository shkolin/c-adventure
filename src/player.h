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
    Vector2 sprite_offset;
    float speed;
    enum PlayerState state;
    enum PlayerDirection direction;
    Animation animation;
} Player;

typedef struct PlayerInput
{
    bool up;
    bool down;
    bool left;
    bool right;
} PlayerInput;

// Animation functions
void init_player_animation(Animation *animation, int frame_rate, int num_frames);
void update_player_animation(Animation *animation);
void update_player_position(Player *player, PlayerInput input, int screen_width, int screen_height,
                            float scale);

#endif

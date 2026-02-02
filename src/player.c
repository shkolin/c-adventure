#include "player.h"

// Define constants
const float DEFAULT_PLAYER_SPEED = 1.0f;
const int DEFAULT_ANIMATION_SPEED = 16;
const int DEFAULT_NUM_FRAMES = 4;

// Initialize animation with default or custom values
void init_player_animation(Animation *animation, int frame_rate, int num_frames)
{
    animation->current_frame = 0;
    animation->frame_counter = 0;
    animation->frame_rate = frame_rate;
    animation->num_frames = num_frames;
}

// Update animation frame based on counter
void update_player_animation(Animation *animation)
{
    animation->frame_counter++;

    if (animation->frame_counter >= animation->frame_rate)
    {
        animation->frame_counter = 0;
        animation->current_frame++;

        if (animation->current_frame >= animation->num_frames)
        {
            animation->current_frame = 0;
        }
    }
}

void update_player_position(Player *player, PlayerInput input, int screen_width, int screen_height,
                            float scale)
{
    float player_x = player->position.x + player->sprite_offset.x * scale;
    float player_y = player->position.y + player->sprite_offset.y * scale;
    int player_width = player->size.width * scale;
    int player_height = player->size.height * scale;

    player->state = IDLE;

    // Player movement
    if (input.up && player_y > 0)
    {
        player->direction = DIR_UP;
        player->state = WALKING;
        player->position.y -= player->speed;
    }
    if (input.down && player_y + player_height < screen_height)
    {
        player->direction = DIR_DOWN;
        player->state = WALKING;
        player->position.y += player->speed;
    }
    if (input.left && player_x > 0)
    {
        player->direction = DIR_LEFT;
        player->state = WALKING;
        player->position.x -= player->speed;
    }
    if (input.right && player_x + player_width < screen_width)
    {
        player->direction = DIR_RIGHT;
        player->state = WALKING;
        player->position.x += player->speed;
    }
}

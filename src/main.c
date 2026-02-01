#include "main.h"
#include "player.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

// Module variables declaration (local)
static Player player = {0};
static Texture2D player_texture = {0};
static Texture2D player_texture_idle = {0};

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const int SCALE = 3;
static const int FPS = 60;

// Main entry point
int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C Adventure");
    SetTargetFPS(FPS);

    init_game();

    while (!WindowShouldClose())
    {
        gameloop();
        draw_game();
    }

    UnloadTexture(player_texture);
    UnloadTexture(player_texture_idle);

    CloseWindow();
    return 0;
}

// Initialize game variables
static void init_game(void)
{
    // Initialize player variables
    player.position = (Vector2){0, 50};
    player.size = (PlayerSize){8, 18};
    player.frame = (PlayerSize){24, 24};
    player.speed = DEFAULT_PLAYER_SPEED;
    player.state = Idle;
    player.direction = DOWN;

    // Initialize player animation
    init_animation(&player.animation, DEFAULT_ANIMATION_SPEED, DEFAULT_NUM_FRAMES);

    player_texture = LoadTexture("../assets/Char_003.png");
    player_texture_idle = LoadTexture("../assets/Char_003_Idle.png");
}

static void gameloop(void)
{
    player.state = Idle;

    bool pressed_key_up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
    bool pressed_key_down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);
    bool pressed_key_left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    bool pressed_key_right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);

    Vector2 sprite_offset = {24, 18};
    float player_x = player.position.x + sprite_offset.x;
    float player_y = player.position.y + sprite_offset.y;
    int player_width = player.size.width * SCALE;
    int player_height = player.size.height * SCALE;

    // Player movement
    if (pressed_key_up && player_y > 0)
    {
        player.direction = UP;
        player.state = Walking;
        player.position.y -= player.speed;
    }
    if (pressed_key_down && player_y + player_height < SCREEN_HEIGHT)
    {
        player.direction = DOWN;
        player.state = Walking;
        player.position.y += player.speed;
    }
    if (pressed_key_left && player_x > 0)
    {
        player.direction = LEFT;
        player.state = Walking;
        player.position.x -= player.speed;
    }
    if (pressed_key_right && player_x + player_width < SCREEN_WIDTH)
    {
        player.direction = RIGHT;
        player.state = Walking;
        player.position.x += player.speed;
    }

    // Animation frame update
    update_animation(&player.animation);
}

// Draw game elements
static void draw_game(void)
{
    BeginDrawing();
    ClearBackground(DARKGRAY);
    // Debug info
    DrawText(TextFormat("Player x:%.0f y:%.0f", player.position.x, player.position.y), 15, 15, 16,
             RAYWHITE);
    DrawText(TextFormat("FPS: %d", GetFPS()), 15, 35, 16, RAYWHITE);

    DrawTexturePro((player.state == Idle) ? player_texture_idle : player_texture,
                   (Rectangle){player.animation.current_frame * player.frame.width,
                               player.direction * player.frame.height, player.frame.width,
                               player.frame.height},
                   (Rectangle){player.position.x, player.position.y, player.frame.width * SCALE,
                               player.frame.height * SCALE},
                   (Vector2){0, 0}, 0.0f, WHITE);
    EndDrawing();
}

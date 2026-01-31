#include "main.h"
#include "player.h"
#include <raylib.h>

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
    player.position.x = 0;
    player.position.y = 50;
    player.size.width = 16;
    player.size.height = 16;
    player.frame_size.width = 24;
    player.frame_size.height = 24;
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

    // Player movement
    if (IsKeyDown(KEY_W) && player.position.y > 0)
    {
        player.direction = UP;
        player.state = Walking;
        player.position.y -= player.speed;
    }
    if (IsKeyDown(KEY_S) && player.position.y + player.size.height < SCREEN_HEIGHT)
    {
        player.direction = DOWN;
        player.state = Walking;
        player.position.y += player.speed;
    }
    if (IsKeyDown(KEY_A) && player.position.x > 0)
    {
        player.direction = LEFT;
        player.state = Walking;
        player.position.x -= player.speed;
    }
    if (IsKeyDown(KEY_D) && player.position.x + player.size.width < SCREEN_WIDTH)
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
                   (Rectangle){player.animation.current_frame * player.frame_size.width,
                               player.direction * player.frame_size.height, player.frame_size.width,
                               player.frame_size.height},
                   (Rectangle){player.position.x, player.position.y,
                               player.frame_size.width * SCALE, player.frame_size.height * SCALE},
                   (Vector2){0, 0}, 0.0f, WHITE);
    EndDrawing();
}

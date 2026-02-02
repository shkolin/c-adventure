#include "main.h"
#include "player.h"
#include <raylib.h>

// Module variables declaration (local)
static Player player = {0};
static Texture2D player_texture = {0};
static Texture2D player_texture_idle = {0};

static const int DEFAULT_SCREEN_WIDTH = 1280;
static const int DEFAULT_SCREEN_HEIGHT = 720;
static float SCALE = 3.0f;
static const int FPS = 60;

// Main entry point
int main(void)
{
    InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "C Adventure");
    // SetConfigFlags(FLAG_VSYNC_HINT);
    SetTargetFPS(FPS);

    init_game();
    update_scale();

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
    player.state = IDLE;
    player.direction = DIR_DOWN;

    // Initialize player animation
    init_animation(&player.animation, DEFAULT_ANIMATION_SPEED, DEFAULT_NUM_FRAMES);

    player_texture = LoadTexture("../assets/Char_003.png");
    player_texture_idle = LoadTexture("../assets/Char_003_Idle.png");
}

static void update_scale(void)
{
    int height = GetScreenHeight();
    SCALE = 3.0f * ((float)height / 720.0f);
    player.speed = DEFAULT_PLAYER_SPEED * SCALE;
}

static void gameloop(void)
{
    if ((IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)) && IsKeyPressed(KEY_ENTER))
    {
        ToggleFullscreen();
        if (IsWindowResized())
        {
            int monitor = GetCurrentMonitor();
            int monitor_width = GetMonitorWidth(monitor);
            int monitor_height = GetMonitorHeight(monitor);
            SetWindowSize(monitor_width, monitor_height);
        }
        else
        {
            SetWindowSize(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
        }
        update_scale();
    }

    bool pressed_key_up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
    bool pressed_key_down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);
    bool pressed_key_left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    bool pressed_key_right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);

    Vector2 player_sprite_offset = {8, 6};
    float player_x = player.position.x + player_sprite_offset.x * SCALE;
    float player_y = player.position.y + player_sprite_offset.y * SCALE;
    int player_width = player.size.width * SCALE;
    int player_height = player.size.height * SCALE;

    player.state = IDLE;

    // Player movement
    if (pressed_key_up && player_y > 0)
    {
        player.direction = DIR_UP;
        player.state = WALKING;
        player.position.y -= player.speed;
    }
    if (pressed_key_down && player_y + player_height < GetScreenHeight())
    {
        player.direction = DIR_DOWN;
        player.state = WALKING;
        player.position.y += player.speed;
    }
    if (pressed_key_left && player_x > 0)
    {
        player.direction = DIR_LEFT;
        player.state = WALKING;
        player.position.x -= player.speed;
    }
    if (pressed_key_right && player_x + player_width < GetScreenWidth())
    {
        player.direction = DIR_RIGHT;
        player.state = WALKING;
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
    DrawFPS(10, 10);
    DrawTexturePro((player.state == IDLE) ? player_texture_idle : player_texture,
                   (Rectangle){player.animation.current_frame * player.frame.width,
                               player.direction * player.frame.height, player.frame.width,
                               player.frame.height},
                   (Rectangle){player.position.x, player.position.y, player.frame.width * SCALE,
                               player.frame.height * SCALE},
                   (Vector2){0, 0}, 0.0f, WHITE);
    EndDrawing();
}

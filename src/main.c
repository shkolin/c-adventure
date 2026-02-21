#include "main.h"
#include "player.h"
#include <raylib.h>

static Player player = {0};
static Texture2D player_texture = {0};
static Texture2D player_texture_idle = {0};
// static Camera2D camera = {0};

static const int DEFAULT_SCREEN_WIDTH = 1280;
static const int DEFAULT_SCREEN_HEIGHT = 720;
static float SCALE = 3.0f;
static const int FPS = 60;

int main(void)
{
    InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "C Adventure");
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

static void init_game(void)
{
    HideCursor();

    player.position = (Vector2){0, 50};
    player.size = (PlayerSize){8, 18};
    player.frame = (PlayerSize){24, 24};
    player.sprite_offset = (Vector2){8, 6};
    player.speed = DEFAULT_PLAYER_SPEED;
    player.state = IDLE;
    player.direction = DIR_DOWN;

    // camera.target = (Vector2){player.position.x, player.position.y};
    // camera.offset = (Vector2){DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT};
    // camera.rotation = 0.0f;
    // camera.zoom = 1.0f;

    init_player_animation(&player.animation, DEFAULT_ANIMATION_SPEED, DEFAULT_NUM_FRAMES);

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
        if (IsWindowFullscreen())
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

    PlayerInput input = {.up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP),
                         .down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN),
                         .left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT),
                         .right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)};

    update_player_position(&player, input, GetScreenWidth(), GetScreenHeight(), SCALE);
    update_player_animation(&player.animation);
}

static void draw_game(void)
{
    BeginDrawing();
    ClearBackground(DARKGRAY);
    // BeginMode2D(camera);
    DrawTexturePro((player.state == IDLE) ? player_texture_idle : player_texture,
                   (Rectangle){player.animation.current_frame * player.frame.width,
                               player.direction * player.frame.height, player.frame.width,
                               player.frame.height},
                   (Rectangle){player.position.x, player.position.y, player.frame.width * SCALE,
                               player.frame.height * SCALE},
                   (Vector2){0, 0}, 0.0f, WHITE);
    // EndMode2D();
    EndDrawing();
}

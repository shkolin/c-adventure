#include "main.h"
#include "player.h"
#include <raylib.h>
#include <stdio.h>

// Module variables declaration (local)
static Player player = {0};
static Texture2D player_texture = {0};
static Texture2D player_texture_idle = {0};
static Camera2D camera = {0};

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const int FPS = 60;

// Main entry point
int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C Adventure");
  SetTargetFPS(FPS);

  InitGame();

  while (!WindowShouldClose()) {
    UpdateGame();
    DrawGame();
  }

  UnloadTexture(player_texture);
  UnloadTexture(player_texture_idle);

  CloseWindow();
  return 0;
}

// Initialize game variables
static void InitGame(void) {
  // Initialize player variables
  player.position.x = 0;
  player.position.y = 0;
  player.size.width = 24;
  player.size.height = 24;
  player.speed = DEFAULT_PLAYER_SPEED;
  player.state = Idle;
  player.direction = DOWN;
  player.current_frame = 0;
  player.frame_counter = 0;
  player.frames_speed = 16;
  player.num_frames = 4;

  player_texture = LoadTexture("../assets/Char_003.png");
  player_texture_idle = LoadTexture("../assets/Char_003_Idle.png");
}

static void UpdateGame(void) {
  player.state = Idle;

  // Player movement
  if (IsKeyDown(KEY_W) && player.position.y > 0) {
    player.direction = UP;
    player.state = Walking;
    player.position.y -= player.speed;
  }
  if (IsKeyDown(KEY_S) &&
      player.position.y + player.size.height < SCREEN_HEIGHT) {
    player.direction = DOWN;
    player.state = Walking;
    player.position.y += player.speed;
  }
  if (IsKeyDown(KEY_A) && player.position.x > 0) {
    player.direction = LEFT;
    player.state = Walking;
    player.position.x -= player.speed;
  }
  if (IsKeyDown(KEY_D) &&
      player.position.x + player.size.width < SCREEN_WIDTH) {
    player.direction = RIGHT;
    player.state = Walking;
    player.position.x += player.speed;
  }

  // Animation frame update
  player.frame_counter++;
  if (player.frame_counter >= player.frames_speed) {
    player.frame_counter = 0;
    player.current_frame++;
    if (player.current_frame >= player.num_frames) {
      player.current_frame = 0;
    }
  }
}

// Draw game elements
static void DrawGame(void) {
  BeginDrawing();
  ClearBackground(DARKGRAY);
  DrawTexturePro((player.state == Idle) ? player_texture_idle : player_texture,
                 (Rectangle){player.current_frame * player.size.width,
                             player.direction * player.size.height,
                             player.size.width, player.size.height},
                 (Rectangle){player.position.x, player.position.y,
                             player.size.width * 3, player.size.height * 3},
                 (Vector2){0, 0}, 0.0f, WHITE);
  EndDrawing();
}

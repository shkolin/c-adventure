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
static const int FONT_SIZE = 14;

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
  player.size.width = 16;
  player.size.height = 16;
  player.speed = DEFAULT_PLAYER_SPEED;
  player.state = Idle;

  player_texture = LoadTexture("../assets/Char_003.png");
  player_texture_idle = LoadTexture("../assets/Char_003_Idle.png");
}

static void UpdateGame(void) {
  // Player movement
  if (IsKeyDown(KEY_W) && player.position.y > 0) {
    player.direction = UP;
    player.position.y -= player.speed;
  }
  if (IsKeyDown(KEY_S) &&
      player.position.y + player.size.height < SCREEN_HEIGHT) {
    player.direction = DOWN;
    player.position.y += player.speed;
  }
  if (IsKeyDown(KEY_A) && player.position.x > 0) {
    player.direction = LEFT;
    player.position.x -= player.speed;
  }
  if (IsKeyDown(KEY_D) &&
      player.position.x + player.size.width < SCREEN_WIDTH) {
    player.direction = RIGHT;
    player.position.x += player.speed;
  }
}

// Draw game elements
static void DrawGame(void) {
  BeginDrawing();
  ClearBackground(DARKGRAY);
  DrawFPS(10, 10);
  EndDrawing();
}

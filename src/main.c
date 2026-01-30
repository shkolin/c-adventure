#include "raylib.h"
#include <stdio.h>

typedef struct Player {
  Vector2 position;
  float speed;
} Player;

// Module functions declaration
static void init_game(void);
static void update_game(void);
static void draw_game(void);

// Module variables declaration (local)
static Player player = {0};
static Texture2D player_texture = {0};
static RenderTexture2D render_target = {0};

static const int SCREEN_WIDTH = 432;
static const int SCREEN_HEIGHT = 270;
static const int SCALE = 3;
static const int FPS = 60;
static const int FONT_SIZE = 14;

// Main entry point
int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE, "My Game");
  SetTargetFPS(FPS);

  init_game();

  while (!WindowShouldClose()) {
    update_game();
    draw_game();
  }

  UnloadRenderTexture(render_target);
  UnloadTexture(player_texture);

  CloseWindow();
  return 0;
}

// Initialize game variables
static void init_game(void) {
  render_target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
  SetTextureFilter(render_target.texture, TEXTURE_FILTER_POINT);
  // Initialize player variables
  player.position.x = 0;
  player.position.y = 0;
  player.speed = 1.0f;

  Image player_image = LoadImage("../assets/character.png");
  player_texture = LoadTextureFromImage(player_image);

  UnloadImage(player_image);
}

static void update_game(void) {
  // Player movement
  if (IsKeyDown(KEY_W)) {
    player.position.y -= player.speed;
  }
  if (IsKeyDown(KEY_S)) {
    player.position.y += player.speed;
  }
  if (IsKeyDown(KEY_A)) {
    player.position.x -= player.speed;
  }
  if (IsKeyDown(KEY_D)) {
    player.position.x += player.speed;
  }
  // Movement bounds
  if (player.position.x < -2) {
    player.position.x = -2;
  }

  if (player.position.y < 0) {
    player.position.y = 0;
  }
}

// Draw game elements
static void draw_game(void) {
  BeginTextureMode(render_target);
  ClearBackground(DARKGRAY);
  DrawTexture(player_texture, player.position.x, player.position.y, WHITE);
  DrawFPS(10, 10);
  EndTextureMode();

  BeginDrawing();
  ClearBackground(BLACK);
  DrawTexturePro(render_target.texture,
                 (Rectangle){0, 0, SCREEN_WIDTH, -SCREEN_HEIGHT},
                 (Rectangle){0, 0, SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE},
                 (Vector2){0, 0}, 0.0f, WHITE);
  EndDrawing();
}

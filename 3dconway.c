#include "3dconway.h"
#include <raylib.h>

int main() {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D Conway's Game of Life");

  Vector3 cameraSpherePosition = {50.0f, +45.0f, +45.0f}; // (r, θ, φ)
  Camera3D camera = {
      .position = {0.0f, 0.0f, 0.0f},
      .target = {0.0f, 0.0f, 0.0f},
      .up = {0.0f, 1.0f, 0.0f},
      .fovy = 45.0f,
      .projection = CAMERA_PERSPECTIVE,
  };

  int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE] = {0};

  while (!WindowShouldClose()) {
    BeginDrawing();
    BeginMode3D(camera);
    handleCameraInput(&camera, &cameraSpherePosition);
    moveCamera(&camera, &cameraSpherePosition);
    ClearBackground(GetColor(BACKGROUND_COLOR));
    randomizeGrid(grid);

    DrawGrid(100, 1.0f);

    EndMode3D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

void moveCamera(Camera3D *cam, Vector3 *pos) {
  cam->position.x = pos->x * cosf(pos->y) * sinf(pos->z);
  cam->position.y = pos->x * cosf(pos->z);
  cam->position.z = pos->x * sinf(pos->z) * sinf(pos->y);
}

void randomizeGrid(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]) {
  for (int x = 0; x < GRID_SIZE; x++)
    for (int y = 0; y < GRID_SIZE; y++)
      for (int z = 0; z < GRID_SIZE; z++)
        grid[x][y][z] = GetRandomValue(0, 1);
}

void handleCameraInput(Camera3D *cam, Vector3 *pos) {
  if (IsKeyDown(KEY_S))
    pos->x += 5.1f * GetFrameTime();
  if (IsKeyDown(KEY_W))
    pos->x -= 5.1f * GetFrameTime();
  if (IsKeyDown(KEY_D))
    pos->y -= 0.1f * GetFrameTime();
  if (IsKeyDown(KEY_A))
    pos->y += 0.1f * GetFrameTime();
  if (IsKeyDown(KEY_Q))
    pos->z -= 0.1f * GetFrameTime();
  if (IsKeyDown(KEY_E))
    pos->z += 0.1f * GetFrameTime();
}

#include "3dconway.h"
#include <raylib.h>

int main() {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D Conway's Game of Life");

  Vector3 cameraSpherePosition = {GRID_SIZE * CELL_SIZE * 3, +45.0f,
                                  +45.0f}; // (r, θ, φ)
  Camera3D camera = {
      .position = {0.0f, 0.0f, 0.0f},
      .target = {0.0f, 0.0f, 0.0f},
      .up = {0.0f, 1.0f, 0.0f},
      .fovy = 45.0f,
      .projection = CAMERA_PERSPECTIVE,
  };

  int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE] = {0};

  int isRotating = 0;
  int isPaused = 0;
  randomizeTopLayer(grid);

  double lastTime = GetTime();
  while (!WindowShouldClose()) {
    BeginDrawing();
    BeginMode3D(camera);

    if (IsKeyPressed(KEY_SPACE)) {
      updateGrid(grid);
    }

    if (IsKeyPressed(KEY_R)) {
      randomizeGrid(grid);
    }

    if (IsKeyPressed(KEY_ENTER)) {
      isRotating = !isRotating;
    }
    if (isRotating) {
      cameraSpherePosition.y += CAMERA_SPEED * GetFrameTime() * 0.5;
    }

    if (IsKeyPressed(KEY_P)) {
      isPaused = !isPaused;
    }

    if (!isPaused) {
      if (GetTime() - lastTime > SIMULATION_SPEED) {
        lastTime = GetTime();
        updateGrid(grid);
      }
    }

    handleCameraInput(&camera, &cameraSpherePosition);
    moveCamera(&camera, &cameraSpherePosition);
    ClearBackground(GetColor(BACKGROUND_COLOR));

    drawGrid(grid);

    EndMode3D();
    DrawFPS(10, 10);
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

void randomizeTopLayer(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]) {
  for (int x = 0; x < GRID_SIZE; x++)
    for (int y = 0; y < GRID_SIZE; y++)
      grid[x][GRID_SIZE - 1][y] = GetRandomValue(0, 1);
}

int countNeighbors(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE], int x, int y,
                   int z) {
  int count = 0;
  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++)
      for (int k = -1; k <= 1; k++)
        if (x + i >= 0 && x + i < GRID_SIZE && y + j >= 0 &&
            y + j < GRID_SIZE && z + k >= 0 && z + k < GRID_SIZE)
          count += grid[x + i][y + j][z + k];
  count -= grid[x][y][z];
  return count;
}

int countNeighbors2D(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE], int x, int z) {
  int count = 0;
  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++)
      if (x + i >= 0 && x + i < GRID_SIZE && z + j >= 0 && z + j < GRID_SIZE)
        count += grid[x + i][GRID_SIZE - 1][z + j];
  count -= grid[x][GRID_SIZE - 1][z];
  return count;
}

void updateGridLayer(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]) {
  for (int x = 0; x < GRID_SIZE; x++)
    for (int z = 0; z < GRID_SIZE; z++) {
      int neighbors = countNeighbors2D(grid, x, z);
      if (grid[x][GRID_SIZE - 1][z] == 1) {
        if (neighbors < 2 || neighbors > 3)
          grid[x][GRID_SIZE - 1][z] = 0;
      } else {
        if (neighbors == 3)
          grid[x][GRID_SIZE - 1][z] = 1;
      }
    }
}

void updateGrid(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]) {
  shiftGridDown(grid);
  updateGridLayer(grid);
}

void drawGrid(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]) {
  float x = -GRID_SIZE * CELL_SIZE / 2;
  float y = -GRID_SIZE * CELL_SIZE / 2;
  float z = -GRID_SIZE * CELL_SIZE / 2;

  DrawCubeWires((Vector3){0, 0, 0}, GRID_SIZE * CELL_SIZE,
                GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE,
                GetColor(0xf0f0f044));

  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      for (int k = 0; k < GRID_SIZE; k++) {
        if (grid[i][j][k] == 1) {
          Color col = GetColor(CELL_COLOR);
          Vector3 colHSV = ColorToHSV(col);
          colHSV.y = countNeighbors(grid, i, j, k) * 30;
          col = ColorFromHSV(colHSV.x, colHSV.y, colHSV.z);
          if (j == GRID_SIZE - 1)
            col = RAYWHITE;
          DrawCube((Vector3){x, y, z}, CELL_SIZE, CELL_SIZE, CELL_SIZE, col);
          DrawCubeWires((Vector3){x, y, z}, CELL_SIZE, CELL_SIZE, CELL_SIZE,
                        GetColor(0x000000ff));
        }
        z += CELL_SIZE;
      }
      y += CELL_SIZE;
      z = -GRID_SIZE * CELL_SIZE / 2;
    }
    x += CELL_SIZE;
    y = -GRID_SIZE * CELL_SIZE / 2;
  }
}

void shiftGridDown(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]) {
  for (int x = 0; x < GRID_SIZE; x++)
    for (int y = 0; y < GRID_SIZE - 1; y++)
      for (int z = 0; z < GRID_SIZE; z++)
        grid[x][y][z] = grid[x][y + 1][z];
}

void handleCameraInput(Camera3D *cam, Vector3 *pos) {
  if (IsKeyDown(KEY_S))
    pos->x += CAMERA_SPEED * CELL_SIZE * 5 * GetFrameTime();
  if (IsKeyDown(KEY_W))
    pos->x -= CAMERA_SPEED * CELL_SIZE * 5 * GetFrameTime();
  if (IsKeyDown(KEY_D))
    pos->y -= CAMERA_SPEED * GetFrameTime();
  if (IsKeyDown(KEY_A))
    pos->y += CAMERA_SPEED * GetFrameTime();
  if (IsKeyDown(KEY_Q))
    pos->z -= CAMERA_SPEED * GetFrameTime();
  if (IsKeyDown(KEY_E))
    pos->z += CAMERA_SPEED * GetFrameTime();
}

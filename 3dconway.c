#include "3dconway.h"
#include <raylib.h>

int COLOR_SHIFT_TYPE = 1; // 1 = hue, 2 = saturation, 3 = value

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

  int isRotating = 1;
  int isPaused = 0;
  int showInstructions = 0;

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

    if (IsKeyPressed(KEY_C)) {
      COLOR_SHIFT_TYPE = (COLOR_SHIFT_TYPE + 1) % 4;
    }

    if (IsKeyPressed(KEY_SLASH) &&
        (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))) {
      showInstructions = !showInstructions;
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
    if (showInstructions) {
      drawInstructions();
    }
    int posX = GetScreenWidth() / 2 -
               MeasureText("Press [?] to toggle instructions", 20) / 2;
    DrawText("Press [?] to toggle instructions", posX, 15, 20, RAYWHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
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

void updateGrid(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]) {
  shiftGridDown(grid);
  updateGridLayerConway(grid);
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
          switch (COLOR_SHIFT_TYPE) {
          case 1:
            colHSV.x = countNeighbors(grid, i, j, k) * 30;
            break;
          case 2:
            colHSV.y = countNeighbors(grid, i, j, k) * 30;
            break;
          case 3:
            colHSV.z = countNeighbors(grid, i, j, k) * 30;
            break;
          }

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

void drawInstructions() {
  DrawText("Controls:", 10, GetScreenHeight() - 150, 25, GetColor(0xF0F0F0FF));
  DrawText("WASD + QE | Mouse => Move Camera", 10, GetScreenHeight() - 120, 20,
           GRAY);
  DrawText("P => Pause", 10, GetScreenHeight() - 100, 20, GRAY);
  DrawText("Space => Next Generation", 10, GetScreenHeight() - 80, 20, GRAY);
  DrawText("C => Change Color Shift", 10, GetScreenHeight() - 60, 20, GRAY);
  DrawText("Enter => Toggle Rotation", 10, GetScreenHeight() - 40, 20, GRAY);
  DrawText("R => Randomize Grid", 10, GetScreenHeight() - 20, 20, GRAY);
}

void shiftGridDown(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]) {
  for (int x = 0; x < GRID_SIZE; x++)
    for (int y = 0; y < GRID_SIZE - 1; y++)
      for (int z = 0; z < GRID_SIZE; z++)
        grid[x][y][z] = grid[x][y + 1][z];
}

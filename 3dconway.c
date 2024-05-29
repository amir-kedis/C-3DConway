#include "3dconway.h"
#include <raylib.h>

int main() {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D Conway's Game of Life");

  Vector3 cameraSpherePosition = {10.0f, 45.0f, -45.0f}; // (r, θ, φ)
  Camera3D camera = {
      .position = {0.0f, 0.0f, 0.0f},
      .target = {0.0f, 0.0f, 0.0f},
      .up = {0.0f, 1.0f, 0.0f},
      .fovy = 45.0f,
      .projection = CAMERA_PERSPECTIVE,
  };

  while (!WindowShouldClose()) {
    BeginDrawing();
    BeginMode3D(camera);
    moveCamera(&camera, &cameraSpherePosition);

    EndMode3D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

void moveCamera(Camera3D *cam, Vector3 *pos) {
  cam->position.x = cosf(pos->z) * sinf(pos->y) * pos->x;
  cam->position.y = sinf(pos->z) * sinf(pos->y) * pos->x;
  cam->position.z = cosf(pos->y) * pos->x;
}

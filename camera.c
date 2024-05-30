#include "3dconway.h"

/**
 * moveCamera - Move the camera + transform the position to cartesian
 * coordinates
 * @cam: Camera3D pointer
 * @pos: Vector3 pointer
 */
void moveCamera(Camera3D *cam, Vector3 *pos) {
  cam->position.x = pos->x * cosf(pos->y) * sinf(pos->z);
  cam->position.y = pos->x * cosf(pos->z);
  cam->position.z = pos->x * sinf(pos->z) * sinf(pos->y);
}

/**
 * handleCameraInput - Handle camera input (keyboard + mouse)
 * @cam: Camera3D pointer
 * @pos: Vector3 pointer
 */
void handleCameraInput(Camera3D *cam, Vector3 *pos) {
  // Keyboard input WASD + QE keys to move camera
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

  // Mouse input to rotate camera
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    pos->y += GetMouseDelta().x * CAMERA_SPEED * GetFrameTime() * 0.1;
    pos->z += -1 * GetMouseDelta().y * CAMERA_SPEED * GetFrameTime() * 0.1;
  }

  // Mouse scroll to zoom in/out
  float scroll = GetMouseWheelMove();
  if (scroll != 0) {
    pos->x += -1 * scroll * CAMERA_SPEED * CELL_SIZE * 50 * GetFrameTime();
  }
}

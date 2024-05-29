/** ================================================================
 * Author: Amir Kedis
 * Description: Conway's Game of Life in 3D (2D + stack generation)
 * ================================================================= */

// ==> INCLUDES
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==> SCREEN SETTINGS
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_TITLE "3D Conway's Game of Life"
#define BACKGROUND_COLOR 0x222831FF

// ==> CAMERA SETTINGS
#define CAMERA_SPEED 1.0f

// ==> GAME SETTINGS
#define GRID_SIZE 10
#define CELL_SIZE 5.0f
#define CELL_COLOR 0xF2A365FF

// ==> FUNCTION PROTOTYPES
void moveCamera(Camera3D *cam, Vector3 *pos);
void randomizeGrid(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]);
void handleCameraInput(Camera3D *cam, Vector3 *pos);

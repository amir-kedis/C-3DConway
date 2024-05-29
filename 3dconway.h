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
#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1440
#define SCREEN_TITLE "3D Conway's Game of Life"
#define BACKGROUND_COLOR 0x1E1E1EFF

// ==> CAMERA SETTINGS
#define CAMERA_SPEED 1.0f

// ==> GAME SETTINGS
#define GRID_SIZE 30
#define CELL_SIZE 10.0f
#define CELL_COLOR 0x76ABAEFF
#define SIMULATION_SPEED 0.05f

// ==> FUNCTION PROTOTYPES
void moveCamera(Camera3D *cam, Vector3 *pos);
void randomizeGrid(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]);
void randomizeTopLayer(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]);
void handleCameraInput(Camera3D *cam, Vector3 *pos);
void drawGrid(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]);
void shiftGridDown(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]);
int countNeighbors(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE], int x, int y,
                   int z);
int countNeighbors2D(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE], int x, int z);
void updateGridLayer(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]);
void updateGrid(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]);

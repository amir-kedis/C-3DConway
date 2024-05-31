#include "3dconway.h"

/**
 * updateGridLayerConway - conway game of life rules on top layer
 * @grid: 3D grid
 */
void updateGridLayerConway(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]) {
  int newGrid[GRID_SIZE][GRID_SIZE][GRID_SIZE];
  for (int i = 0; i < GRID_SIZE; i++)
    for (int j = 0; j < GRID_SIZE; j++)
      for (int k = 0; k < GRID_SIZE; k++)
        newGrid[i][j][k] = grid[i][j][k];

  for (int x = 0; x < GRID_SIZE; x++)
    for (int z = 0; z < GRID_SIZE; z++) {
      int neighbors = countNeighbors2D(grid, x, z);

      if (neighbors < 2)
        newGrid[x][GRID_SIZE - 1][z] = 0;
      else if (neighbors == 3)
        newGrid[x][GRID_SIZE - 1][z] = 1;
      else if (neighbors > 3)
        newGrid[x][GRID_SIZE - 1][z] = 0;
      else
        newGrid[x][GRID_SIZE - 1][z] = grid[x][GRID_SIZE - 1][z];
    }

  memcpy(grid, newGrid, sizeof(newGrid));
}

/**
 * countNeighbors2D - Count neighbors in top layer only
 * @grid: 3D grid
 * @x: x position
 * @z: z position
 * Return: Number of neighbors
 */
int countNeighbors2D(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE], int x, int z) {
  int count = 0;
  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++) {
      int row = (x + i + GRID_SIZE) % GRID_SIZE;
      int col = (z + j + GRID_SIZE) % GRID_SIZE;
      count += grid[row][GRID_SIZE - 1][col];
    }
  count -= grid[x][GRID_SIZE - 1][z];
  return count;
}

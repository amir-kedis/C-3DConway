#include "3dconway.h"

/**
 * updateGridLayerConway - conway game of life rules on top layer
 * @grid: 3D grid
 */
void updateGridLayerConway(int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]) {
  for (int x = 0; x < GRID_SIZE; x++)
    for (int z = 0; z < GRID_SIZE; z++) {
      int neighbors = countNeighbors2D(grid, x, z);
      if (neighbors < 2)
        grid[x][GRID_SIZE - 1][z] = 0;
      else if (neighbors == 3)
        grid[x][GRID_SIZE - 1][z] = 1;
      else if (neighbors > 3)
        grid[x][GRID_SIZE - 1][z] = 0;
    }
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
    for (int j = -1; j <= 1; j++)
      if (x + i >= 0 && x + i < GRID_SIZE && z + j >= 0 && z + j < GRID_SIZE)
        count += grid[x + i][GRID_SIZE - 1][z + j];
  count -= grid[x][GRID_SIZE - 1][z];
  return count;
}

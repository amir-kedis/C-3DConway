# 3D visualization of Conway's Game of Life, written in C

## 📽 Demo

https://github.com/amir-kedis/C-3DCownay/assets/88613195/b0696874-1eb2-4af6-80f5-42f706b097ff

This my trial to combine 3D graphics with Conway's Game of Life and practice my C skills.
The idea is to visualize the game of life in 3D space, every cube of the top layer represents a cell in the game of life.
each layer represents a generation so the y axis is the time axis. colors represent the number of neighbors of each cell.

## 🚀 To run the simulation install raylib and run the following command:

```bash
make
```

## ⚙️ Controls

- `WASD+QE` or `mouse`: Move camera
- `P`: Pause simulation
- `R`: Randomize grid
- `C`: Change color shift type
- `SPACE`: Step simulation
- `ENTER`: Toggle Rotation
- `?`: Show Instructions

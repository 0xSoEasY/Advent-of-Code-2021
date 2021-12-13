#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 5

#define MARKED 1
#define UNMARKED 0

typedef struct {
    // Access with x and y positions : bingo_grid.grid[y][x]
    int grid[GRID_SIZE][GRID_SIZE];
    int marked[GRID_SIZE][GRID_SIZE];
    int has_won;
} bingo_grid;
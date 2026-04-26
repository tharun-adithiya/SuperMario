#include "Tilemap.h"
#include "raylib.h"
#include <iostream>
using namespace std;
Tilemap::Tilemap(int width, int height, int tileSize)
{
    this->width = width;
    this->height = height;
    this->tileSize = tileSize;

    grid.resize(height, vector<int>(width, 0)); // Initialize grid with default tile type (0)
}

void Tilemap::Load()
{
    // Loading tile data here. For now, it is hardcoded for simplicity.

    for(int x=0;x<width;x++)
    {
        if(x==width-1) break;
        grid[height-1][x] = TileType::Ground; // Set bottom row to ground
    }
    grid[height-5][5] = TileType::Ground; // Add a floating platform for testing
    grid[height-5][6] = TileType::Ground;
    grid[height-5][7] = TileType::Ground;
}

void Tilemap::Render()
{
    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width;x++)
        {
            int tileType = grid[y][x];
            if(tileType == TileType::Ground) // Ground tile
            {
                DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, DARKGREEN);
            }
        }
    }
}

int Tilemap::GetTile(int x, int y) const
{
    if(x < 0 || x >= width || y < 0 || y >= height)
        return -1; // Out of bounds
    return grid[y][x];
}


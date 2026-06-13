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
    grid2.resize(height, vector<Tile>(width, Tile())); // Initialize grid2 to fix exception
}

void Tilemap::Load()
{
    // Loading tile data here. For now, it is hardcoded for simplicity.

    for(int x=0;x<width;x++)
    {
        if(x==width-1) break;
        //grid[height-1][x] = TileType::Ground; // Set bottom row to ground
        Vector2D tilePos = Vector2D(x * tileSize, (height - 2) * tileSize);
        grid2[height - 2][x] = Tile(MyRect(Vector2D(tileSize, tileSize), tilePos), TileType::Ground);
        //grid2[height-1][x] = Tile(MyRect(Vector2D(tileSize,tileSize),Vector2D(0,0)),TileType::Ground); // Set bottom row to ground
    }
    for(int x=4;x<8;x++)
    {
        Vector2D tilePos = Vector2D(x * tileSize, (height - 3) * tileSize);
        grid2[height-3][x]=Tile(MyRect(Vector2D(tileSize, tileSize), tilePos), TileType::Ground);
    }
    

    /*grid[height-5][5] = TileType::Ground; // Add a floating platform for testing
    grid[height-5][6] = TileType::Ground;
    grid[height-5][7] = TileType::Ground;*/
}

void Tilemap::Render()
{
    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width;x++)
        {
            int tileType = grid[y][x];
            Tile tile=grid2[y][x];
            /*if(tileType == TileType::Ground) // Ground tile
            {
                DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, DARKGREEN);
            }*/
            if(tile.tileType == TileType::Ground) // Ground tile
            {
                DrawRectangle(x * tile.collider.size.x, y * tile.collider.size.y, tileSize, tileSize, BLACK);
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


Tile Tilemap::GetActualTile(int x,int y) const
{
    if(x < 0 || x >= width || y < 0 || y >= height)
        return Tile(); // Out of bounds
    return grid2[y][x];
}

vector<Tile> Tilemap::GetSolidTiles()
{
    vector<Tile> solidTiles;
    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width;x++)
        {
            if(grid2[y][x].tileType==TileType::Ground) 
            {
                solidTiles.push_back(grid2[y][x]);
                //std::cout<<"Added Tile indices:"<<y<<" "<<x;   
            }
        }
    }
    return solidTiles;
}
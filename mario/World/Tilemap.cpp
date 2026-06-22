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
    for(int y=3;y<7;y++)
    {
        Vector2D tilePos = Vector2D(10 * tileSize, (height - y) * tileSize);
        grid2[height-y][10]=Tile(MyRect(Vector2D(tileSize, tileSize), tilePos), TileType::Ground);
    }
    
    grid2[height-5][9]=Tile(MyRect(Vector2D(tileSize, tileSize), Vector2D(9*tileSize,(height-5)*tileSize)),TileType::Ground);
    grid2[height-4][9]=Tile(MyRect(Vector2D(tileSize, tileSize), Vector2D(9*tileSize,(height-5)*tileSize)),TileType::Ground);
    grid2[height-3][9]=Tile(MyRect(Vector2D(tileSize, tileSize), Vector2D(9*tileSize,(height-3)*tileSize)),TileType::Ground);
    grid2[height-4][8]=Tile(MyRect(Vector2D(tileSize, tileSize), Vector2D(8*tileSize,(height-4)*tileSize)),TileType::Ground);
    grid2[height-3][8]=Tile(MyRect(Vector2D(tileSize, tileSize), Vector2D(8*tileSize,(height-3)*tileSize)),TileType::Ground);
    grid2[height-2][8]=Tile(MyRect(Vector2D(tileSize, tileSize), Vector2D(8*tileSize,(height-2)*tileSize)),TileType::Ground);
    


}

void Tilemap::Render()
{
    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width;x++)
        {
            // int tileType = grid[y][x]; // Unused
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

vector<Tile> Tilemap::GetNearbySolidTiles(const MyRect& bounds, Vector2D velocity, float dt)
{
    vector<Tile> solidTiles;
    
    //Calculates the bounding box of the player's entire movement path for this frame
    float minX = std::min(bounds.position.x, bounds.position.x + velocity.x * dt);
    float minY = std::min(bounds.position.y, bounds.position.y + velocity.y * dt);
    float maxX = std::max(bounds.position.x + bounds.size.x, bounds.position.x + bounds.size.x + velocity.x * dt);
    float maxY = std::max(bounds.position.y + bounds.size.y, bounds.position.y + bounds.size.y + velocity.y * dt);

    // Converts to grid coordinates (and expand by 1 to be safe against floating point rounding)
    int startX = std::max(0, (int)(minX / tileSize) - 1);
    int startY = std::max(0, (int)(minY / tileSize) - 1);
    int endX = std::min(width - 1, (int)(maxX / tileSize) + 1);
    int endY = std::min(height - 1, (int)(maxY / tileSize) + 1);

    // Loops through only this tiny section of the grid
    for(int y = startY; y <= endY; y++)
    {
        for(int x = startX; x <= endX; x++)
        {
            if(grid2[y][x].tileType == TileType::Ground) 
            {
                solidTiles.push_back(grid2[y][x]);
            }
        }
    }
    
    return solidTiles;
}
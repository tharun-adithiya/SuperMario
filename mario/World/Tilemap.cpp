#include "Tilemap.h"
#include "raylib.h"
#include <memory>
#include <iostream>
#include <fstream>
#include "Entities/Block.h"
using namespace std;
Tilemap::Tilemap(int width, int height, int tileSize)
{
    this->width = width;
    this->height = height;
    this->tileSize = tileSize;

    grid.resize(height, vector<int>(width, 0)); // Initialize grid with default tile type (0)
    tileGrid.resize(height, vector<Tile>(width, Tile())); // Initialize grid2 to fix exception
    
}

void Tilemap::Load()
{
    vector<string> levelString;
    
    std::ifstream levelFile("mario/World/MarioLevel.txt");
    string line;
    while(std::getline(levelFile,line))
    {
        levelString.push_back(line);
    }

    // Loading tile data here. For now, it is hardcoded for simplicity.
    coins.push_back(Coin(8.0f,Vector2D(200,450)));
    coins.push_back(Coin(8.0f,Vector2D(250,450)));
    /*for(int x=0;x<width;x++)
    {
        if(x==width-1) break;
        //grid[height-1][x] = TileType::Ground; // Set bottom row to ground
        Vector2D tilePos = Vector2D(x * tileSize, (height - 2) * tileSize);
        tileGrid[height - 2][x] = Tile(boxCollider2D(Vector2D(tileSize, tileSize), tilePos), TileType::Ground);
        //grid2[height-1][x] = Tile(MyRect(Vector2D(tileSize,tileSize),Vector2D(0,0)),TileType::Ground); // Set bottom row to ground

    }*/
    for(int y=0; y < height && y < levelString.size(); y++)
    {
        for(int x=0; x < width && x < levelString[y].size(); x++)
        {
            if(levelString[y][x]=='1')
            {
                Vector2D tilePos = Vector2D(x * tileSize, y * tileSize);
                tileGrid[y][x]=Tile(boxCollider2D(Vector2D(tileSize, tileSize), tilePos), TileType::Ground);
            }
            else if(levelString[y][x]=='2')
            {
                Vector2D blockPos = Vector2D(x * tileSize, y * tileSize);
                Vector2D blockSize= Vector2D(tileSize,tileSize);
                interactiveBlocks.push_back(std::make_unique<BreakableBlock>(blockPos,blockSize));
            }
        }
    }
    
    


}

void Tilemap::Render()
{
    
    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width;x++)
        {
            // int tileType = grid[y][x]; // Unused
            Tile tile=tileGrid[y][x];
            /*if(tileType == TileType::Ground) // Ground tile
            {
                DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, DARKGREEN);
            }*/
            if(tile.tileType == TileType::Ground) // Ground tile
            {
                DrawRectangleV((Vector2){x * tile.collider.size.x, y * tile.collider.size.y}, (Vector2){(float)tileSize, (float)tileSize}, BLACK);
            }

        }
    }
    //Renders Interactible block
    for(auto& block : interactiveBlocks)
    {
        block->Render();
    }
    //RenderCoins
    for(size_t i=0;i<coins.size();i++)
    {
        if (coins[i].isCollected) continue;
        DrawCircleV((Vector2){coins[i].position.x, coins[i].position.y}, coins[i].radius, YELLOW);
        DrawRectangleLinesEx((Rectangle){coins[i].triggerCollider.position.x, coins[i].triggerCollider.position.y, coins[i].triggerCollider.size.x, coins[i].triggerCollider.size.y}, 1.0f, GREEN);  //Collider bounds
    }
}
void Tilemap::Update(float dt)
{
    for(auto& block : interactiveBlocks)
    {
        block->Update(dt);
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
    return tileGrid[y][x];
}

vector<Tile> Tilemap::GetSolidTiles()
{
    vector<Tile> solidTiles;
    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width;x++)
        {
            if(tileGrid[y][x].tileType==TileType::Ground) 
            {
                solidTiles.push_back(tileGrid[y][x]);
                //std::cout<<"Added Tile indices:"<<y<<" "<<x;   
            }
        }
    }
    return solidTiles;
}

vector<Tile> Tilemap::GetNearbySolidTiles(const boxCollider2D& bounds, Vector2D velocity, float dt)
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
            if(tileGrid[y][x].tileType == TileType::Ground) 
            {
                solidTiles.push_back(tileGrid[y][x]);
            }
        }
    }
    
    return solidTiles;
}

vector<Coin>& Tilemap:: GetAllCoins()
{
    return coins;
}
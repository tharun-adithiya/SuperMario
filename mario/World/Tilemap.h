#pragma once
#include "vector"
#include "Math/AABB.h"
using namespace std;

enum TileType
{
    Empty,
    Ground,
};

class Tilemap
{
    int width;
    int height;
    int tileSize;

    vector<vector<int>> grid; // 2D vector to hold tile data

    public:
    Tilemap() : width(0), height(0), tileSize(0) {}
    Tilemap(int width, int height, int tileSize);
    void Load();
    void Render();

    int GetTile(int x, int y) const; // Get tile type at specific coordinates
    int GetTileSize() { return tileSize; } 
    AABB GetTileAABB(int x, int y) { return AABB(Vector2D(x*tileSize, y*tileSize), Vector2D((x+1)*tileSize, (y+1)*tileSize)); } //Gets AABB for a specific tile.
    
};
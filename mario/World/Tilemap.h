#pragma once
#include "vector"
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
};
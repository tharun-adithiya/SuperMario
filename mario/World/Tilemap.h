#pragma once
#include "vector"
#include "Math/AABB.h"
#include <memory>
#include "Entities/Block.h"
using namespace std;


enum TileType
{
    Empty,
    Ground,
};

struct Coin
{
    Vector2D position;
    float radius;
    bool isCollected;
    boxCollider2D triggerCollider;
    bool operator ==(const Coin&) const = default;
    Coin()
    {
        position={0,0};
        radius=0.5f;
        isCollected=false;
        triggerCollider= boxCollider2D(Vector2D(radius*2,radius*2), Vector2D(position.x - radius, position.y - radius));
        triggerCollider.isTrigger=true;
    }
    Coin(float radius, Vector2D position) : position(position), radius(radius) {
        isCollected=false;
        triggerCollider= boxCollider2D(Vector2D(radius*2,radius*2), Vector2D(position.x-radius, position.y-radius));
        triggerCollider.isTrigger=true;
    }

    void DisableCoin()
    {
        this->isCollected = true;
    }
};

struct LevelEndCollider
{
    Vector2D position;
    Vector2D size;
    boxCollider2D collider;
    LevelEndCollider()
    {
        position= Vector2D(0,0);
        size= Vector2D();
        collider= boxCollider2D(size,position);
    }
    LevelEndCollider(Vector2D position, Vector2D size) : position(position), size(size)
    {
        collider= boxCollider2D(this->size,this->position);
    }
};

struct GridPos
{
    int x;
    int y;
};

struct Tile
{
    boxCollider2D collider;
    TileType tileType;

    Tile() : collider(Vector2D(0,0), Vector2D(0,0)), tileType(TileType::Empty) {}
    Tile(boxCollider2D collider, TileType tileType) : collider(collider),tileType(tileType)
    {}
};

class Tilemap
{
    int width;
    int height;
    int tileSize;
    LevelEndCollider end;
    std::vector<std::unique_ptr<Block>> interactiveBlocks;
    vector<vector<int>> grid; // 2D vector to hold tile data
    vector<vector<Tile>> tileGrid;
    vector<Coin> coins;
    public:
    Tilemap() : width(0), height(0), tileSize(0) {}
    Tilemap(int width, int height, int tileSize);
    void Update(float dt);
    void Load();
    void ResetWorldItems();
    void Render();

    int GetTile(int x, int y) const; // Get tile type at specific coordinates
    GridPos WorldToGridCenter(Vector2D worldPos);
    vector<std::unique_ptr<Block>>& GetAllBlocks();
    Tile GetActualTile(int x,int y) const;
    vector<Tile> GetSolidTiles();
    vector<Tile> GetNearbySolidTiles(const boxCollider2D& bounds, Vector2D velocity, float dt);
    vector<Coin> GetNearByCoins(const boxCollider2D& bounds, Vector2D velocity, float dt);
    vector<Coin>& GetAllCoins();
    int GetTileSize() { return tileSize; } 
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    boxCollider2D GetLevelEndCollider() {return end.collider;}
    //AABB GetTileAABB(int x, int y) { return AABB(Vector2D(x*tileSize, y*tileSize), Vector2D((x+1)*tileSize, (y+1)*tileSize)); } //Gets AABB for a specific tile.
    
};
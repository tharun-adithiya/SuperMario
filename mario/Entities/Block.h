#include "raylib.h"
#include "Math/Vector.h"
#include "Math/AABB.h"
#pragma once


enum class BlockType
{
    BreakableBlock,
    CoinBlock,
};

class Block
{   
    protected:
       
        
        
    public:
        Vector2D position;
        Vector2D size;
        BlockType type;
        boxCollider2D collider;
        Texture2D blockImage;
        bool isBroken;
        Block(){}
        Block(Vector2D position, Vector2D size) : position (position) ,size(size)
        {}
        virtual ~Block() = default;
        virtual void OnHitFromBelow();
        virtual void Update(float dt);
        virtual void Render();
};

class BreakableBlock : public Block
{
    public:
        
        float startY;
        BreakableBlock(){
            type= BlockType::BreakableBlock;
            position= Vector2D(0,0);
            size=Vector2D(0,0);
            isBroken=false;
            startY=0;
        }
        BreakableBlock(Vector2D position, Vector2D size) : Block(position,size)
        {
            type= BlockType::BreakableBlock;
            isBroken=false;
            startY = position.y;
            collider = boxCollider2D(size,position);
        }
        void Update(float dt) override;
        void Render() override;
        void OnHitFromBelow() override;   
};

class CoinBlock : public Block
{
    public:
        BlockType type= BlockType::CoinBlock;
        int numberOfCoins;
        Texture2D imageAfterBroke;                                                                                                                                                                                  
        void Update(float dt) override;
        void Render() override;
        void OnHitFromBelow() override;
        
};

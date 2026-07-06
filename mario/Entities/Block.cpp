#include "Block.h"

void Block:: Update(float dt)
{   

}

void Block:: Render()
{

}

void BreakableBlock:: Update(float dt)
{
    float amplitude = 4.0f; // Moves 4 pixels up and down
    float speed = 5.0f;     // How fast it bobs

    // Sine wave formula: baseline + sin(time * speed) * amplitude
    position.y = startY + sin(GetTime() * speed) * amplitude;
    
    // Keeps the collision box perfectly synced with the visual position!
    collider.position.y = position.y;
}

void BreakableBlock :: Render()
{
    DrawRectangleV(Vector2(position.x,position.y),Vector2(size.x,size.y), RED);
}

void BreakableBlock :: OnHitFromBelow()
{

}

void Block::OnHitFromBelow()
{
}

void CoinBlock::Update(float dt)
{
}

void CoinBlock::Render()
{
}

void CoinBlock::OnHitFromBelow()
{
}
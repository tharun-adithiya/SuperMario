#include "Entities/Player.h"
#include <raylib.h>
#include "Math/Vector.h"

Player::Player()
{
    position = Vector2D(100, 100);
    width = 50;
    height = 50;
}

void Player::Update(float dt)
{
    if (IsKeyDown(KEY_D))
    {
        position.x += speed * dt;
    }

    if (IsKeyDown(KEY_A))
    {
        position.x -= speed * dt;
    }
}

void Player::Render()
{
    DrawRectangle(position.x, position.y, width, height, RED);
}

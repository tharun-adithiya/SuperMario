#include "MovingTile.h"

void MovingTile::Update(float dt)
{
    collider.velocity = Vector2D(direction * speed, 0);
    collider.position = collider.position + collider.velocity * dt;

    if (direction == 1 && collider.position.x >= pointB.x)
    {
        collider.position.x = pointB.x;
        direction = -1;
    }
    else if (direction == -1 && collider.position.x <= pointA.x)
    {
        collider.position.x = pointA.x;
        direction = 1;
    }
}

void MovingTile::Render()
{
    DrawRectangleV(
        {collider.position.x, collider.position.y},
        {collider.size.x, collider.size.y},
        ORANGE
    );
    DrawRectangleLinesEx(
        {collider.position.x, collider.position.y, collider.size.x, collider.size.y},
        2.0f,
        YELLOW
    );
}

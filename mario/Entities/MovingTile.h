#pragma once
#include "raylib.h"
#include "Math/AABB.h"

struct MovingTile
{
    boxCollider2D collider;
    Vector2D      pointA;
    Vector2D      pointB;
    float         speed;
    float         mass;
    float         restitution;
    int           direction;

    MovingTile() : speed(120.0f), mass(100.0f), restitution(0.0f), direction(1) {}

    MovingTile(Vector2D start, Vector2D end, Vector2D size, float speed, float mass, float restitution)
        : pointA(start), pointB(end), speed(speed), mass(mass), restitution(restitution), direction(1)
    {
        collider = boxCollider2D(size, start);
        collider.velocity = Vector2D(speed, 0);
    }

    void Update(float dt);
    void Render();
};

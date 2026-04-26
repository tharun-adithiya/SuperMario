#pragma once
#include "Math/Vector.h"
#include "Math/AABB.h"
class Player
{
    private:
        Vector2D position;
        Vector2D velocity;
        AABB hitBox;
        float height;
        float width;
        float gravity = 9.81*30;
        float maxFallSpeed = 1000;
        float speed=100;
        float jumpHeight=50;
        int inputAxisX=0;
    public:
        Player();
        void Update(float dt);
        void HandleInput();
        void Render();
        void Move(float dt);
        void Jump();
        bool IsGrounded();
        void ApplyGravity(float dt);
        Vector2D GetPosition() const { return position; }
};
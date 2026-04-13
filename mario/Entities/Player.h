#pragma once
#include "Math/Vector.h"

class Player
{
    private:
        Vector2D position;
        Vector2D velocity;
        float height;
        float width;
        float gravity = 9.81*10;
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
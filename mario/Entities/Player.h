#pragma once
#include "Math/Vector.h"

class Player
{
    private:
        Vector2D position;
        Vector2D velocity;
        float height;
        float width;
        float gravity = 9.81;
        float speed=100;
        int inputAxisX=0;
    public:
        Player();
        void Update(float dt);
        void HandleInput();
        void Render();
        void Move(float dt);
        void ApplyGravity(float dt);
};
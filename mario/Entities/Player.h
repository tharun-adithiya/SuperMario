#pragma once
#include "Math/Vector.h"

class Player
{
    private:
        Vector2D position;
        float height;
        float width;
        float speed=100;
    public:
        
        Player();
        void Update(float dt);
        void Render();
};
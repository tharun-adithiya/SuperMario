#pragma once
#include <raylib.h>
#include "Entities/Player.h"
class Game
{
    private:
        Player player;
    public:
        void Init();
        void Update(float dt);
        void Render();
        void Shutdown();
        
};
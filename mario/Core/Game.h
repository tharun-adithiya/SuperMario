#pragma once
#include <raylib.h>
#include "Entities/Player.h"
#include "World/Tilemap.h"

class Game
{
    private:
        Player player;
        
    public:
        static Tilemap tilemap;
        void Init();
        void Update(float dt);
        void Render();
        void Shutdown();
        
};
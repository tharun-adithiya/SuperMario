#pragma once
#include <raylib.h>
#include "Entities/Player.h"
#include "World/Tilemap.h"
#include "UI.h"
class Game
{
    private:
        Player player;
        
        bool isDebugOn=false;
        Camera2D camera;
        UI ui;
        static int coinsColected;
    public:
        Game(){};
        static Game Instance;
        static Tilemap tilemap;
        void Init();
        void Restart();
        void Update(float dt);
        void Render();
        void Shutdown();
        static int GetCoins(){return coinsColected;}
        static void updateCoins() {coinsColected++;}
};


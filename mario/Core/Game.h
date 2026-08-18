#pragma once
#include <raylib.h>
#include "Entities/Player.h"
#include "World/Tilemap.h"
#include "Entities/Enemy.h"
#include "UI.h"
#include "AudioSystem.h"
#include <memory>
using namespace std;

enum GameState
{
    PLAYING,
    PLAYER_DIES,
    GAME_OVER
};

class Game
{
    private:
        
        Player player;
        Goompa goompa;
        bool isDebugOn=false;
        Camera2D camera;
        UI ui;
        static int coinsColected;
    public:
        GameState currentState = PLAYING;
        Game(){};
        static Game Instance;
        static Tilemap tilemap;
        static AudioSystem audioSystem;
        void Init();
        void Restart();
        void Update(float dt);
        void Render();
        void Shutdown();
        static int GetCoins(){return coinsColected;}
        static void updateCoins() {coinsColected++;}
        Goompa& getGoompa(){return goompa;}
};


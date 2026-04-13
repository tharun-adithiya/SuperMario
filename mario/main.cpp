#include <raylib.h>
#include <math.h>
#include "Math/Vector.h"
#include "Core/Game.h"


int main()
{
    Game game;
    game.Init();
    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();
        game.Update(dt);
        game.Render();
    }
    game.Shutdown();
    return 0;
} 
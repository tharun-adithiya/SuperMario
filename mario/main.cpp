#include <raylib.h>
#include <math.h>
#include "Math/Vector.h"
#include "Core/Game.h"


int main()
{
    Game::Instance.Init();
    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Game::Instance.Update(dt);
        Game::Instance.Render();
    }
    Game::Instance.Shutdown();
    return 0;
} 
#include "raylib.h"
#include "Core/Game.h"

void Game::Init()
{
    InitWindow(800, 600, "Mario");
    SetTargetFPS(60);
}

void Game::Update(float dt)
{
    player.Update(dt);
}

void Game::Render()
{
    BeginDrawing();
    ClearBackground(BLUE);
    player.Render();
    EndDrawing();
}

void Game::Shutdown()
{
    CloseWindow();
}
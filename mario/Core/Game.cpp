#include "raylib.h"
#include "Core/Game.h"
#include "Core/Debug.h"
#include "World/Tilemap.h"
void Game::Init()
{
    InitWindow(800, 600, "Mario");
    tilemap=Tilemap(10, 10, 50); // Initialize tilemap with width, height, and tile size
    tilemap.Load(); // Load tile data
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
    tilemap.Render();
    DrawDebugPosition(player.GetPosition());
    EndDrawing();
}

void Game::Shutdown()
{
    CloseWindow();
}
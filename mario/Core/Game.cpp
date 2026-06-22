#include "raylib.h"
#include "Core/Game.h"
#include "Core/Debug.h"
#include "World/Tilemap.h"
#include "Math/Vector.h"
#include "Math/AABB.h"
Tilemap Game::tilemap;

void Game::Init()
{
    InitWindow(800, 600, "Mario");
    tilemap=Tilemap(16, 12, 50); // Initialize tilemap with width, height, and tile size
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
    Debug::DrawWorldGrid(tilemap.GetTileSize(), GetScreenWidth(), GetScreenHeight());
    Debug::DrawDebugPosition(player.GetPosition());
    Debug::DrawPlayerHitBox(player.GetPosition().x, player.GetPosition().y, player.getHitboxHeight(),player.getHitboxWidth());
    Debug::DrawSweptArea(player.GetDebugSweptArea());
    EndDrawing();
}

void Game::Shutdown()
{
    CloseWindow();
}


#include "raylib.h"
#include "Core/Game.h"
#include "Core/Debug.h"
#include "World/Tilemap.h"
#include "Math/Vector.h"
#include "Math/AABB.h"
Tilemap Game::tilemap;
int Game::coinsColected = 0;
Game Game::Instance;

void Game::Init()
{
    InitWindow(800, 600, "Mario");
    player.Init(); 
    tilemap=Tilemap(100, 50, 50); // Initialize tilemap with width, height, and tile size
    tilemap.Load(); // Load tile data
    SetTargetFPS(60);
    ui=UI();
    coinsColected=0;
    
    camera = { 0 };
    camera.target = (Vector2){ player.GetPosition().x, player.GetPosition().y };
    camera.offset = (Vector2){ 800.0f / 2.0f, 600.0f / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void Game::Update(float dt)
{
    tilemap.Update(dt);
    player.Update(dt);
    camera.target = (Vector2){ player.GetPosition().x, player.GetPosition().y };

    if(IsKeyPressed(KEY_T)&&!isDebugOn) isDebugOn=true;
    else if (IsKeyPressed(KEY_T)&& isDebugOn) isDebugOn=false;

}

void Game::Render()
{
    BeginDrawing();
    ClearBackground(BLUE);
    
    BeginMode2D(camera);
    player.Render();
    tilemap.Render();
    if(isDebugOn)
    {
        //Debug::DrawWorldGrid(tilemap.GetTileSize(), tilemap.GetWidth(), tilemap.GetHeight());
       // Debug::DrawPlayerHitBox(player.GetPosition().x, player.GetPosition().y, player.getHitboxHeight(),player.getHitboxWidth());
        Debug::DrawSweptArea(player.GetDebugSweptArea());
        Debug::DrawLevelEndCollider(tilemap.GetLevelEndCollider());
    }
    EndMode2D();

    ui.Render();

    if(isDebugOn)
    {
        Debug::DrawDebugPosition(player.GetPosition());
        Debug::DrawFPS();
    }
    
    EndDrawing();
}

void Game::Restart()
{
    player.ResetPlayer();
    tilemap.ResetWorldItems();
    coinsColected=0;
    
    camera = { 0 };
    camera.target = (Vector2){ player.GetPosition().x, player.GetPosition().y };
    camera.offset = (Vector2){ 800.0f / 2.0f, 600.0f / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void Game::Shutdown()
{
    CloseWindow();
}



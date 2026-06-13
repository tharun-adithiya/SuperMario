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
    /*Vector2D rayPoint= {20,20};
    Vector2D mousePos= {GetMousePosition().x,GetMousePosition().y};
    int gridX = static_cast<int>(mousePos.x) / tilemap.GetTileSize();
    int gridY = static_cast<int>(mousePos.y) / tilemap.GetTileSize();
    MyRect playerRect= {Vector2D(50,50), Vector2D(GetScreenWidth()/2,GetScreenHeight()/2),Vector2D(0,0)};
    Vector2D rayDir= mousePos-rayPoint;
    DrawRectangle(playerRect.position.x,playerRect.position.y,playerRect.size.x,playerRect.size.y,BLACK);
    DrawLine(rayPoint.x,rayPoint.y,mousePos.x,mousePos.y,GREEN);
    Vector2D cPoint, cNormal;
    float t;
    if (AABB::RayVsRect(rayPoint, rayDir, playerRect, t, cPoint, cNormal) && t < 1.0f)
    {
        Vector2D endPoint = cPoint + cNormal * 30.0f; 
        
        DrawRectangle(playerRect.position.x, playerRect.position.y, playerRect.size.x, playerRect.size.y, GREEN);
        DrawCircle(cPoint.x, cPoint.y, 10, RED);
        DrawLineEx(Vector2{cPoint.x, cPoint.y}, Vector2{endPoint.x, endPoint.y}, 3.0f, YELLOW); 
    }
    if(AABB::RayVsRect(rayPoint,rayDir,tilemap.GetActualTile(gridX,gridY).collider,t, cPoint, cNormal) && t < 1.0f)
    {
        Vector2D endPoint = cPoint + cNormal * 30.0f; 
        DrawCircle(cPoint.x, cPoint.y, 10, RED);
        DrawLineEx(Vector2{cPoint.x, cPoint.y}, Vector2{endPoint.x, endPoint.y}, 3.0f, YELLOW); 
    }
    else
    {
        DrawRectangle(playerRect.position.x,playerRect.position.y,playerRect.size.x,playerRect.size.y,BLACK);
    }*/

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
    EndDrawing();
}

void Game::Shutdown()
{
    CloseWindow();
}


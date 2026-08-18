#include "raylib.h"
#include "Core/Game.h"
#include "Core/Debug.h"
#include "World/Tilemap.h"
#include "Math/Vector.h"
#include "Math/AABB.h"
Tilemap Game::tilemap;
AudioSystem Game::audioSystem;
int Game::coinsColected = 0;
Game Game::Instance;


void Game::Init()
{
    InitWindow(800, 600, "Mario");
    
    currentState = PLAYING;
    player.OnDeathEvent = [this]() {
        this->currentState = PLAYER_DIES;
        audioSystem.PlayMusic(DEATH_MUSIC);
    };
    audioSystem.Init();
    audioSystem.PlayMusic(GAME_MUSIC);
    player.Init(); 
    goompa=Goompa({300,100});
    goompa.InitTexture();
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
    audioSystem.Update(dt);

    if (currentState == PLAYING) {
        tilemap.Update(dt);
        player.Update(dt);
        goompa.Update(dt);
        camera.target = (Vector2){ player.GetPosition().x, player.GetPosition().y };
    } 
    else if (currentState == PLAYER_DIES) {
        player.UpdateDeathAnimation(dt);
    }

    if(IsKeyPressed(KEY_T)&&!isDebugOn) isDebugOn=true;
    else if (IsKeyPressed(KEY_T)&& isDebugOn) isDebugOn=false;

}

void Game::Render()
{
    BeginDrawing();
    ClearBackground(BLUE);
    BeginMode2D(camera);
    tilemap.Render();
    player.Render();
    goompa.Render();
    
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
    currentState = PLAYING;
    audioSystem.PlayMusic(GAME_MUSIC);
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
    audioSystem.ShutDown();
    CloseWindow();
}



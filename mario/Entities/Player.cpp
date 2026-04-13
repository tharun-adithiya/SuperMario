#include "Entities/Player.h"
#include <algorithm>
#include <raylib.h>
#include "Math/Vector.h"
#include "Player.h"
#include "World/Tilemap.h"
#include "Core/Game.h"
#include "iostream"
using namespace std;
Player::Player()
{
    position = Vector2D(100, 100);
    velocity = Vector2D(0, 0);
    width = 50;
    height = 100;
}

void Player::Update(float dt)
{
    HandleInput();

    ApplyGravity(dt);

    Move(dt);

    if(IsGrounded()) // Simple ground collision check
    {
        position.y = Game::tilemap.GetTileSize() * (static_cast<int>((position.y+height) / Game::tilemap.GetTileSize()))-height; // Snap player to the top of the ground tile
        velocity.y = 0;
    }
    
}
void Player::HandleInput()
{
    if(IsKeyPressed(KEY_W) && IsGrounded()) // Simple jump check, only allows jumping if player is on the ground
    {
        Jump();
    }
    
    if (IsKeyDown(KEY_D)) inputAxisX = 1;
    
    else if (IsKeyDown(KEY_A)) inputAxisX = -1;

    else inputAxisX = 0;
}


void Player::Move(float dt)               // This function updates the player's position based on the input axis and speed, allowing for horizontal movement
{
    velocity.x = inputAxisX * speed;
    position += velocity * dt;
}

void Player::Jump()
{
    velocity.y = -sqrt(2 * gravity * jumpHeight); // Jump velocity calculated using physics formula for jump height
}

bool Player::IsGrounded()
{
    return Game::tilemap.GetTile(position.x / Game::tilemap.GetTileSize(), (position.y+height) / Game::tilemap.GetTileSize()) == TileType::Ground;
    //return position.y >= GetScreenHeight() - height;
}
void Player::ApplyGravity(float dt)     // This function applies gravity to the player, affecting the vertical velocity and position
{
    velocity.y += gravity * dt;        // 9.81 is the gravitation constant for earth, you can adjust it for different gravity strength 
    velocity.y = std::min(velocity.y, maxFallSpeed); // Limit the falling speed to prevent excessive velocity
}

void Player::Render()
{
    DrawRectangle(position.x, position.y, width, height, RED);
}

#include "Entities/Player.h"
#include <raylib.h>
#include "Math/Vector.h"

Player::Player()
{
    position = Vector2D(100, 100);
    velocity = Vector2D(0, 0);
    width = 50;
    height = 50;
}

void Player::Update(float dt)
{
    ApplyGravity(dt);
    HandleInput();
    Move(dt);
}
void Player::HandleInput()
{
    if (IsKeyDown(KEY_D)) inputAxisX = 1;
    
    else if (IsKeyDown(KEY_A)) inputAxisX = -1;

    else inputAxisX = 0;
}
void Player::Move(float dt)               // This function updates the player's position based on the input axis and speed, allowing for horizontal movement
{
    velocity.x = inputAxisX * speed;
    position += velocity * dt;
}
void Player::ApplyGravity(float dt)     // This function applies gravity to the player, affecting the vertical velocity and position
{
    velocity.y += gravity * dt;        // 9.81 is the gravitation constant for earth, you can adjust it for different gravity strength 
    position += velocity * dt;
}

void Player::Render()
{
    DrawRectangle(position.x, position.y, width, height, RED);
}

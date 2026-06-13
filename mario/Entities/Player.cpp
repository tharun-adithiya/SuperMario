#include "Entities/Player.h"
#include <algorithm>
#include <raylib.h>
#include "Math/Vector.h"
#include "Player.h"
#include "World/Tilemap.h"
#include "Core/Game.h"
#include "Physics/CollisionResolver.h"
using namespace std;
Player::Player()
{
    position = Vector2D(100, 100);
    playerCenter = Vector2D(position.x + width/2, position.y + height/2);
    velocity = Vector2D(0, 0);
    width = 50;
    height = 100;
    collider= MyRect(Vector2D(width,height),position,velocity);
}

void Player::Update(float dt)
{
    HandleInput();
    ApplyGravity(dt);
    
    velocity.x = inputAxisX * speed; 
    collider.velocity = velocity;
    isGrounded = false;
    debugHits.clear();

    // Get all tiles once
    vector<Tile> solidTiles = Game::tilemap.GetSolidTiles();

    // Loop a few times to allow for sliding off multiple walls/floors in one frame
    for (int i = 0; i < 4; i++) 
    {
        vector<CollisionInfo> hits;

        // 1. Gather all current hits
        for(const Tile &tile : solidTiles)
        {
            CollisionInfo hit = AABB::DynamicRectVsRect(collider, tile.collider, dt);
            if(hit.hit) 
            {
                hits.push_back(hit);
            }
        }

        // 2. If we didn't hit anything, we are safe to break out!
        if (hits.empty()) break;

        // 3. Sort hits so we resolve the CLOSEST one first
        std::sort(hits.begin(), hits.end(), [](const CollisionInfo& a, const CollisionInfo& b) {
            return a.collisionTime < b.collisionTime;
        });

        // 4. Resolve only the FIRST hit
        CollisionInfo firstHit = hits[0];
        
        if (firstHit.contactNormal.y == -1)
        {
            isGrounded = true;
        }

        CollisionResolver::Resolve(velocity, firstHit);
        debugHits.push_back(firstHit);
        // 5. CRITICAL: Update the collider's velocity for the next loop iteration!
        // This ensures we don't hit the internal cracks of the tiles!
        collider.velocity = velocity;
    }
    
    position += velocity * dt;
    collider.position = position;
}
void Player::HandleInput()
{
    if(IsKeyPressed(KEY_W) && isGrounded) // Simple jump check, only allows jumping if player is on the ground
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

void Player::ApplyGravity(float dt)     // This function applies gravity to the player, affecting the vertical velocity and position
{
    velocity.y += gravity * dt;        // 9.81 is the gravitation constant for earth, you can adjust it for different gravity strength 
    velocity.y = std::min(velocity.y, maxFallSpeed); // Limit the falling speed to prevent excessive velocity
}

void Player::Render()
{
    DrawRectangle(position.x, position.y, width, height, RED);
    
    // Draw collision normal visualizers on top of the player

    for(const auto& hit : debugHits)
    {
        Vector2D endPoint = hit.contactPoint + hit.contactNormal * 30.0f; 
        DrawCircle(hit.contactPoint.x, hit.contactPoint.y+height/2, 10, YELLOW);
        DrawLineEx(Vector2{hit.contactPoint.x, hit.contactPoint.y+height/2}, Vector2{endPoint.x, endPoint.y+height/2}, 5.0f, GREEN);
    }
}

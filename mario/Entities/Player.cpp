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
    
    HandleInput(dt);

    ApplyGravity(dt);
    
    if(wasGrounded&&!isGrounded&&velocity.y>=0)
    {
        coyoteTimer=coyoteTime;
    }
    if(!isGrounded)
    { 
        coyoteTimer-=dt;
    }
    //if(bufferTimer>0) bufferTimer-=dt;

    wasGrounded=isGrounded;

    velocity.x = inputAxisX * speed; 
    collider.velocity = velocity;
    isGrounded = false;
    debugHits.clear();

    // Calculate the swept area for debugging
    float minX = std::min(collider.position.x, collider.position.x + velocity.x * dt);
    float minY = std::min(collider.position.y, collider.position.y + velocity.y * dt);
    float maxX = std::max(collider.position.x + collider.size.x, collider.position.x + collider.size.x + velocity.x * dt);
    float maxY = std::max(collider.position.y + collider.size.y, collider.position.y + collider.size.y + velocity.y * dt);
    debugSweptArea = MyRect(Vector2D(maxX - minX, maxY - minY), Vector2D(minX, minY));

    // Get only the tiles near the player's movement path
    vector<Tile> solidTiles = Game::tilemap.GetNearbySolidTiles(collider, velocity, dt);

    // Loop a few times to allow for sliding off multiple walls/floors in one frame
    for (int i = 0; i < 4; i++) 
    {
        vector<CollisionInfo> hits;

        // Gathers all current hits
        for(const Tile &tile : solidTiles)
        {
            CollisionInfo hit = AABB::DynamicRectVsRect(collider, tile.collider, dt);
            if(hit.hit) 
            {
                hits.push_back(hit);
            }
        }

        // If didn't hit anything, breaks out!
        if (hits.empty()) break;

        //Sort hits so to resolve the closest one first

        std::sort(hits.begin(), hits.end(), [](const CollisionInfo& a, const CollisionInfo& b) {
            return a.collisionTime < b.collisionTime;
        });

        // Resolves only the first hit
        CollisionInfo firstHit = hits[0];
        
        if (firstHit.contactNormal.y == -1)
        {
            isGrounded = true;
        }

        CollisionResolver::Resolve(velocity, firstHit);
        debugHits.push_back(firstHit);
        
        // Updating the collider's velocity for the next loop iteration
        // This ensures that the player don't hit the internal cracks of the tiles
        collider.velocity = velocity;
    }
    
    position += velocity * dt;
    collider.position = position;
}
void Player::HandleInput(float dt)
{
    if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_SPACE))
    {
        JumpbufferTimer = JumpbufferTime;
    }

    // Updates timers
    JumpbufferTimer -= dt;
    
    if(JumpbufferTimer > 0 &&
    (isGrounded || coyoteTimer > 0))
    {
        Jump();

        JumpbufferTimer = 0;
        coyoteTimer = 0;
    }
    if(IsKeyReleased(KEY_W)&&velocity.y<0)          //Variable jump height
    {
        velocity.y*=0.52f;
    }

    if (IsKeyDown(KEY_D)) {inputAxisX = 1; }
    
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
        DrawCircle(hit.contactPoint.x, hit.contactPoint.y, 10, YELLOW);
        DrawLineEx(Vector2{hit.contactPoint.x, hit.contactPoint.y}, Vector2{endPoint.x, endPoint.y}, 3.0f, GREEN);
    }
}

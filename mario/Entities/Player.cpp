#include "Entities/Player.h"
#include <algorithm>
#include "Math/Vector.h"
#include "Player.h"
#include "World/Tilemap.h"
#include "Core/Game.h"
#include "Physics/CollisionResolver.h"
using namespace std;
Player::Player()
{
    position = Vector2D(100, 100);
    width = 50;
    height = 50;
    playerCenter = Vector2D(position.x + width/2, position.y + height/2);
    velocity = Vector2D(0, 0);
    
    colliderPadding=8;

    collider= boxCollider2D(Vector2D(width-2*colliderPadding,height),Vector2D(position.x+colliderPadding,position.y),velocity);
}

void Player::Init()
{
    try{
        string playerTexturePath="mario/Art/Mario_Small_Idle.png";

        if(!FileExists(playerTexturePath.c_str()))  throw runtime_error("Failed to get file at "+ playerTexturePath);
        else cout<<"Player texture is found";

        playerTexture=LoadTexture(playerTexturePath.c_str());
    }
    catch(const runtime_error& e)
    {   
        cout<<e.what()<<endl;
    }
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

    wasGrounded=isGrounded;

    velocity.x = inputAxisX * maxSpeed*builtUpSpeed; 
    collider.velocity = velocity;
    isGrounded = false;
    debugHits.clear();

    PerformCollisionCheckAgainstTiles(dt);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
    PerformCollisionCheckAgainstTriggers(dt);
    PerformCollisionCheckAgainstBlocks(dt);
    PerformCollisionCheckAgainstLevelEnd(dt);
    position += velocity * dt;
    // Center the collider horizontally based on how much smaller it is than the visual width
    collider.position = Vector2D(position.x + (width - collider.size.x) / 2.0f, position.y);
}

void Player::PerformCollisionCheckAgainstTiles(float dt)
{
    // Calculate the swept area for debugging
    float minX = std::min(collider.position.x, collider.position.x + velocity.x * dt);
    float minY = std::min(collider.position.y, collider.position.y + velocity.y * dt);
    float maxX = std::max(collider.position.x + collider.size.x, collider.position.x + collider.size.x + velocity.x * dt);
    float maxY = std::max(collider.position.y + collider.size.y, collider.position.y + collider.size.y + velocity.y * dt);
    debugSweptArea = boxCollider2D(Vector2D(maxX - minX, maxY - minY), Vector2D(minX, minY));

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
}

void Player :: PerformCollisionCheckAgainstTriggers(float dt)
{
    for(auto& coin : Game::tilemap.GetAllCoins())
    {
        if(coin.isCollected) continue;

        CollisionInfo info = AABB::DynamicRectVsRect(collider, coin.triggerCollider, dt);
        if(info.hit) {
            cout<<"Coin is hit\n";
            Game::updateCoins();
            cout<<"Current coins:"<<Game::GetCoins();
            coin.DisableCoin();
        }
    }
}

void Player:: PerformCollisionCheckAgainstBlocks(float dt)
{
    for(auto& block : Game::tilemap.GetAllBlocks())
    {
        CollisionInfo info = AABB::DynamicRectVsRect(collider, block->collider, dt);
        if(block->isBroken) continue;
        if (info.contactNormal.y == -1)
        {
            isGrounded = true;
        }
        switch(block->type)
        {
            case BlockType::BreakableBlock:
            {
                //5cout<<"Checking breakable block";
                
                if(info.hit&&info.contactNormal==Vector2D{0,1})
                {
                    cout<<"Hit from below";
                    CollisionResolver::Resolve(velocity,info);
                    collider.velocity = velocity; // update collider velocity after resolution
                    block->OnHitFromBelow();
                }
                else if(info.hit)
                {
                    CollisionResolver::Resolve(velocity,info);
                    collider.velocity = velocity; // update collider velocity after resolution
                }
                
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

void Player::PerformCollisionCheckAgainstLevelEnd(float dt)
{
    CollisionInfo info= AABB::DynamicRectVsRect(collider,Game::tilemap.GetLevelEndCollider(),dt);
    if(info.hit)
    {
        cout<<"Player hit level end";
        Game::Instance.Restart();
    }
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
    if((IsKeyReleased(KEY_W)||IsKeyPressed(KEY_UP))&&velocity.y<0)          //Variable jump height
    {
        velocity.y*=0.52f;
    }

    if (IsKeyDown(KEY_D)||IsKeyDown(KEY_RIGHT)) {
        inputAxisX = 1; 
        lastInputAxis=inputAxisX;
        if(builtUpSpeed>1)
        {
            builtUpSpeed=1;
        }
        builtUpSpeed+=dt*rateofBuiltUpSpeed;
        //cout<<"BuiltUp speed:"<<builtUpSpeed;
    }
    
    else if (IsKeyDown(KEY_A)||IsKeyDown(KEY_LEFT)) {
        inputAxisX = -1;
        lastInputAxis=inputAxisX;
        if(builtUpSpeed>1)
        {
            builtUpSpeed=1;
        }
        builtUpSpeed+=dt*rateofBuiltUpSpeed;
        //cout<<"BuiltUp speed:"<<builtUpSpeed;
    }

    else{
        inputAxisX=0;
        builtUpSpeed=0;
    }
}


void Player::Move(float dt)               // This function updates the player's position based on the input axis and speed, allowing for horizontal movement. This function is not being used now.
{
    velocity.x = inputAxisX * maxSpeed*builtUpSpeed;
    cout<<"Current Velocity: "<<velocity.x;
    position += velocity;
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
    //DrawRectangleV((Vector2){position.x, position.y}, (Vector2){(float)width, (float)height}, RED);
    
    DrawTexturePro(playerTexture, {0, 0, lastInputAxis*(float)playerTexture.width, (float)playerTexture.height}, {position.x, position.y, (float)width, (float)height}, {0, 0}, 0.0f, WHITE);
   
    /*for(const auto& hit : debugHits)                  Debug to check collision normal and hit status with tiles.
    {
        Vector2D endPoint = hit.contactPoint + hit.contactNormal * 30.0f; 
        DrawCircleV((Vector2){hit.contactPoint.x, hit.contactPoint.y}, 10.0f, YELLOW);
        DrawLineEx(Vector2{hit.contactPoint.x, hit.contactPoint.y}, Vector2{endPoint.x, endPoint.y}, 3.0f, GREEN);
    }*/
}

void Player::ResetPlayer()
{
    position = Vector2D(100, 100);
    playerCenter = Vector2D(position.x + width/2, position.y + height/2);
    velocity = Vector2D(0, 0);
    colliderPadding=8;
    collider= boxCollider2D(Vector2D(width-2*colliderPadding,height),Vector2D(position.x+colliderPadding,position.y),velocity);
}
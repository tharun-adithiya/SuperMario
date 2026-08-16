#include "Enemy.h"
#include "Core/Game.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <algorithm>

using namespace std;
void Goompa::Update(float dt)
{
    walkAnim.AnimationUpdate(dt);
    velocity.y+=gravity*dt;
    velocity.y=min(velocity.y,maxFallSpeed);
    isGrounded = false;
    if(!isDead)Patrol(Vector2D(300,0),Vector2D(450,0),dt);
    collider.velocity=velocity;
    PerformCollisionCheckAgainstTiles(dt);
    position+=velocity*dt;
    collider.position=position;
}

void Goompa::PerformCollisionCheckAgainstTiles(float dt)
{
    vector<Tile> nearbyTiles= Game::tilemap.GetNearbySolidTiles(collider,velocity,dt);
    for(int i=0;i<5;i++)
    {
        vector<CollisionInfo> collisionInfoList;
        for(auto& tile : nearbyTiles)
        {
            CollisionInfo collisionInfo=AABB::DynamicRectVsRect(collider,tile.collider,dt);
            if(collisionInfo.hit)
            {
                collisionInfoList.push_back(collisionInfo);
            }
        }
        if(collisionInfoList.empty()) break;
        std::sort(collisionInfoList.begin(), collisionInfoList.end(), [](const CollisionInfo& a, const CollisionInfo& b) {
            return a.collisionTime < b.collisionTime;
        });

        CollisionInfo firstHit=collisionInfoList[0];

        if(firstHit.contactNormal.y==-1) isGrounded=true;

        CollisionResolver::Resolve(velocity,firstHit);

        collider.velocity=velocity;

    }
    
}
void Goompa::Render()
{
    Texture2D activeTexture=texture;
    Rectangle source;
    if(isDead)
    {
        source=deathAnimation.AnimationFrame(3);   
    }
    else source=walkAnim.AnimationFrame(3);
    DrawTexturePro(activeTexture,source,{position.x,position.y,width,height},{0,0},0,WHITE);
}
void Goompa:: Patrol(const Vector2D& aPos, const Vector2D& bPos, float dt)
{
    // Start moving if standing still
    if (velocity.x == 0) velocity.x = moveSpeed;

    // Reverse direction if we hit the patrol bounds
    if (position.x <= aPos.x) {
        velocity.x = moveSpeed;
    } 
    else if (position.x >= bPos.x) {
        velocity.x = -moveSpeed;
    }
}
void Goompa::TakeDamage()
{

}
void Goompa::Die()
{
    cout<<"Invoked Die()";
    isDead=true;
    velocity.x=0;
    collider.velocity.x=0;
}
void Goompa::InitTexture()
{
    try
    {
        string texPath= "mario/Art/GoombaSheet.png";
        if(!FileExists(texPath.c_str())) throw runtime_error("Could not load goomba texture at: "+texPath);
        else cout<<"Goomba texture found";
        texture=LoadTexture(texPath.c_str());
    }
    catch(const runtime_error &e)
    {
        std::cerr << e.what() << '\n';
    }
}
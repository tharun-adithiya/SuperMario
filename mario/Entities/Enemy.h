#pragma once
#include "raylib.h"
#include "Math/Vector.h"
#include "Physics/CollisionResolver.h"
#include "Math/AABB.h"
#include "World/Tilemap.h"
#include "Graphics/Animation.h"
class Enemy
{
    protected:
        Texture2D texture;
        Vector2D position;
        Vector2D velocity;
        boxCollider2D collider;
        float health;
        float moveSpeed=50;
        float width, height;
        float gravity=9.81*50;
        float maxFallSpeed=1000;
        bool isGrounded;

        Enemy()
        {
            position={0,0};
            width=30;
            height=30;
            collider= boxCollider2D({width,height},position,velocity);
        }
       Enemy(Vector2D pos,float width,float height): 
        position(pos),
        velocity({0,0}),
        collider({width, height}, position, velocity),
        width(width),
        height(height)
        {}
        virtual void InitTexture() {}
        virtual void Update(float dt) {}
        virtual void Render() {}
        virtual void TakeDamage() {}
        virtual void Die() {}
        virtual void PerformCollisionCheckAgainstTiles(float dt) {}
        virtual void Patrol(const Vector2D& Apos, const Vector2D& Bpos, float dt) {}

};

class Goompa : public Enemy
{
    private:
        Animation walkAnim; 
    public:
        Goompa()
        {
            walkAnim=Animation(0,1,0,0.1,0.1);
        }
        Goompa(Vector2D position) : Enemy(position,30,30)
        {
            walkAnim=Animation(0,1,0,0.1,0.1);
        } 
        void InitTexture() override;
        void Update(float dt) override;
        void PerformCollisionCheckAgainstTiles(float dt)override;
        void Render() override;
        void TakeDamage() override;
        void Die() override;
        void Patrol(const Vector2D& Apos, const Vector2D& Bpos, float dt) override;
};
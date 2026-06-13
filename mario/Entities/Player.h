#pragma once
#include <vector>
#include "Math/Vector.h"
#include "Math/AABB.h"
class Player
{
    private:
        Vector2D position;
        Vector2D velocity;
        Vector2D playerCenter;
        AABB hitBox;
        MyRect collider;
        std::vector<CollisionInfo> debugHits;
        bool isGrounded=false;
        float height;
        float width;
        float gravity = 9.81*30;
        float maxFallSpeed = 1000;
        float speed=100;
        float jumpHeight=55;
        int inputAxisX=0;
    public:
        
        Player();
        void Update(float dt);
        void HandleInput();
        void Render();
        void Move(float dt);
        void Jump();
        bool IsGrounded();
        void ApplyGravity(float dt);
        Vector2D GetPosition() const { return position; }
        int getHitboxHeight() const {return collider.size.y;}
        int getHitboxWidth() const {return  collider.size.x;}
        Vector2D getVelocity() {return velocity;}
        void setVelocity(Vector2D velocity) {this->velocity=velocity;}
};
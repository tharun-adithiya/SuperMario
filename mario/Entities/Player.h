#pragma once
#include <vector>
#include "Math/Vector.h"
#include "Math/AABB.h"
class Player
{
    private:
        //Transform properties
        Vector2D position;
        Vector2D velocity;
        Vector2D playerCenter;

        //Collision properties
        MyRect collider;
        std::vector<CollisionInfo> debugHits;
        MyRect debugSweptArea;

        //Size properties
        float height;
        float width;

        //Movement properties
        bool isGrounded=false;
        bool wasGrounded=false;
        float gravity = 9.81*35;
        float maxFallSpeed = 1000;
        float speed=100;
        float coyoteTime=0.2;
        float jumpHeight=57;
        float rateOfJump=0.0;
        float coyoteTimer=0;
        int inputAxisX=0;


    public:
        
        Player();
        void Update(float dt);
        void HandleInput(float dt);
        void Render();
        void Move(float dt);
        void Jump();
        void VariableJump(float step);
        bool IsGrounded();
        void ApplyGravity(float dt);
        Vector2D GetPosition() const { return position; }
        int getHitboxHeight() const {return collider.size.y;}
        int getHitboxWidth() const {return  collider.size.x;}
        Vector2D getVelocity() {return velocity;}
        void setVelocity(Vector2D velocity) {this->velocity=velocity;}
        MyRect GetDebugSweptArea() const { return debugSweptArea; }
};
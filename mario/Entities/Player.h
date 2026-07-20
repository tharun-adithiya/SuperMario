#pragma once
#include <vector>
#include "Math/Vector.h"
#include "Math/AABB.h"
#include "Graphics/Animation.h"
#include "raylib.h"
class Player
{
    private:

        Texture2D playerTexture;

        Animation runAnimation;
        Animation idle;
        Animation jump;

        //Transform properties
        Vector2D position;
        Vector2D velocity;
        Vector2D playerCenter;
        
        //Collision properties
        boxCollider2D collider;
        float colliderPadding;
        std::vector<CollisionInfo> debugHits;
        boxCollider2D debugSweptArea;

        //Size properties
        float height;
        float width;

        //Movement properties
        bool isGrounded=false;
        bool wasGrounded=false;

        float gravity = 9.81*35;
        float maxFallSpeed = 1000;

        float maxSpeed=300;
        float builtUpSpeed=0;
        float rateofBuiltUpSpeed=5;

        float coyoteTime=0.2;
        float coyoteTimer=0;

        float JumpbufferTime=0.15;
        float JumpbufferTimer=0;

        float jumpHeight=57;

        int inputAxisX=0;
        int lastInputAxis=1;

    public:
        
        Player();
        void Init();
        void ResetPlayer();
        void Update(float dt);
        void PerformCollisionCheckAgainstTiles(float dt);
        void PerformCollisionCheckAgainstTriggers(float dt);
        void PerformCollisionCheckAgainstBlocks(float dt);
        void PerformCollisionCheckAgainstLevelEnd(float dt);
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
        boxCollider2D GetDebugSweptArea() const { return debugSweptArea; }
};
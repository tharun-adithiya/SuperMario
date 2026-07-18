#pragma once
#include "Vector.h"
struct boxCollider2D
{
    Vector2D size;
    Vector2D position;
    Vector2D velocity;
    bool isTrigger=false;
    boxCollider2D()
    {}
    /// @brief Takes the size, position and velocity of the box collider
    /// @param size 
    /// @param position 
    /// @param velocity 
    boxCollider2D(Vector2D size, Vector2D position, Vector2D velocity) : size(size), position(position), velocity(velocity)
    {}
    /// @brief Takes the size and position of the boxCollider
    /// @param size 
    /// @param position 
    boxCollider2D(Vector2D size, Vector2D position) : size(size), position(position){}

    bool operator==(const boxCollider2D&) const = default;
};

struct CollisionInfo
{
    bool hit=false;
    float collisionTime;
    Vector2D contactNormal;
    Vector2D contactPoint;

    
    CollisionInfo()
    {
        hit=false;
        collisionTime=1.0;
        contactNormal=Vector2D(0,0);
        contactPoint=Vector2D(0,0);
    }

    CollisionInfo(bool hit, float collisionTime, Vector2D contactPoint,Vector2D contactNormal) : 
    hit(hit), collisionTime(collisionTime), contactNormal(contactNormal), contactPoint(contactPoint)
    {}
};


struct AABB
{


    static bool RayVsRect(const Vector2D &rayOrigin , const Vector2D & velocityVec, const boxCollider2D & stationaryTarget, float & time_hit_near, Vector2D &contact_point, Vector2D & contact_normal)
    {
        contact_normal= {0,0};
        contact_point = {0,0};

        Vector2D inverseDir= 1/velocityVec;
        Vector2D t_near= (stationaryTarget.position-rayOrigin)*inverseDir;
        Vector2D t_far= (stationaryTarget.position+stationaryTarget.size-rayOrigin)*inverseDir;

        if(std::isnan(t_near.x)||std::isnan(t_near.y)) return false;
        if(std::isnan(t_far.x)||std::isnan(t_far.y)) return false;

       if(t_near.x>t_far.x) std::swap(t_near.x,t_far.x);
       if(t_near.y>t_far.y) std::swap(t_near.y,t_far.y);
       
       if(t_near.x>t_far.y||t_near.y>t_far.x) return false;

       time_hit_near= std::max(t_near.x,t_near.y);
       float time_hit_far= std::min(t_far.x,t_far.y);

       if(time_hit_far<=0) return false;

       contact_point=rayOrigin+time_hit_near*velocityVec;

       if(t_near.x>t_near.y) 
       {
            if(inverseDir.x<0)
            contact_normal ={1,0};
            else
            contact_normal={-1,0};
       }    
       else if(t_near.x<t_near.y)
       {
            if(inverseDir.y<0)
                contact_normal={0,1};
            else
                contact_normal={0,-1};
       }
       else
        {
            if(inverseDir.y < 0)
                contact_normal = {0,1};
            else
                contact_normal = {0,-1};
        }
            
        return true;
    }

    static CollisionInfo DynamicRectVsRect(const boxCollider2D &movingRect ,const boxCollider2D & stationaryTarget,float &elapsedTime)
    {

        CollisionInfo thisCollisionInfo= CollisionInfo();

        if(movingRect.velocity.x==0&&movingRect.velocity.y==0) return thisCollisionInfo;

        boxCollider2D expandedtargetRect;

        expandedtargetRect.position= stationaryTarget.position-movingRect.size/2;
        expandedtargetRect.size= stationaryTarget.size+movingRect.size;
        
        if(RayVsRect(
            movingRect.position+movingRect.size/2,
            movingRect.velocity*elapsedTime,
            expandedtargetRect,
            thisCollisionInfo.collisionTime,
            thisCollisionInfo.contactPoint,
            thisCollisionInfo.contactNormal
        ))
        {
            if(thisCollisionInfo.collisionTime<=1.0f&&thisCollisionInfo.collisionTime>=0.0f) 
            {
                thisCollisionInfo.hit=true;

                return thisCollisionInfo;
            }
        }

        return thisCollisionInfo;

    }
    
};
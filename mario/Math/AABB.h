#pragma once
#include "Vector.h"
struct MyRect
{
    Vector2D position;
    Vector2D size;
};

struct AABB
{
    Vector2D min;
    Vector2D max;

    AABB()
    {
        min=Vector2D(0, 0);
        max=Vector2D(0,0);
    }

    AABB(const Vector2D&min, const Vector2D &max)
    {
        this->min=min;
        this->max=max;
    }

    bool Intersects(const AABB& other)
    {
        return ((min.x<=other.max.x&& max.x>=other.min.x)&&(min.y<=other.max.y&& max.y>=other.min.y));
    }
    int getWidth() const
    {
        return max.x - min.x;
    }
    int getHeight() const
    {
        return max.y - min.y;
    }

    Vector2D getCenter() const
    {
        return Vector2D((min.x+max.x)/2,(min.y+max.y)/2);
    }

    bool SweptAABB(const AABB& moving, const Vector2D & velocity, const AABB & stationary, float & time_hit, Vector2D &contact_point, Vector2D & contact_normal)
    {
        AABB expandedStationary;
        expandedStationary.min=stationary.min - Vector2D(moving.getWidth()/2, moving.getHeight()/2);
        expandedStationary.max=stationary.max + Vector2D(moving.getWidth()/2, moving.getHeight()/2);

        Vector2D origin = moving.getCenter();

        float t_near_x=(expandedStationary.min.x - origin.x) / velocity.x;
        float t_far_x=(expandedStationary.max.x - origin.x) / velocity.x;
         
        float t_near_y=(expandedStationary.min.y - origin.y) / velocity.y;
        float t_far_y=(expandedStationary.max.y - origin.y) / velocity.y;

        if(t_near_x > t_far_x) swap(t_near_x, t_far_x);
        if(t_near_y> t_far_y) swap(t_near_y, t_far_y);

        if(t_near_x > t_far_y || t_near_y > t_far_x)
            return false;

        time_hit= std::max(t_near_x,t_near_y);
        float time_exit= std::min(t_far_x,t_far_y);

        if(t_far_x < 0 || t_far_y < 0)
            return false;

        contact_point = origin + velocity * time_hit;

        if(t_near_x>t_near_y)
        {
            if(velocity.x<0) contact_normal= Vector2D(-1,0);
            else contact_normal=Vector2D(1,0);
        }
        if(t_near_x<t_near_y)
        {
            if(velocity.y<0) contact_normal= Vector2D(0,1);
            else contact_normal=Vector2D(0,-1);
        }

        return true;
    }

    static bool RayVsRect(const Vector2D &rayOrigin , const Vector2D & velocityVec, const MyRect & stationaryTarget, float & time_hit_near, Vector2D &contact_point, Vector2D & contact_normal)
    {
        contact_normal= {0,0};
        contact_point = {0,0};

        Vector2D inverseDir= 1/velocityVec;
        Vector2D t_near= (stationaryTarget.position-rayOrigin)*inverseDir;
        Vector2D t_far= (stationaryTarget.position+stationaryTarget.size-rayOrigin)*inverseDir;

        if(std::isnan(t_near.x)||std::isnan(t_near.x)) return false;
        if(std::isnan(t_far.x)||std::isnan(t_far.x)) return false;

       if(t_near.x>t_far.x) std::swap(t_near.x,t_far.x);
       if(t_near.y>t_far.y) std::swap(t_near.y,t_far.y);
       
       if(t_near.x>t_far.y||t_near.y>t_far.x) return false;

       time_hit_near= std::max(t_near.x,t_near.y);
       float time_hit_far= std::min(t_far.x,t_far.y);

       if(time_hit_far<0) return false;

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
       return true;
    }
    
};
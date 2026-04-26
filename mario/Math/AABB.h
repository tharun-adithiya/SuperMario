#pragma once
#include "Vector.h"

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
};
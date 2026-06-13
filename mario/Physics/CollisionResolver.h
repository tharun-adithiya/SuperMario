#include "Entities/Player.h"
#include "Math/AABB.h"
#pragma once

class CollisionResolver
{
    public:
       static void Resolve(Vector2D& velocity, CollisionInfo &hit);
};

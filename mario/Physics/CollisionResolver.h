#include "Entities/Player.h"
#include "Math/AABB.h"
#pragma once

class CollisionResolver
{
    public:
       static void Resolve(Vector2D& velocity, CollisionInfo &hit);
       static void ResolveDynamic(Vector2D& velA, Vector2D& velB, float massA, float massB, float restitution, const CollisionInfo& hit);
};

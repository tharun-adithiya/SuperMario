#include "CollisionResolver.h"
#include "Math/Vector.h"
void CollisionResolver::Resolve(Vector2D& velocity, CollisionInfo &hit)
{
    velocity += hit.contactNormal* Vector2D(std::abs(velocity.x),std::abs(velocity.y))*(1-hit.collisionTime);

    
}


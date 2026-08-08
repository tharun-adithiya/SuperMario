#include "CollisionResolver.h"
#include "Math/Vector.h"

void CollisionResolver::Resolve(Vector2D& velocity, CollisionInfo &hit)
{
    velocity += hit.contactNormal* Vector2D(std::abs(velocity.x),std::abs(velocity.y))*(1-hit.collisionTime);
}

void CollisionResolver::ResolveDynamic(Vector2D& velA, Vector2D& velB, float massA, float massB, float restitution, const CollisionInfo& hit)
{
    Vector2D relVel = velA - velB;
    float relVelAlongNormal = Vector2D::DotProduct(relVel, hit.contactNormal);

    if (relVelAlongNormal > 0) return;

    float invMassA = (massA <= 0) ? 0.0f : 1.0f / massA;
    float invMassB = (massB <= 0) ? 0.0f : 1.0f / massB;

    float j = -(1.0f + restitution) * relVelAlongNormal;
    j /= (invMassA + invMassB);

    Vector2D impulse = j * hit.contactNormal;
    velA += invMassA * impulse;
    velB -= invMassB * impulse;
}

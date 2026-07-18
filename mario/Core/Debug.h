#pragma once
#include "Math/Vector.h"
#include "Math/AABB.h"

namespace Debug
{
    void DrawDebugInfo(const Vector2D& position, const Vector2D& velocity);
    void DrawDebugPosition(const Vector2D& position);
    void DrawLevelEndCollider(boxCollider2D collider);
    void DrawPlayerHitBox(float posX, float posY, float length, float width);
    void DrawWorldGrid(int tileSize, int cols, int rows);
    void DrawSweptArea(const boxCollider2D& sweptArea);
    void DrawFPS();
}

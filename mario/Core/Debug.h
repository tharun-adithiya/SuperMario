#pragma once
#include "Math/Vector.h"
#include "Math/AABB.h"

namespace Debug
{
    void DrawDebugInfo(const Vector2D& position, const Vector2D& velocity);
    void DrawDebugPosition(const Vector2D& position);
    void DrawPlayerHitBox(int posX, int posY,int length, int width);
    void DrawWorldGrid(int tileSize, int screenWidth, int screenHeight);
    void DrawSweptArea(const MyRect& sweptArea);
}

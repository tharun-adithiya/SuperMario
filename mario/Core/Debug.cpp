#include "Debug.h"
# include "raylib.h"

void Debug::DrawDebugPosition(const Vector2D& position)
{
    const int fontSize = 20;
    const int padding = 10;

    const char* text= TextFormat("Position: (%.2f, %.2f)", position.x, position.y);

    int textWidth = MeasureText(text, fontSize);

    int x= GetScreenWidth() - textWidth - padding;
    int y= padding;
    DrawText(text, x, y, fontSize, WHITE);
}

void Debug::DrawPlayerHitBox(int posX, int posY, int length, int width)
{
    DrawRectangleLines(posX, posY, width, length, GREEN);
}

void Debug:: DrawWorldGrid(int tileSize, int screenWidth, int screenHeight)
{
    for (int x = 0; x < screenWidth; x += tileSize)
    {
        DrawLine(x, 0, x, screenHeight, GRAY);
    }
    for (int y = 0; y < screenHeight; y += tileSize)
    {
        DrawLine(0, y, screenWidth, y, GRAY);
    }
}

void Debug::DrawSweptArea(const MyRect& sweptArea)
{
    DrawRectangleLines(sweptArea.position.x, sweptArea.position.y, sweptArea.size.x+10, sweptArea.size.y+10, ORANGE);
}

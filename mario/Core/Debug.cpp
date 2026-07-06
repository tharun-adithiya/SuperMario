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
void Debug::DrawFPS()
{
    const int fontSize = 20;
    const int padding = 40;
    const char* text= TextFormat("FPS:(%d)", GetFPS());

    int textWidth = MeasureText(text, fontSize);

    int x= GetScreenWidth() - textWidth - padding;
    int y= padding;
    DrawText(text, x, y, fontSize, WHITE);
}
void Debug::DrawPlayerHitBox(float posX, float posY, float length, float width)
{
    DrawRectangleLinesEx((Rectangle){posX, posY, width, length}, 1.0f, GREEN);
}

void Debug:: DrawWorldGrid(int tileSize, int cols, int rows)
{
    float worldWidth = cols * tileSize;
    float worldHeight = rows * tileSize;
    
    for (int x = 0; x <= cols; x++)
    {
        DrawLineV((Vector2){(float)(x * tileSize), 0.0f}, (Vector2){(float)(x * tileSize), worldHeight}, GRAY);
    }
    for (int y = 0; y <= rows; y++)
    {
        DrawLineV((Vector2){0.0f, (float)(y * tileSize)}, (Vector2){worldWidth, (float)(y * tileSize)}, GRAY);
    }
}

void Debug::DrawSweptArea(const boxCollider2D& sweptArea)
{
    DrawRectangleLinesEx((Rectangle){sweptArea.position.x, sweptArea.position.y, sweptArea.size.x, sweptArea.size.y}, 1.0f, ORANGE);
}

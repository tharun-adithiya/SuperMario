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

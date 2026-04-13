#include "Debug.h"
# include "raylib.h"
void DrawDebugPosition(const Vector2D& position)
{
    const int fontSize = 20;
    const int padding = 10;

    const char* text= TextFormat("Position: (%.2f, %.2f)", position.x, position.y);

    int textWidth = MeasureText(text, fontSize);

    int x= GetScreenWidth() - textWidth - padding;
    int y= padding;
    DrawText(text, x, y, fontSize, WHITE);
}
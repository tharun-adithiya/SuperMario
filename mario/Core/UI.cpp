#include "UI.h"
#include "Game.h"

void UI::DrawCoinsCollectedUI(int coins)
{
     const int fontSize = 20;
    const int padding = 10;

    const char* text= TextFormat("Coins: %d",coins);

    int textWidth = MeasureText(text, fontSize);

    int x= GetScreenWidth() - textWidth - padding;
    int y= padding;
    DrawText(text, x, y, fontSize, WHITE);
}

void UI::Render()
{
    DrawCoinsCollectedUI(Game::GetCoins());
}
#include "StartGameView.h"

void StartGameView::init()
{
    MenuView::init();
}

void StartGameView::render(SDL_Window *window)
{
    SDL_Rect backgroundRect = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2};
    SDL_FillRect(SDL_GetWindowSurface(window), &backgroundRect, 0x00FF0000);
    MenuView::render(window);
}
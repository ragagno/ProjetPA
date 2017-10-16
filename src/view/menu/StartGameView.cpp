#include "StartGameView.h"

void StartGameView::init()
{
    MenuView::init();
}

void StartGameView::render(SDL_Window *window)
{
    SDL_Rect rect = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2};
    SDL_FillRect(SDL_GetWindowSurface(window), &rect, 0x0000FF00);
    MenuView::render(window);
}
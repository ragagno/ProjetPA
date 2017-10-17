#include "ControlsView.h"

void ControlsView::init()
{
    MenuView::init();
}

void ControlsView::render(SDL_Window *window)
{
    SDL_Rect backgroundRect = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2};
    SDL_FillRect(SDL_GetWindowSurface(window), &backgroundRect, 0x0000FF00);
    MenuView::render(window);
}
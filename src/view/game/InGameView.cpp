#include <SDL2/SDL_ttf.h>
#include "InGameView.h"
#include "data/EntityRenderer.h"

InGameView::InGameView()
{
    resume = nullptr;
    quit = nullptr;
}

void InGameView::init()
{
    SDL_Color black = {0, 0, 0, 0};
    TTF_Font *munroMedium = TTF_OpenFont("resources/munro.ttf", 64);

    resume = TTF_RenderUTF8_Blended(munroMedium, "RESUME", black);
    quit = TTF_RenderUTF8_Blended(munroMedium, "QUIT", black);

    TTF_CloseFont(munroMedium);

    resumeRect = {(WINDOW_WIDTH - resume->w) / 2 + 3, (WINDOW_HEIGHT - 3 * resume->h) / 2 + 6, 0, 0};
    quitRect = {(WINDOW_WIDTH - quit->w) / 2 + 3, (WINDOW_HEIGHT + quit->h) / 2 + 6, 0, 0};
    pauseBackgroundRect = {0, (WINDOW_HEIGHT - (128 + resume->h + quit->h)) / 2, WINDOW_WIDTH, 128 + resume->h + quit->h};

}

InGameView::~InGameView()
{
    SDL_FreeSurface(resume);
    SDL_FreeSurface(quit);
}

void InGameView::reset()
{
    if (resetable)
    {
    }
    else
    {
        resetable = true;
    }
}

void InGameView::preRenderPause(uint_fast32_t selectedIndex)
{
    this->paused = true;
    switch (selectedIndex)
    {
        case 0:
            underlineRect = {resumeRect.x, resumeRect.y + this->resume->h - 8, this->resume->w - 6, 6};
            break;
        case 1:
            underlineRect = {quitRect.x, quitRect.y + this->quit->h - 8, this->quit->w - 6, 6};
            break;
        default:
            break;
    }
}

void InGameView::preRenderPlaying(Player *player)
{
    this->paused = false;
    this->player = player;
}

void InGameView::render(SDL_Window *window)
{
    SDL_Rect rect1 = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_FillRect(SDL_GetWindowSurface(window), &rect1, 0x00000000);

    EntityRenderer renderer;
    renderer.render(window, player);

    if (paused)
    {
        SDL_FillRect(SDL_GetWindowSurface(window), &pauseBackgroundRect, 0x00FFFFFF);
        SDL_BlitSurface(resume, nullptr, SDL_GetWindowSurface(window), &resumeRect);
        SDL_BlitSurface(quit, nullptr, SDL_GetWindowSurface(window), &quitRect);
        SDL_FillRect(SDL_GetWindowSurface(window), &underlineRect, 0x00000000);
    }
}